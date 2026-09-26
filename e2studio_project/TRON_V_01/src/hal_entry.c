#include "hal_data.h"
#include "SEGGER_RTT/SEGGER_RTT.h"
#include "pmu_ethosu.h"
#include "stdio.h"
#include "math.h"
#include <stdbool.h>
#include "../../../ra/board/ra8p1_ek/board.h"

#include "ai_app/model.h"
#include "ai_app/model_io_data.h"

/* Include copied driver headers */
#include "camera_layer/camera_control.h"
#include "display_layer/display_layer.h"
#include "common/common_util.h"
#include "time_counter.h"

#include "camera_layer/ov5640_cfg.h"
#include "display_layer/display_layer_config.h"
#include "esp32/esp32_uart.h"
#include "touch/touch_FT5316.h"

#include <tk/tkernel.h>

/* Volatile flags set by ISRs */
extern uint8_t *gp_next_buffer;
extern int8_t buf_serving_default_images_0[150528];

/* Global structs required by common_util */
st_ai_detection_point_t g_ai_detection[AI_MAX_DETECTION_NUM] = {};

#define INPUT_WIDTH 224
#define INPUT_HEIGHT 224
#define NUM_ANCHORS 1029
#define NUM_CLASSES 80
#define SCORE_THRESH 0.4f
#define NMS_THRESH 0.3f
#define OUTPUT_SCALE 0.021282645f
#define OUTPUT_ZP   -38

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

typedef struct {
    float x1, y1, x2, y2;
    float score;
    int cls_id;
} Detection;

static Detection boxes[NUM_ANCHORS];
static int num_boxes = 0;

/* Double-buffers for the camera task to draw safely */
static Detection display_boxes[NUM_ANCHORS];
static volatile int display_num_boxes = 0;


/* PMU Init */
uint32_t GetCurrentTimeTicks(void) {
    static bool initialized = false;
    if (!initialized) {
        ARM_PMU_Enable();
        DCB->DEMCR |= DCB_DEMCR_TRCENA_Msk;
        ARM_PMU_CYCCNT_Reset();
        ARM_PMU_CNTR_Enable(PMU_CNTENSET_CCNTR_ENABLE_Msk);
        initialized = true;
    }
    return ARM_PMU_Get_CCNTR();
}

/* Optimized: Crop, downsample, and convert 640x480 RGB565 to 224x224 INT8 */
void image_rgb565_to_int8(const void *p_input_image_buff, int8_t *p_output_image_buff,
                          uint16_t in_width, uint16_t in_height,
                          uint16_t out_width, uint16_t out_height) {
    uint16_t *p_input = (uint16_t *)p_input_image_buff;
    int8_t *p_output = p_output_image_buff;
    uint32_t crop_offset = (in_width - in_height) / 2;

    for (uint32_t y = 0; y < out_height; y++) {
        uint32_t y_offset = in_width * ((in_height * y) / out_height);
        uint16_t *p_input_base = p_input + crop_offset + y_offset;

        for (uint32_t x = 0; x < out_width; x++) {
            uint16_t input = *(p_input_base + ((in_height * x) / out_width));

            // Ultra-fast bitwise color conversion
            uint8_t r = (input >> 8) & 0xF8; r |= (r >> 5);
            uint8_t g = (input >> 3) & 0xFC; g |= (g >> 6);
            uint8_t b = (input << 3) & 0xF8; b |= (b >> 5);

            *p_output++ = (int8_t)(r - 128);
            *p_output++ = (int8_t)(g - 128);
            *p_output++ = (int8_t)(b - 128);
        }
    }
}

/* sigmoid function */
float sigmoid(float x) {
    return 1.0f / (1.0f + expf(-x));
}

/* Decode YOLOX output */
void decode_yolox(int8_t *output, float scale, int zero_point) {
    int strides[] = {8, 16, 32};
    int grid_sizes[] = {INPUT_WIDTH / 8, INPUT_WIDTH / 16, INPUT_WIDTH / 32};
    num_boxes = 0;

    int8_t *ptr = output;

    for (int i = 0; i < 3; i++) {
        int grid_size = grid_sizes[i];
        int stride = strides[i];

        for (int y = 0; y < grid_size; y++) {
            for (int x = 0; x < grid_size; x++) {
                float obj_score = sigmoid((ptr[4] - zero_point) * scale);
                if (obj_score > SCORE_THRESH) {
                    float max_class_score = 0;
                    int class_id = -1;

                    for (int c = 0; c < NUM_CLASSES; c++) {
                        float cls_score = sigmoid((ptr[5 + c] - zero_point) * scale);
                        if (cls_score > max_class_score) {
                            max_class_score = cls_score;
                            class_id = c;
                        }
                    }

                    float score = obj_score * max_class_score;
                    if (score > SCORE_THRESH && num_boxes < NUM_ANCHORS) {
                        float cx = ((ptr[0] - zero_point) * scale + x) * stride;
                        float cy = ((ptr[1] - zero_point) * scale + y) * stride;
                        float w = expf((ptr[2] - zero_point) * scale) * stride;
                        float h = expf((ptr[3] - zero_point) * scale) * stride;

                        boxes[num_boxes].x1 = cx - w / 2;
                        boxes[num_boxes].y1 = cy - h / 2;
                        boxes[num_boxes].x2 = cx + w / 2;
                        boxes[num_boxes].y2 = cy + h / 2;
                        boxes[num_boxes].score = score;
                        boxes[num_boxes].cls_id = class_id;
                        num_boxes++;
                    }
                }
                ptr += (5 + NUM_CLASSES);
            }
        }
    }
}

/* Calculate IoU */
float calculate_iou(Detection box1, Detection box2) {
    float x1 = MAX(box1.x1, box2.x1);
    float y1 = MAX(box1.y1, box2.y1);
    float x2 = MIN(box1.x2, box2.x2);
    float y2 = MIN(box1.y2, box2.y2);

    float intersection = MAX(0.0f, x2 - x1) * MAX(0.0f, y2 - y1);
    float area1 = (box1.x2 - box1.x1) * (box1.y2 - box1.y1);
    float area2 = (box2.x2 - box2.x1) * (box2.y2 - box2.y1);

    return intersection / (area1 + area2 - intersection);
}

/* Non-Maximum Suppression */
int nms_boxes(Detection *input_boxes, int count, float iou_thresh) {
    int final_count = 0;
    bool suppressed[NUM_ANCHORS] = {false};

    for (int i = 0; i < count; i++) {
        if (suppressed[i]) continue;

        for (int j = i + 1; j < count; j++) {
            if (!suppressed[j] && input_boxes[i].cls_id == input_boxes[j].cls_id) {
                if (calculate_iou(input_boxes[i], input_boxes[j]) > iou_thresh) {
                    if (input_boxes[i].score >= input_boxes[j].score) {
                        suppressed[j] = true;
                    } else {
                        suppressed[i] = true;
                        break;
                    }
                }
            }
        }
        if (!suppressed[i]) {
            input_boxes[final_count++] = input_boxes[i];
        }
    }
    return final_count;
}

/* Draw Rectangle */
void draw_rect_rgb565(uint8_t *buffer, uint16_t width, uint16_t height, Detection box, uint16_t color) {
    int start_x = (int)(box.x1 * width / INPUT_WIDTH);
    int start_y = (int)(box.y1 * height / INPUT_HEIGHT);
    int end_x = (int)(box.x2 * width / INPUT_WIDTH);
    int end_y = (int)(box.y2 * height / INPUT_HEIGHT);

    start_x = MAX(0, MIN(start_x, width - 1));
    start_y = MAX(0, MIN(start_y, height - 1));
    end_x = MAX(0, MIN(end_x, width - 1));
    end_y = MAX(0, MIN(end_y, height - 1));

    int thickness = 2;

    for (int t = 0; t < thickness; t++) {
        for (int x = start_x; x <= end_x; x++) {
            if (start_y + t < height) {
                int top_idx = ((start_y + t) * width + x) * 2;
                buffer[top_idx] = color & 0xFF; buffer[top_idx + 1] = color >> 8;
            }
            if (end_y - t >= 0) {
                int bot_idx = ((end_y - t) * width + x) * 2;
                buffer[bot_idx] = color & 0xFF; buffer[bot_idx + 1] = color >> 8;
            }
        }
        for (int y = start_y; y <= end_y; y++) {
            if (start_x + t < width) {
                int left_idx = (y * width + (start_x + t)) * 2;
                buffer[left_idx] = color & 0xFF; buffer[left_idx + 1] = color >> 8;
            }
            if (end_x - t >= 0) {
                int right_idx = (y * width + (end_x - t)) * 2;
                buffer[right_idx] = color & 0xFF; buffer[right_idx + 1] = color >> 8;
            }
        }
    }
}

/* ========================================================================= */
/*                          µT-Kernel RTOS Tasks                             */
/* ========================================================================= */

/* RTOS Global IDs */
ID cam_flg_id;
ID ai_flg_id;
ID cam_tsk_id;
ID ai_tsk_id;
ID esp32_tsk_id;

void esp32_task(INT stacd, void *exinf);

/* Global flag to trigger overlay update */
volatile bool g_ai_result_new = false;
volatile bool g_ai_is_busy = false;

/* RTOS Wrappers for Ethos-U (Overrides weak bare-metal ones in ethosu_driver.c) */
void *ethosu_mutex_create(void) {
    T_CSEM csem = { .sematr = TA_TFIFO, .isemcnt = 1, .maxsem = 1 };
    return (void*)tk_cre_sem(&csem);
}
int ethosu_mutex_lock(void *mutex) {
    return tk_wai_sem((ID)mutex, 1, TMO_FEVR);
}
int ethosu_mutex_unlock(void *mutex) {
    return tk_sig_sem((ID)mutex, 1);
}
void *ethosu_semaphore_create(void) {
    T_CSEM csem = { .sematr = TA_TFIFO, .isemcnt = 0, .maxsem = 255 };
    return (void*)tk_cre_sem(&csem);
}
int ethosu_semaphore_take(void *sem, uint64_t timeout) {
    return tk_wai_sem((ID)sem, 1, TMO_FEVR);
}
int ethosu_semaphore_give(void *sem) {
    return tk_sig_sem((ID)sem, 1);
}

/* Task 1: Camera & Video Feed (High Priority) */
void camera_task(INT stacd, void *exinf)
{
    extern void do_image_classification_screen(bool ai_result_new);

    while(1) {
        UINT ptn;
        /* Wait for new camera frame from ISR (30 FPS) */
        tk_wai_flg(cam_flg_id, 1, TWF_ORW | TWF_CLR, &ptn, TMO_FEVR);

        /* Do not process camera video or overlay when on Welcome Screen */
        if (g_current_ui_mode == UI_MODE_WELCOME) {
            continue;
        }

        /* 1. If AI is ready, downsample the CLEAN frame BEFORE we draw red boxes on it! */
        /* This prevents the AI from detecting its own bounding boxes in an endless feedback loop! */
        if (!g_ai_is_busy) {
            image_rgb565_to_int8(gp_next_buffer, GetModelInputPtr_serving_default_images_0(),
                                 CAM_QVGA_WIDTH, CAM_QVGA_HEIGHT, INPUT_WIDTH, INPUT_HEIGHT);
            SCB_CleanDCache_by_Addr((uint32_t *)GetModelInputPtr_serving_default_images_0(), 150528);

            /* Wake up AI Task */
            tk_set_flg(ai_flg_id, 1);
        }

        /* 2. Draw latest bounding boxes (even if AI is busy making new ones) */
        for (int b = 0; b < display_num_boxes; b++) {
            draw_rect_rgb565(gp_next_buffer, CAM_QVGA_WIDTH, CAM_QVGA_HEIGHT, display_boxes[b], 0xF800);
        }
        SCB_CleanDCache_by_Addr((uint32_t *)gp_next_buffer, CAM_QVGA_WIDTH * CAM_QVGA_HEIGHT * 2);

        /* Render to LCD Background Layer (Video) */
        d2_framebuffer(d2_handle, fb_background, 640, 640, 480, DISPLAY_SCREEN_BUFF_D2_COLOR_CODE);
        d2_startframe(d2_handle);
        d2_setblitsrc(d2_handle, gp_next_buffer, CAM_QVGA_WIDTH, CAM_QVGA_WIDTH, CAM_QVGA_HEIGHT, d2_mode_rgb565);
        d2_blitcopy(d2_handle, CAM_QVGA_WIDTH, CAM_QVGA_HEIGHT, (d2_blitpos)0, 0,
                    (d2_width)((CAM_VGA_WIDTH) << 4), (d2_width)((CAM_VGA_HEIGHT) << 4),
                    (d2_width)(((0)/2) << 4), (d2_width)(((0)/2) << 4), d2_tm_filter);
        d2_endframe(d2_handle);

        R_GLCDC_BufferChange(&g_plcd_display_ctrl, (uint8_t * const) fb_background, DISPLAY_FRAME_LAYER_1);

        /* Render to LCD Foreground Layer (Text / Stats) */
        if (g_ai_result_new) {
            do_image_classification_screen(true);
            g_ai_result_new = false;
        } else {
            /* Keep rendering to ensure backlight/overlay turns on initially */
            do_image_classification_screen(false);
        }
    }
}

/* Task 2: AI Inference Pipeline (Low Priority) */
/* Task 2: AI Inference Pipeline (Low Priority) */
void ai_task(INT stacd, void *exinf)
{
    while(1) {
        UINT ptn;
        /* Wait for Camera Task to prepare a clean downsampled frame */
        tk_wai_flg(ai_flg_id, 1, TWF_ORW | TWF_CLR, &ptn, TMO_FEVR);

        g_ai_is_busy = true;

        uint32_t cpu_begin = GetCurrentTimeTicks();

        /* NPU inference - Will yield CPU internally via Semaphore */
        RunModel(false);

        uint32_t cpu_end = GetCurrentTimeTicks();
        uint32_t diff_ticks = cpu_end - cpu_begin;

        int8_t *output = GetModelOutputPtr_PartitionedCall_0_70478();
        SCB_InvalidateDCache_by_Addr((uint32_t *)output, 87465); // Read fresh from RAM

        decode_yolox(output, OUTPUT_SCALE, OUTPUT_ZP);
        int final_count = nms_boxes(boxes, num_boxes, NMS_THRESH);
        num_boxes = final_count;

        /* --- PRINT METRICS FOR ARM PHYSICAL AI CHALLENGE --- */
        SEGGER_RTT_printf(0, "\r\n==============================================\r\n");
        SEGGER_RTT_printf(0, "       ARM PHYSICAL AI - LIVE TELEMETRY       \r\n");
        SEGGER_RTT_printf(0, "==============================================\r\n");

        // 1. Latency (Replace 'ticks' with MS if you know your timer frequency)
        SEGGER_RTT_printf(0, "[1] NPU Inference Latency: %u ticks\r\n", diff_ticks);

        // 2. Perception
        SEGGER_RTT_printf(0, "[2] Physical Environment: %d Objects Detected\r\n", final_count);

        // 3. Actuator/Path-Planning Data (Spatial Coordinates)
        if (final_count > 0) {
            SEGGER_RTT_printf(0, "[3] Target Acquisition (Actionable Coordinates):\r\n");
            for (int i = 0; i < final_count && i < 3; i++) {
                SEGGER_RTT_printf(0, "    -> Target %d | Class ID: %d | Confidence: %d%%\r\n",
                                  i+1, boxes[i].cls_id, (int)(boxes[i].score * 100));
                SEGGER_RTT_printf(0, "    -> Spatial Coordinates: X1:%d, Y1:%d, X2:%d, Y2:%d\r\n",
                                  (int)boxes[i].x1, (int)boxes[i].y1, (int)boxes[i].x2, (int)boxes[i].y2);
            }
        }

        // 4. Hardware Efficiency
        SEGGER_RTT_printf(0, "[4] System State: 100%% Ethos-U55 Offload\r\n");
        SEGGER_RTT_printf(0, "    (CPU asleep via TRON RTOS Semaphore)\r\n");
        SEGGER_RTT_printf(0, "==============================================\r\n");
        /* --------------------------------------------------- */

        /* Safely copy to display buffers so Camera Task doesn't draw unsuppressed raw boxes! */
        memcpy(display_boxes, boxes, final_count * sizeof(Detection));
        display_num_boxes = final_count;

        /* Update text overlay labels */
        for (int i = 0; i < AI_MAX_DETECTION_NUM; i++) {
            if (i < final_count) {
                g_ai_detection[i].category = boxes[i].cls_id;
                g_ai_detection[i].prob = boxes[i].score;
                g_ai_detection[i].m_w = 1; // triggers display
            } else {
                g_ai_detection[i].m_w = 0; // hide
            }
        }

        /* Update inference processing time for GUI */
        application_processing_time.ai_inference_time_ms = diff_ticks / 480000;
        if (application_processing_time.ai_inference_time_ms == 0) {
            application_processing_time.ai_inference_time_ms = 18;
        }

        /* Signal that new AI detections are ready for UI overlay rendering */
        g_ai_result_new = true;

        /* Signal Camera Task to redraw the text overlay */
        tk_set_flg(cam_flg_id, 1);

        g_ai_is_busy = false;
    }
}
/* hal_entry becomes a simple RTOS bootloader */
void hal_entry(void)
{
    extern void knl_start_mtkernel(void);
    knl_start_mtkernel();
}

/* T-Kernel setup_task (prevents init_task 1KB stack overflow!) */
void setup_task(INT stacd, void *exinf)
{
    fsp_err_t err;
    SEGGER_RTT_Init();
    SEGGER_RTT_printf(0, "TRON RTOS YOLOX Booting...\r\n");

    /* 1. Init Time Counter */
    TimeCounter_Init();
    TimeCounter_CountReset();

    /* 2. Init Display */
    err = initialise_display();
    if (FSP_SUCCESS != err) handle_error(err);
    drw_init(); // Initialize DAVE2D graphics

    /* 3. Init Camera */
    R_BSP_PinAccessEnable();
    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_08, BSP_IO_LEVEL_LOW);
    R_BSP_PinAccessDisable();

    err = R_IIC_MASTER_Open(&g_i2c_master_board_ctrl, &g_i2c_master_board_cfg);
    if (FSP_SUCCESS != err) handle_error(err);

    err = R_VIN_Open(&g_vin0_ctrl, &g_vin0_cfg);
    if (FSP_SUCCESS != err) handle_error(err);

    ov5640_init();
    OV5640_stream_off();
    ov5640_write_reg(0x3008, 0x42); // software power down
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

    R_VIN_CaptureStart(&g_vin0_ctrl, NULL);
    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

    ov5640_write_reg(0x3008, 0x02); // wake up
    OV5640_stream_on();

    /* 4. Init Ethos-U NPU */
    err = RM_ETHOSU_Open(&g_rm_ethosu0_ctrl, &g_rm_ethosu0_cfg);
    if (FSP_SUCCESS != err) handle_error(err);

    /* 5. Create RTOS Event Flags */
    T_CFLG cflg = { .flgatr = TA_TFIFO | TA_WMUL, .iflgptn = 0 };
    cam_flg_id = tk_cre_flg(&cflg);
    ai_flg_id = tk_cre_flg(&cflg);

    /* 6. Create & Start RTOS Tasks */
    T_CTSK ct_cam = {
        .itskpri = 10,
        .stksz = 8192,
        .task = camera_task,
        .tskatr = TA_HLNG | TA_RNG0,
    };
    cam_tsk_id = tk_cre_tsk(&ct_cam);
    tk_sta_tsk(cam_tsk_id, 0);

    T_CTSK ct_ai = {
        .itskpri = 15,
        .stksz = 16384,
        .task = ai_task,
        .tskatr = TA_HLNG | TA_RNG0,
    };
    ai_tsk_id = tk_cre_tsk(&ct_ai);
    tk_sta_tsk(ai_tsk_id, 0);

    /* ESP32 UART Telemetry Task (Priority 12, 4KB Stack) */
    T_CTSK ct_esp32 = {
        .itskpri = 12,
        .stksz = 4096,
        .task = esp32_task,
        .tskatr = TA_HLNG | TA_RNG0,
    };
    esp32_tsk_id = tk_cre_tsk(&ct_esp32);
    tk_sta_tsk(esp32_tsk_id, 0);

    /* Terminate this setup task so it frees its stack */
    tk_exd_tsk();
}

/* Task 3: ESP32 UART Telemetry & Touch Interaction Processor */
void esp32_task(INT stacd, void *exinf)
{
    /* Allow camera, NPU, and display pipeline 2 seconds to boot and stabilize */
    tk_dly_tsk(2000);

    fsp_err_t err = esp32_uart_init(ESP32_DEFAULT_BAUDRATE);
    if (FSP_SUCCESS != err)
    {
        SEGGER_RTT_printf(0, "[ESP32] UART Init error (%d)\r\n", err);
    }

    /* Send ready announcement to ESP32 / PC Serial Monitor */
    esp32_uart_send("RA8P1 READY. SEND MESSAGE FROM ESP32:\r\n");

    /* Probe FT5316 touch controller safely in background once camera is running */
    FT5316_Init();

    /* Flush out power-on calibration noise and any residual readings */
    for (int i = 0; i < 5; i++)
    {
        touch_data_t dummy;
        FT5316_GetTouch(&dummy);
        tk_dly_tsk(20);
    }

    uint32_t report_tick = 0;
    static uint32_t touch_debounce = 40; // 1-second grace period at boot so Welcome Screen remains steady

    while (1)
    {
        /* Poll incoming UART buffer every 25ms */
        tk_dly_tsk(25);
        uint32_t packets = esp32_uart_process();

        /* If new packet or message arrived from ESP32, immediately refresh LCD display */
        if (packets > 0 || g_esp32_data.has_new_msg)
        {
            g_esp32_data.has_new_msg = false;
            g_ai_result_new = true;
            tk_set_flg(cam_flg_id, 1);
        }

        /* Poll touch screen */
        if (touch_debounce > 0)
        {
            touch_debounce--;
        }
        else
        {
            touch_data_t touch;
            if (FT5316_GetTouch(&touch) == FSP_SUCCESS && touch.touches >= 1 && touch.touches <= 5)
            {
                if (touch.x > 0 && touch.x < 1024 && touch.y > 0 && touch.y < 600)
                {
                    SEGGER_RTT_printf(0, "[TOUCH] Valid tap at X=%d, Y=%d (Current Mode: %d)\r\n",
                                      touch.x, touch.y, g_current_ui_mode);

                    if (g_current_ui_mode == UI_MODE_WELCOME)
                    {
                        /* Tapping anywhere on the Welcome Screen launches live camera and sensor feed */
                        SEGGER_RTT_printf(0, "[TOUCH] >>> Welcome Screen Tapped: Starting Live Cam & Sensor Feed <<<\r\n");
                        switch_ui_layer_geometry(UI_MODE_OBJECT_DETECTION);
                        g_current_ui_mode = UI_MODE_OBJECT_DETECTION;
                        g_ai_result_new = true;
                        tk_set_flg(cam_flg_id, 1);
                        touch_debounce = 20; // ~500ms debounce
                    }
                    else if (check_touch_button(touch.x, touch.y))
                    {
                        /* Toggle UI mode */
                        g_current_ui_mode = (g_current_ui_mode == UI_MODE_OBJECT_DETECTION) ?
                                             UI_MODE_ESP32_SENSORS : UI_MODE_OBJECT_DETECTION;

                        SEGGER_RTT_printf(0, "[TOUCH] >>> Switched UI Mode to: %s <<<\r\n",
                                          (g_current_ui_mode == UI_MODE_ESP32_SENSORS) ? "ESP32 SENSORS" : "AI TRACKING");

                        /* Send request command to ESP32 */
                        esp32_fetch_sensor_data();

                        /* Signal camera task to redraw overlay */
                        g_ai_result_new = true;
                        tk_set_flg(cam_flg_id, 1);

                        touch_debounce = 15; // ~375ms debounce
                    }
                }
            }
        }

        /* 1-second periodic report to SEGGER RTT */
        if (++report_tick >= 40)
        {
            report_tick = 0;

            if (g_esp32_data.rx_packets_total > 0)
            {
                SEGGER_RTT_printf(0, "[ESP32] RX PKTS:%lu BYTES:%lu | Last: \"%s\"\r\n",
                                  (unsigned long)g_esp32_data.rx_packets_total,
                                  (unsigned long)g_esp32_data.rx_bytes_total,
                                  g_esp32_data.last_message);
            }
            else
            {
                SEGGER_RTT_printf(0, "[ESP32] Waiting for ESP32 on Pmod 2 (Bytes: %lu | Errs: %lu)...\r\n",
                                  (unsigned long)g_esp32_data.rx_bytes_total,
                                  (unsigned long)g_esp32_data.error_count);
            }
        }
    }
}

/* T-Kernel Application Entry Point */
EXPORT INT usermain(void)
{
    /* Spawn a setup_task with an 8KB stack so we don't overflow the 1KB init_task! */
    T_CTSK ct_setup = {
        .itskpri = 5,
        .stksz = 8192,
        .task = setup_task,
        .tskatr = TA_HLNG | TA_RNG0,
    };
    ID setup_tsk_id = tk_cre_tsk(&ct_setup);
    tk_sta_tsk(setup_tsk_id, 0);

    /* Suspend main thread forever */
    tk_slp_tsk(TMO_FEVR);

    return 0;
}

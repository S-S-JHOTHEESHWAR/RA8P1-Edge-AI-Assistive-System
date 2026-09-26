#include "hal_data.h"
#include <stdio.h>
#include <string.h>
#include "camera_control.h"
#include "common_util.h"
#include "display_layer.h"
#include "time_counter.h"
#include "display_layer_config.h"
#include "ai_application_config.h"
#include "user_font_body/user_font_body_if.h"

#include "../esp32/esp32_uart.h"

#define MAX_STR_LEN 24
#define INFERENCE_ROW_HEIGHT    55 // Spacing for progress bars
#define TEXT_AREA_WIDTH         320
#define TEXT_AREA_HEIGHT        560
#define PERCENTAGE_OFF          240 // Right-aligned percentage offset

volatile ui_mode_t g_current_ui_mode = UI_MODE_WELCOME;

void do_image_classification_screen(bool ai_result_new);
display_runtime_cfg_t glcd_layer_change_1;
display_runtime_cfg_t glcd_layer_change_2;

static void process_str(const char* input, char* output, int max_len);
static void print_inf_time(void);
static void draw_toggle_button(d2_device *handle, int x, int y, int w, int h, const char *text, d2_color bg_color);
static void render_esp32_sensor_view(d2_device *handle);

static bool overlay_drawn = false;
static char local_str[5][32] = {0};
static char local_prob[5][8] = {0};

const char* coco_labels[] = {
    "person", "bicycle", "car", "motorcycle", "airplane", "bus", "train", "truck", "boat", "traffic light",
    "fire hydrant", "stop sign", "parking meter", "bench", "bird", "cat", "dog", "horse", "sheep", "cow",
    "elephant", "bear", "zebra", "giraffe", "backpack", "umbrella", "handbag", "tie", "suitcase", "frisbee",
    "skis", "snowboard", "sports ball", "kite", "baseball bat", "baseball glove", "skateboard", "surfboard",
    "tennis racket", "bottle", "wine glass", "cup", "fork", "knife", "spoon", "bowl", "banana", "apple",
    "sandwich", "orange", "broccoli", "carrot", "hot dog", "pizza", "donut", "cake", "chair", "couch",
    "potted plant", "bed", "dining table", "toilet", "tv", "laptop", "mouse", "remote", "keyboard", "cell phone",
    "microwave", "oven", "toaster", "sink", "refrigerator", "book", "clock", "vase", "scissors", "teddy bear",
    "hair drier", "toothbrush"
};

// =========================================================================
// MODERN UI PRIMITIVES (CustomTkinter / Fluent Design Style)
// =========================================================================

static void draw_rounded_rect(d2_device *handle, int x, int y, int w, int h, int r, d2_color color)
{
    d2_setcolor(handle, 0, color);
    d2_renderbox(handle, (x + r) << 4, y << 4, (w - 2 * r) << 4, h << 4);
    d2_renderbox(handle, x << 4, (y + r) << 4, w << 4, (h - 2 * r) << 4);
    d2_rendercircle(handle, (x + r) << 4,         (y + r) << 4,         r << 4, 0);
    d2_rendercircle(handle, (x + w - r) << 4,     (y + r) << 4,         r << 4, 0);
    d2_rendercircle(handle, (x + r) << 4,         (y + h - r) << 4,     r << 4, 0);
    d2_rendercircle(handle, (x + w - r) << 4,     (y + h - r) << 4,     r << 4, 0);
}

static void draw_ctk_panel(d2_device *handle, int x, int y, int w, int h, int r) {
    // Enable Alpha Blending to draw translucent drop shadows
    d2_setblendmode(handle, d2_bm_alpha, d2_bm_one_minus_alpha);

    // Draw 2 layers of soft drop shadows (expanding outwards)
    d2_setalpha(handle, 40);
    draw_rounded_rect(handle, x - 2, y + 2, w + 4, h + 4, r + 2, 0xFF000000);
    d2_setalpha(handle, 20);
    draw_rounded_rect(handle, x - 4, y + 4, w + 8, h + 8, r + 4, 0xFF000000);

    // Restore opacity
    d2_setalpha(handle, 255);

    // Main Panel Card (Sleek Dark Blue/Gray)
    draw_rounded_rect(handle, x, y, w, h, r, 0xFF2A2D3E);
}

static void draw_capsule_bar(d2_device *handle, int x, int y, int w, int h, d2_color color)
{
    if (w <= 0 || h <= 0) return;
    int r = h / 2;
    d2_setcolor(handle, 0, color);
    if (w > 2 * r) {
        d2_renderbox(handle, (x + r) << 4, y << 4, (w - 2 * r) << 4, h << 4);
        d2_rendercircle(handle, (x + r) << 4, (y + r) << 4, r << 4, 0);
        d2_rendercircle(handle, (x + w - r) << 4, (y + r) << 4, r << 4, 0);
    } else {
        d2_rendercircle(handle, (x + r) << 4, (y + r) << 4, r << 4, 0);
    }
}

static void draw_ctk_progressbar(d2_device *handle, int x, int y, int w, int h, float percentage, d2_color accent_color)
{
    // Background track (Very dark gray)
    draw_capsule_bar(handle, x, y, w, h, 0xFF1C1E29);

    // Progress fill with smooth capsule ends
    int fill_w = (int)((w * percentage) / 100.0f);
    if (fill_w > 0) {
        if (fill_w > w) fill_w = w;
        draw_capsule_bar(handle, x, y, fill_w, h, accent_color);
    }
}

static void draw_toggle_button(d2_device *handle, int x, int y, int w, int h, const char *text, d2_color bg_color)
{
    // Button drop shadow
    d2_setblendmode(handle, d2_bm_alpha, d2_bm_one_minus_alpha);
    d2_setalpha(handle, 40);
    draw_rounded_rect(handle, x - 1, y + 2, w + 2, h + 2, 6, 0xFF000000);
    d2_setalpha(handle, 255);

    // Button body
    draw_rounded_rect(handle, x, y, w, h, 6, bg_color);

    // Button text in crisp white
    print_user_font(handle, x + 8, y + 4, 0.45f, text);
}

bool check_touch_button(uint16_t touch_x, uint16_t touch_y)
{
    /* Toggle between AI Vision and ESP32 Sensor Dashboard */
    if (touch_x >= 550 && touch_y >= 160 && touch_y <= 320)
    {
        return true;
    }
    return false;
}

static void print_inf_time(void)
{
    uint32_t time = (uint32_t)(application_processing_time.ai_inference_time_ms);
    char time_str[8] = {'0', '0', '0', '0', ' ', 'm', 's', '\0'};
    time_str[0] += (char)((time / 1000) % 10);
    time_str[1] += (char)((time / 100) % 10);
    time_str[2] += (char)((time / 10) % 10);
    time_str[3] += (char)(time % 10);

    // Latency number in Electric Cyan
    print_user_font_colored(d2_handle, 80, 155, 0.55f, 0xFF00E5FF, (char*)time_str);

    // Draw a visual representation of latency (Max 200ms = 100% full bar)
    float latency_pct = (time / 200.0f) * 100.0f;
    if (latency_pct > 100.0f) latency_pct = 100.0f;

    d2_color latency_color = (latency_pct > 50.0f) ? 0xFFFF3333 : 0xFF00FFCC; // Red if slow, Cyan if fast
    draw_ctk_progressbar(d2_handle, 165, 158, 120, 10, latency_pct, latency_color);
}

static void process_str(const char* input, char* output, int max_len) {
    int i;
    for (i = 0; input[i] != '\0' && i < max_len - 1; i++) {
        if (input[i] == ',') break;
        output[i] = input[i];
    }
    output[i] = '\0';

    // Capitalize first letter and any letter after space (e.g. "cell phone" -> "Cell Phone")
    if (output[0] >= 'a' && output[0] <= 'z') {
        output[0] = (char)(output[0] - 32);
    }
    for (int j = 1; output[j] != '\0'; j++) {
        if (output[j-1] == ' ' && output[j] >= 'a' && output[j] <= 'z') {
            output[j] = (char)(output[j] - 32);
        }
    }
}

static void render_esp32_sensor_view(d2_device *handle)
{
    char buf[48];

    // Card Header & Return Button
    print_user_font(handle, 25, 222, 0.55f, "ESP32 Sensors");
    draw_toggle_button(handle, 195, 218, 105, 26, "AI VISION", 0xFF107C41);

    // 1. SCD40 Section: CO2 Concentration
    print_user_font_colored(handle, 25, 258, 0.48f, 0xFF8899AA, "SCD40 Air Quality");

    uint16_t co2 = g_esp32_data.co2;
    d2_color co2_color;
    const char *air_quality_tag;

    if (co2 == 0) {
        snprintf(buf, sizeof(buf), "CO2: Waiting...");
        co2_color = 0xFF8899AA;
        air_quality_tag = "Init";
    } else if (co2 < 800) {
        snprintf(buf, sizeof(buf), "CO2: %u ppm", co2);
        co2_color = 0xFF00FF88; // Emerald Green (Good)
        air_quality_tag = "Good";
    } else if (co2 < 1200) {
        snprintf(buf, sizeof(buf), "CO2: %u ppm", co2);
        co2_color = 0xFFFFD000; // Amber Gold (Moderate)
        air_quality_tag = "Fair";
    } else {
        snprintf(buf, sizeof(buf), "CO2: %u ppm", co2);
        co2_color = 0xFFFF4444; // Coral Red (High)
        air_quality_tag = "High";
    }

    print_user_font_colored(handle, 25, 282, 0.55f, co2_color, buf);
    print_user_font_colored(handle, 235, 282, 0.50f, co2_color, air_quality_tag);

    // CO2 Level Bar (Max 2000 ppm = 100%)
    float co2_pct = (co2 > 0) ? ((float)co2 / 2000.0f) * 100.0f : 5.0f;
    if (co2_pct > 100.0f) co2_pct = 100.0f;
    draw_ctk_progressbar(handle, 25, 308, 260, 8, co2_pct, co2_color);

    // Temperature & Humidity
    snprintf(buf, sizeof(buf), "Temp: %.1f C   Hum: %.1f%%",
             g_esp32_data.temperature, g_esp32_data.humidity);
    print_user_font_colored(handle, 25, 326, 0.50f, 0xFF00E5FF, buf);

    // 2. MPU9250 Motion & Orientation Section
    print_user_font_colored(handle, 25, 360, 0.48f, 0xFF8899AA, "MPU9250 Motion (IMU)");

    snprintf(buf, sizeof(buf), "Accel X:%.2f Y:%.2f Z:%.2f g",
             g_esp32_data.accel_x, g_esp32_data.accel_y, g_esp32_data.accel_z);
    print_user_font(handle, 25, 382, 0.48f, buf);

    snprintf(buf, sizeof(buf), "Gyro  X:%.1f Y:%.1f Z:%.1f d/s",
             g_esp32_data.gyro_x, g_esp32_data.gyro_y, g_esp32_data.gyro_z);
    print_user_font_colored(handle, 25, 406, 0.48f, 0xFFCCDDEE, buf);

    // 3. Link Telemetry
    snprintf(buf, sizeof(buf), "Link: %s   Pkts: %lu",
             g_esp32_data.is_connected ? "ONLINE" : "OFFLINE",
             (unsigned long)g_esp32_data.rx_packets_total);
    d2_color link_color = g_esp32_data.is_connected ? 0xFF00FF88 : 0xFFFF4444;
    print_user_font_colored(handle, 25, 436, 0.45f, link_color, buf);

    // 4. Live Message from ESP32
    print_user_font_colored(handle, 25, 460, 0.45f, 0xFF8899AA, "Last Message:");
    print_user_font_colored(handle, 25, 482, 0.45f, 0xFF00FF88, g_esp32_data.last_message);

    // Action button
    draw_toggle_button(handle, 25, 514, 260, 26, "  FETCH SENSOR DATA", 0xFF0078D4);
}

void do_image_classification_screen(bool ai_result_new)
{
    if (g_current_ui_mode == UI_MODE_WELCOME)
    {
        return;
    }

    d2_point vpos = 258; // Starting Y for detections
    d2_point hpos = 25;

    d2_framebuffer(d2_handle, (void *)fb_foreground, TEXT_AREA_WIDTH, TEXT_AREA_WIDTH, TEXT_AREA_HEIGHT, d2_mode_rgb565);
    d2_startframe(d2_handle);

    // Enable Anti-Aliasing for perfectly smooth corners
    d2_setantialiasing(d2_handle, 1);

    if (!overlay_drawn)
    {
        // 1. Draw Global Background (Deep OLED Black/Blue)
        d2_setcolor(d2_handle, 0, 0xFF12141C);
        d2_renderbox(d2_handle, 0, 0, TEXT_AREA_WIDTH << 4, TEXT_AREA_HEIGHT << 4);

        // 2. Draw Floating Panels (Drop Shadows + Rounded Corners)
        draw_ctk_panel(d2_handle, 10, 10, 300, 80, 12);  // Header Panel
        draw_ctk_panel(d2_handle, 10, 105, 300, 90, 12); // Performance Panel
        draw_ctk_panel(d2_handle, 10, 210, 300, 340, 12); // Detections / Telemetry Panel

        // 3. Draw Static Text inside Panels using QuickStart user_font_body
        print_user_font(d2_handle, 25, 25, 0.70f, "EDGESIGHT OS");

        char init_hdr[48];
        if (g_esp32_data.co2 > 0)
        {
            snprintf(init_hdr, sizeof(init_hdr), "CO2:%uppm  %.1fC  %.0f%%",
                     g_esp32_data.co2, g_esp32_data.temperature, g_esp32_data.humidity);
            print_user_font_colored(d2_handle, 25, 56, 0.44f, 0xFF00FF88, init_hdr);
        }
        else
        {
            snprintf(init_hdr, sizeof(init_hdr), "ESP: %s", g_esp32_data.last_message);
            print_user_font_colored(d2_handle, 25, 56, 0.45f, 0xFF00FF88, init_hdr);
        }

        print_user_font(d2_handle, 25, 120, 0.55f, "Ethos-U55 NPU Status");
        print_user_font(d2_handle, 25, 155, 0.55f, "Time:");
        print_user_font_colored(d2_handle, 80, 155, 0.55f, 0xFF8899AA, "---- ms");

        print_user_font(d2_handle, 25, 222, 0.55f, "Active Tracking");
        draw_toggle_button(d2_handle, 175, 218, 125, 26, "ESP32 SENSORS", 0xFF0078D4);

        print_user_font_colored(d2_handle, 25, 252, 0.48f, 0xFF00E5FF, "ESP MSG:");
        print_user_font_colored(d2_handle, 110, 252, 0.48f, 0xFF00FF88, g_esp32_data.last_message);

        print_user_font_colored(d2_handle, 25, 282, 0.50f, 0xFF8899AA, "Scanning for targets...");

        R_IOPORT_PinWrite(&g_ioport_ctrl, DISP_BLEN, BSP_IO_LEVEL_HIGH);
        overlay_drawn = true;
    }
    else if (ai_result_new)
    {
        // Erase old latency area cleanly
        d2_setcolor(d2_handle, 0, 0xFF2A2D3E);
        d2_renderbox(d2_handle, 80 << 4, 150 << 4, 210 << 4, 30 << 4);
        print_inf_time();

        // Update Header Panel subtitle with live ESP32 message or SCD40 telemetry
        d2_setcolor(d2_handle, 0, 0xFF2A2D3E);
        d2_renderbox(d2_handle, 20 << 4, 52 << 4, 275 << 4, 28 << 4);
        char header_buf[48];
        if (g_esp32_data.co2 > 0)
        {
            snprintf(header_buf, sizeof(header_buf), "CO2:%uppm  %.1fC  %.0f%%",
                     g_esp32_data.co2, g_esp32_data.temperature, g_esp32_data.humidity);
            print_user_font_colored(d2_handle, 25, 56, 0.44f, 0xFF00FF88, header_buf);
        }
        else
        {
            snprintf(header_buf, sizeof(header_buf), "ESP: %s", g_esp32_data.last_message);
            print_user_font_colored(d2_handle, 25, 56, 0.45f, 0xFF00FF88, header_buf);
        }

        // Cleanly erase the entire 3rd card interior before drawing active view
        d2_setcolor(d2_handle, 0, 0xFF2A2D3E);
        d2_renderbox(d2_handle, 15 << 4, 215 << 4, 290 << 4, 330 << 4);

        if (g_current_ui_mode == UI_MODE_ESP32_SENSORS)
        {
            // Render Live ESP32 Dual-Sensor Dashboard
            render_esp32_sensor_view(d2_handle);
        }
        else
        {
            // Render Vision AI Object Detection View
            print_user_font(d2_handle, 25, 222, 0.55f, "Active Tracking");
            draw_toggle_button(d2_handle, 175, 218, 125, 26, "ESP32 SENSORS", 0xFF0078D4);

            if (g_esp32_data.co2 > 0)
            {
                // Prominent SCD40 Air Quality Pill
                char scd_buf[32];
                d2_color scd_color = (g_esp32_data.co2 < 800) ? 0xFF00FF88 :
                                     ((g_esp32_data.co2 < 1200) ? 0xFFFFD000 : 0xFFFF4444);
                snprintf(scd_buf, sizeof(scd_buf), "CO2: %u ppm", g_esp32_data.co2);
                print_user_font_colored(d2_handle, 25, 248, 0.50f, scd_color, scd_buf);

                char th_buf[32];
                snprintf(th_buf, sizeof(th_buf), "%.1f C  %.0f%%", g_esp32_data.temperature, g_esp32_data.humidity);
                print_user_font_colored(d2_handle, 175, 248, 0.45f, 0xFF00E5FF, th_buf);

                float co2_bar = (float)g_esp32_data.co2 / 2000.0f * 100.0f;
                if (co2_bar > 100.0f) co2_bar = 100.0f;
                draw_ctk_progressbar(d2_handle, 25, 270, 260, 6, co2_bar, scd_color);

                vpos = 286; // Start detections below SCD40 gauge
            }
            else
            {
                // Prominent ESP Message banner inside center panel
                print_user_font_colored(d2_handle, 25, 252, 0.48f, 0xFF00E5FF, "ESP MSG:");
                print_user_font_colored(d2_handle, 110, 252, 0.48f, 0xFF00FF88, g_esp32_data.last_message);
                vpos = 282;
            }

            bool any_detection = false;
            for (uint8_t i = 0; i < AI_MAX_DETECTION_NUM; i++)
            {
                char processed_str[MAX_STR_LEN] = {0};

                if (g_ai_detection[i].m_w > 0)
                {
                    any_detection = true;
                    int cls_id = g_ai_detection[i].category;
                    if (cls_id < 0 || cls_id >= 80) cls_id = 0;

                    process_str(coco_labels[cls_id], processed_str, MAX_STR_LEN);
                    snprintf(local_str[i], sizeof(local_str[i]), "%s", processed_str);

                    float prob_float = g_ai_detection[i].prob * 100.0f;
                    if (prob_float > 99.0f) prob_float = 99.0f;
                    if (prob_float < 0.0f)  prob_float = 0.0f;
                    snprintf(local_prob[i], sizeof(local_prob[i]), "%2d%%", (int)prob_float);

                    // High confidence: Cyan, Medium: Amber Gold, Low: Coral Red
                    d2_color accent_color = (prob_float >= 75.0f) ? 0xFF00E5FF :
                                            ((prob_float >= 50.0f) ? 0xFFFFD000 : 0xFFFF6B6B);

                    // 1. Class Name (Crisp White)
                    print_user_font(d2_handle, hpos, vpos + INFERENCE_ROW_HEIGHT*i, 0.55f, (char*)local_str[i]);

                    // 2. Accuracy Percentage (Accent Color)
                    print_user_font_colored(d2_handle, PERCENTAGE_OFF, vpos + INFERENCE_ROW_HEIGHT*i, 0.55f, accent_color, (char*)local_prob[i]);

                    // 3. Dynamic Smooth Capsule Progress Bar
                    draw_ctk_progressbar(d2_handle, 25, vpos + INFERENCE_ROW_HEIGHT*i + 26, 260, 8, prob_float, accent_color);
                }
            }

            if (!any_detection)
            {
                print_user_font_colored(d2_handle, 25, vpos, 0.50f, 0xFF8899AA, "Scanning for targets...");
            }
        }
    }

    d2_endframe(d2_handle);
    SCB_CleanDCache_by_Addr((uint32_t *)fb_foreground, TEXT_AREA_WIDTH * TEXT_AREA_HEIGHT * 2);
    (void)R_GLCDC_LayerChange(&g_plcd_display.p_ctrl, &glcd_layer_change_2, DISPLAY_FRAME_LAYER_2);
}

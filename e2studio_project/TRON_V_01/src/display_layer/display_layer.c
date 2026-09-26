/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#include "hal_data.h"
#include "display_layer.h"
#include "common_util.h"
#include "camera_control.h"
#include "time_counter.h"

#include "display_layer_config.h"
#include "image.h"
volatile bool g_vsync_flag = false;

uint8_t fb_welcome[1024 * 600 * 2] BSP_PLACE_IN_SECTION(".sdram_noinit");

/***************************************************************************************************************************
 * Macro definitions
 ***************************************************************************************************************************/

/***************************************************************************************************************************
 * Typedef definitions
 ***************************************************************************************************************************/

/***************************************************************************************************************************
 * Imported global variables and functions (from other files)
 ***************************************************************************************************************************/

 extern display_runtime_cfg_t glcd_layer_change_2;
 extern display_runtime_cfg_t glcd_layer_change_1;


 /***************************************************************************************************************************
  * Private global variables and functions
  ***************************************************************************************************************************/
 static uint16_t g_hz_size, g_vr_size;
 static uint32_t last_lcd_glcdc_frame_end = 0;


 /**********************************************************************************************************************
  * Function Name: drw_init
  * Description  : Initialize the DRW
  * Argument     : none
  * Return Value : none
  *********************************************************************************************************************/
fsp_err_t drw_init(void)
{
    /* Initialize D/AVE 2D driver */
     d2_handle = d2_opendevice(0);
     d2_inithw(d2_handle, 0);

     /* Clear both buffers */
     d2_framebuffer(d2_handle, fb_background, 640, 640, 480, DISPLAY_SCREEN_BUFF_D2_COLOR_CODE);
     d2_clear(d2_handle, 0x00000000);

     /* Set various D2 parameters */
     d2_setblendmode(d2_handle, d2_bm_alpha, d2_bm_one_minus_alpha);
     d2_setalphamode(d2_handle, d2_am_constant);
     d2_setalpha(d2_handle, 0xff);
     d2_setantialiasing(d2_handle, 1);
     d2_setlinecap(d2_handle, d2_lc_butt);
     d2_setlinejoin(d2_handle, d2_lj_none);

     return FSP_SUCCESS;
}



/**********************************************************************************************************************
 * Function Name: glcdc_vsync_isr
 * Description  : GLCDC Interrupt Callback
 * Argument     : p_args
 * Return Value : none
 *********************************************************************************************************************/
void glcdc_vsync_isr(display_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    if (DISPLAY_EVENT_LINE_DETECTION & p_args->event )
    {
        application_processing_time.lcd_display_update_refresh_ms = TimeCounter_CountValueConvertToMs(last_lcd_glcdc_frame_end, TimeCounter_CurrentCountGet());
        last_lcd_glcdc_frame_end = TimeCounter_CurrentCountGet();
        g_vsync_flag = true; // Tell bare metal loop vsync occurred
    }
}

/**********************************************************************************************************************
 * Function Name: initialise_display
 * Description  : Initializes GLCDC and Drw engines
 * Argument     : none
 * Return Value : none
 *********************************************************************************************************************/
fsp_err_t initialise_display(void)
{
    fsp_err_t result;

    R_BSP_PinAccessEnable();

    /* Reset Display - active low */
    /* Note: Please update wait periods according to LCD controller specification */
    R_IOPORT_PinWrite(&g_ioport_ctrl, DISP_RESET, BSP_IO_LEVEL_LOW);
    R_BSP_SoftwareDelay(10, BSP_DELAY_UNITS_MICROSECONDS);
    R_IOPORT_PinWrite(&g_ioport_ctrl, DISP_RESET, BSP_IO_LEVEL_HIGH);
    R_BSP_SoftwareDelay(120, BSP_DELAY_UNITS_MILLISECONDS);


    /* Initialize GLCDC driver */
    result = R_GLCDC_Open(&g_plcd_display_ctrl, &g_plcd_display_cfg);
    if(FSP_SUCCESS != result)
    {
        handle_error(VISION_AI_APP_ERR_GLCDC_OPEN);
        return result;
    }

    /* Start GLCDC display output */
    result = R_GLCDC_Start(&g_plcd_display_ctrl);

    /* Handle error */
    if(FSP_SUCCESS != result)
    {
        /* GLCDC initialization failed  */
        handle_error(VISION_AI_APP_ERR_GLCDC_START);
        return result;
    }

    R_BSP_SoftwareDelay(40, BSP_DELAY_UNITS_MILLISECONDS);

    R_BSP_PinAccessDisable();

    glcd_layer_change_1.layer = g_plcd_display.p_cfg->layer[0];
    glcd_layer_change_2.layer = g_plcd_display.p_cfg->layer[1];

    /* Turn on LCD backlight immediately so Welcome screen is visible from moment 0 */
    R_BSP_PinAccessEnable();
    R_IOPORT_PinWrite(&g_ioport_ctrl, DISP_BLEN, BSP_IO_LEVEL_HIGH);
    R_BSP_PinAccessDisable();

    /* Boot up displaying the 1024x600 Welcome Splash Screen */
    switch_ui_layer_geometry(UI_MODE_WELCOME);

    return FSP_SUCCESS;
}

void switch_ui_layer_geometry(ui_mode_t mode)
{
    if (mode == UI_MODE_WELCOME)
    {
        /* Copy 1024x600 image from OSPI Flash into SDRAM buffer */
        memcpy(fb_welcome, image_data.pixel_data, 1024 * 600 * 2);
        SCB_CleanDCache_by_Addr((uint32_t *)fb_welcome, 1024 * 600 * 2);

        /* Configure Layer 1 for full 1024x600 Welcome Screen */
        glcd_layer_change_1.layer.coordinate.x = 0;
        glcd_layer_change_1.layer.coordinate.y = 0;
        glcd_layer_change_1.input.hsize = 1024;
        glcd_layer_change_1.input.vsize = 600;
        glcd_layer_change_1.input.hstride = 1024;
        glcd_layer_change_1.input.format = DISPLAY_IN_FORMAT_16BITS_RGB565;
        glcd_layer_change_1.input.p_base = (uint32_t *)&fb_welcome[0];
        (void)R_GLCDC_LayerChange(&g_plcd_display_ctrl, &glcd_layer_change_1, DISPLAY_FRAME_LAYER_1);

        /* Move Layer 2 off-screen so overlay is hidden during welcome */
        glcd_layer_change_2.layer.coordinate.x = (int16_t)1024;
        glcd_layer_change_2.layer.coordinate.y = (int16_t)600;
        (void)R_GLCDC_LayerChange(&g_plcd_display_ctrl, &glcd_layer_change_2, DISPLAY_FRAME_LAYER_2);
    }
    else
    {
        /* UI_MODE_OBJECT_DETECTION: Live Camera (640x480) + AI Detections & Sensor Feed (320x560) */
        glcd_layer_change_1.layer.coordinate.x = 35;
        glcd_layer_change_1.layer.coordinate.y = 65;
        glcd_layer_change_1.input.hsize = 640;
        glcd_layer_change_1.input.vsize = 480;
        glcd_layer_change_1.input.hstride = ((((640 * DISPLAY_BITS_PER_PIXEL_INPUT0 + 0x1FF) >> 9) << 6)*8/(16));
        glcd_layer_change_1.input.format = DISPLAY_IN_FORMAT_16BITS_RGB565;
        glcd_layer_change_1.input.p_base = (uint32_t *)&fb_background[0];
        (void)R_GLCDC_LayerChange(&g_plcd_display_ctrl, &glcd_layer_change_1, DISPLAY_FRAME_LAYER_1);

        /* Layer 2: Live AI Detections + SCD40 Sensor Overlay (320x560) at (700, 40) */
        glcd_layer_change_2.layer.coordinate.x = (int16_t)700;
        glcd_layer_change_2.layer.coordinate.y = (int16_t)40;
        glcd_layer_change_2.input.hsize = 320;
        glcd_layer_change_2.input.vsize = 560;
        glcd_layer_change_2.input.hstride = ((((320 * DISPLAY_BITS_PER_PIXEL_INPUT1 + 0x1FF) >> 9) << 6)*8/(16));
        glcd_layer_change_2.input.format = DISPLAY_IN_FORMAT_16BITS_RGB565;
        glcd_layer_change_2.input.p_base = (uint32_t *)&fb_foreground[0];
        (void)R_GLCDC_LayerChange(&g_plcd_display_ctrl, &glcd_layer_change_2, DISPLAY_FRAME_LAYER_2);
    }
}



/*********************************************************************************************************************
 *  Start a new frame with the current draw buffer.
 *  @param[IN]   None
 *  @retval      None
***********************************************************************************************************************/
void graphics_start_frame()
{
    /* Start a new display list */
    d2_startframe(d2_handle);


}

/*********************************************************************************************************************
 *  Wait the current frame to end and swap the framebuffer
 *  @param[IN]   None
 *  @retval      None
***********************************************************************************************************************/
void graphics_end_frame()
{
    /* End the current display list */
    d2_endframe(d2_handle);
    R_GLCDC_BufferChange(&g_plcd_display_ctrl, (uint8_t * const) fb_background, DISPLAY_FRAME_LAYER_1);

}


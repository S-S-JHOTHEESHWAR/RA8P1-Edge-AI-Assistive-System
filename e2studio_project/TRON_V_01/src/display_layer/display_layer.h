/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/**********************************************************************************************************************
 * File Name    : display_layer.h
 * Version      : .
 * Description  : .
 *********************************************************************************************************************/
#ifndef __DISPLAY_LAYER_H__
#define __DISPLAY_LAYER_H__

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "hal_data.h"

/***************************************************************************************************************************
 * Exported global variables and functions (to be accessed by other files)
 ***************************************************************************************************************************/
extern d2_device * d2_handle;


typedef enum {
    UI_MODE_WELCOME          = 0,
    UI_MODE_OBJECT_DETECTION = 1,
    UI_MODE_ESP32_SENSORS    = 2
} ui_mode_t;

extern volatile ui_mode_t g_current_ui_mode;
extern uint8_t fb_welcome[1024 * 600 * 2];

fsp_err_t drw_init(void);
fsp_err_t initialise_display(void);
void display_image_buffer_initialize(void);
void graphics_start_frame(void);
void graphics_end_frame(void);

void do_image_classification_screen(bool ai_result_new);
bool check_touch_button(uint16_t touch_x, uint16_t touch_y);
void switch_ui_layer_geometry(ui_mode_t mode);

#endif /*__DISPLAY_LAYER_H__*/

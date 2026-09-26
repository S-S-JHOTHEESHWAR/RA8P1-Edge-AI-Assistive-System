/*
 * Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _R_TYPEDEFS_H_
#define _R_TYPEDEFS_H_

#include <stdint.h>
#include <stdbool.h>

typedef char         char_t;
typedef int          int_t;
typedef unsigned int bool_t;

typedef float        float32_t;
typedef double       float64_t;

typedef struct
{
    uint16_t       width;
    uint16_t       height;
    uint16_t       offset;
    uint16_t       bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
    uint8_t        pixel_data[26 * 34 * 2 + 1];
} st_font_body_rgb565_t;

typedef struct
{
    uint16_t       width;
    uint16_t       height;
    uint16_t       offset;
    uint16_t       bytes_per_pixel;
    uint8_t        pixel_data[40 * 48 * 2 + 1];
} st_font_title_rgb565_t;

#endif /* _R_TYPEDEFS_H_ */

/*
 * Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_data.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

#include "r_typedefs.h"
#include "user_font_body_if.h"

#if defined(__GNUC__) || defined(__clang__)
#define BSP_ALIGN_VARIABLE(x) __attribute__((aligned(x)))
#else
#define BSP_ALIGN_VARIABLE(x)
#endif

#define FONT_TOTAL_CHARS    (76)
#define FONT_CHAR_WIDTH     (26)
#define FONT_CHAR_HEIGHT    (34)
#define FONT_CHAR_PIXELS    (FONT_CHAR_WIDTH * FONT_CHAR_HEIGHT)

/* Alpha8 font cache: each character occupies 884 bytes of opacity data.
 * Background pixels have Alpha = 0 (100% transparent).
 * Text stroke pixels have Alpha = 255 (opaque), with smooth antialiased edges.
 */
static uint8_t s_font_alpha8_cache[FONT_TOTAL_CHARS][FONT_CHAR_PIXELS] BSP_ALIGN_VARIABLE(8);
static bool    s_font_cached[FONT_TOTAL_CHARS] = { false };

static const st_font_body_rgb565_t *g_user_font_body_uc_tbl[26] =
{
    &g_user_font_body_uc_a, // A
    &g_user_font_body_uc_b, // B
    &g_user_font_body_uc_c, // C
    &g_user_font_body_uc_d, // D
    &g_user_font_body_uc_e, // E
    &g_user_font_body_uc_f, // F
    &g_user_font_body_uc_g, // G
    &g_user_font_body_uc_h, // H
    &g_user_font_body_uc_i, // I
    &g_user_font_body_uc_j, // J
    &g_user_font_body_uc_k, // K
    &g_user_font_body_uc_l, // L
    &g_user_font_body_uc_m, // M
    &g_user_font_body_uc_n, // N
    &g_user_font_body_uc_o, // O
    &g_user_font_body_uc_p, // P
    &g_user_font_body_uc_q, // Q
    &g_user_font_body_uc_r, // R
    &g_user_font_body_uc_s, // S
    &g_user_font_body_uc_t, // T
    &g_user_font_body_uc_u, // U
    &g_user_font_body_uc_v, // V
    &g_user_font_body_uc_w, // W
    &g_user_font_body_uc_x, // X
    &g_user_font_body_uc_y, // Y
    &g_user_font_body_uc_z  // Z
};

static const st_font_body_rgb565_t *g_user_font_body_lc_tbl[26] =
{
    &g_user_font_body_lc_a, // a
    &g_user_font_body_lc_b, // b
    &g_user_font_body_lc_c, // c
    &g_user_font_body_lc_d, // d
    &g_user_font_body_lc_e, // e
    &g_user_font_body_lc_f, // f
    &g_user_font_body_lc_g, // g
    &g_user_font_body_lc_h, // h
    &g_user_font_body_lc_i, // i
    &g_user_font_body_lc_j, // j
    &g_user_font_body_lc_k, // k
    &g_user_font_body_lc_l, // l
    &g_user_font_body_lc_m, // m
    &g_user_font_body_lc_n, // n
    &g_user_font_body_lc_o, // o
    &g_user_font_body_lc_p, // p
    &g_user_font_body_lc_q, // q
    &g_user_font_body_lc_r, // r
    &g_user_font_body_lc_s, // s
    &g_user_font_body_lc_t, // t
    &g_user_font_body_lc_u, // u
    &g_user_font_body_lc_v, // v
    &g_user_font_body_lc_w, // w
    &g_user_font_body_lc_x, // x
    &g_user_font_body_lc_y, // y
    &g_user_font_body_lc_z  // z
};

static const st_font_body_rgb565_t *g_user_font_body_num_tbl[10] =
{
    &g_user_font_body_0, // 0
    &g_user_font_body_1, // 1
    &g_user_font_body_2, // 2
    &g_user_font_body_3, // 3
    &g_user_font_body_4, // 4
    &g_user_font_body_5, // 5
    &g_user_font_body_6, // 6
    &g_user_font_body_7, // 7
    &g_user_font_body_8, // 8
    &g_user_font_body_9  // 9
};

static int get_char_index(char c)
{
    if ((c >= 'A') && (c <= 'Z')) return (int)(c - 'A');
    if ((c >= 'a') && (c <= 'z')) return 26 + (int)(c - 'a');
    if ((c >= '0') && (c <= '9')) return 52 + (int)(c - '0');

    switch (c)
    {
        case ' ':  return 62;
        case '-':  return 63;
        case '&':  return 64;
        case '(':  return 65;
        case ')':  return 66;
        case '[':  return 67;
        case ']':  return 68;
        case '\'': return 69;
        case ':':  return 70;
        case ',':  return 71;
        case '%':  return 72;
        case '/':  return 73;
        case '.':  return 74;
        case '_':  return 75;
        default:   return 62;
    }
}

static const st_font_body_rgb565_t * select_bitmap(char character)
{
    if ((character >= 'A') && (character <= 'Z'))
    {
        return g_user_font_body_uc_tbl[character - 'A'];
    }

    if ((character >= 'a') && (character <= 'z'))
    {
        return g_user_font_body_lc_tbl[character - 'a'];
    }

    if ((character >= '0') && (character <= '9'))
    {
        return g_user_font_body_num_tbl[character - '0'];
    }

    switch (character)
    {
        case ' ':  return &g_user_font_body_space;
        case '-':  return &g_user_font_body_minus;
        case '&':  return &g_user_font_body_and;
        case '(':  return &g_user_font_body_open_curved;
        case ')':  return &g_user_font_body_closed_curved;
        case '[':  return &g_user_font_body_open_square;
        case ']':  return &g_user_font_body_closed_square;
        case '\'': return &g_user_font_body_degrees;
        case ':':  return &g_user_font_body_colon;
        case ',':  return &g_user_font_body_comma;
        case '%':  return &g_user_font_body_percent;
        case '/':  return &g_user_font_body_slash;
        case '.':  return &g_user_font_body_full_stop;
        case '_':  return &g_user_font_body_underscore;
        default:   return &g_user_font_body_space;
    }
}

/* Converts RGB565 character bitmap to Alpha8 opacity map on demand.
 * 0x0000 background becomes Alpha = 0 (100% transparent!).
 * Non-zero stroke pixels become proportional opacity (0..255).
 */
static const uint8_t * get_char_alpha8(char c, const st_font_body_rgb565_t **out_image)
{
    int idx = get_char_index(c);
    const st_font_body_rgb565_t *img = select_bitmap(c);
    if (out_image) *out_image = img;
    if (img == NULL || idx < 0 || idx >= FONT_TOTAL_CHARS) return NULL;

    if (!s_font_cached[idx])
    {
        const uint16_t *src_pixels = (const uint16_t *)img->pixel_data;
        uint8_t *dst_alpha = s_font_alpha8_cache[idx];
        int num_pixels = img->width * img->height;

        for (int i = 0; i < num_pixels; i++)
        {
            uint16_t p = src_pixels[i];
            if (p == 0)
            {
                dst_alpha[i] = 0; /* Fully transparent */
            }
            else
            {
                /* Green channel (bits 5..10, 6 bits) gives best anti-aliased gradient precision */
                uint8_t g = (uint8_t)((p >> 5) & 0x3F);
                dst_alpha[i] = (uint8_t)((g << 2) | (g >> 4));
            }
        }

        /* Clean L1 D-Cache so DAVE2D hardware reads the converted alpha from SRAM */
        SCB_CleanDCache_by_Addr((uint32_t *)dst_alpha, (int32_t)num_pixels);
        s_font_cached[idx] = true;
    }

    return s_font_alpha8_cache[idx];
}

void print_user_font_scaled(d2_device *handle, int x, int y, float scale_x, float scale_y, d2_color color, const char *str)
{
    if (str == NULL || handle == NULL) return;
    if (scale_x <= 0.001f) scale_x = 1.0f;
    if (scale_y <= 0.001f) scale_y = 1.0f;

    size_t len = strlen(str);
    int cur_x = x;
    int cur_y = y;

    /* Enable Alpha Blending so alpha=0 is completely transparent */
    d2_setblendmode(handle, d2_bm_alpha, d2_bm_one_minus_alpha);
    d2_setalphamode(handle, d2_am_constant);
    d2_setalpha(handle, 255);

    /* Set text color (e.g. 0xFFFFFFFF for White) */
    d2_setcolor(handle, 0, color);

    for (size_t i = 0; i < len; i++)
    {
        char c = str[i];
        if (c == '\n')
        {
            cur_x = x;
            cur_y += (int)(34.0f * scale_y);
            continue;
        }

        const st_font_body_rgb565_t *image = NULL;
        const uint8_t *alpha_data = get_char_alpha8(c, &image);

        if (image != NULL)
        {
            /* Only blit visible characters */
            if ((c != ' ') && (alpha_data != NULL))
            {
                /* d2_mode_alpha8 tells DAVE2D that the buffer contains opacity data */
                d2_setblitsrc(handle, (void *)alpha_data, (d2_s32)image->width, (d2_s32)image->width, (d2_s32)image->height, d2_mode_alpha8);

                uint32_t dest_w = (uint32_t)((float)image->width * scale_x);
                uint32_t dest_h = (uint32_t)((float)image->height * scale_y);

                d2_blitcopy(handle,
                            (d2_width)image->width, (d2_width)image->height,
                            (d2_blitpos)0, (d2_blitpos)0,
                            (d2_width)(dest_w << 4), (d2_width)(dest_h << 4),
                            (d2_point)(cur_x << 4), (d2_point)(cur_y << 4),
                            (d2_u32)(d2_bf_filter | d2_bf_usealpha | d2_bf_colorize));
            }

            int advance = (image->offset > 0) ? (int)((float)image->offset * scale_x) : (int)((float)image->width * scale_x);
            cur_x += advance;
        }
    }
}

void print_user_font_colored(d2_device *handle, int x, int y, float scale, d2_color color, const char *str)
{
    print_user_font_scaled(handle, x, y, scale, scale, color, str);
}

void print_user_font(d2_device *handle, int x, int y, float scale, const char *str)
{
    /* Default to crisp white text with true transparent background */
    print_user_font_scaled(handle, x, y, scale, scale, 0xFFFFFFFF, str);
}

int get_user_font_string_width(const char *str, float scale)
{
    if (str == NULL) return 0;
    if (scale <= 0.001f) scale = 1.0f;
    int total_w = 0;
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++)
    {
        const st_font_body_rgb565_t *image = select_bitmap(str[i]);
        if (image != NULL)
        {
            int advance = (image->offset > 0) ? (int)((float)image->offset * scale) : (int)((float)image->width * scale);
            total_w += advance;
        }
    }
    return total_w;
}

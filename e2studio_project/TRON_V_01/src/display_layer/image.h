#ifndef IMAGE_H
#define IMAGE_H

#include "bsp_api.h"
#include <stdint.h>

typedef struct
{
    uint16_t       width;
    uint16_t       height;
    uint16_t       bytes_per_pixel;
    uint8_t        pixel_data[1024 * 600 * 2 + 1];
} st_full_image_rgb565_t;

extern const st_full_image_rgb565_t image_data;

#endif /* IMAGE_H */

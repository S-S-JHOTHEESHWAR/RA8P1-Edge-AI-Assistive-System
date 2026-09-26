#ifndef MODERN_FONT_A8_H
#define MODERN_FONT_A8_H

#include <stdint.h>

typedef struct {
    char ascii_value;
    unsigned int width;
    unsigned int height;
    unsigned char pixel_data[460];
} modern_font_char_t;

const modern_font_char_t* get_modern_font_char(char c);

#endif

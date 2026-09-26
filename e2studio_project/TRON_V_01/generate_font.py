import os
from PIL import Image, ImageFont, ImageDraw

font_path = r"D:\jhotheeshwar\TRON\font\timesbd.ttf"
size = 20
font = ImageFont.truetype(font_path, size)

ascent, descent = font.getmetrics()
fixed_height = ascent + descent

chars = [chr(i) for i in range(32, 127)]
char_data = []
max_size = 0

for c in chars:
    width = int(font.getlength(c))
    if width <= 0: width = 5
    
    bbox = font.getbbox(c)
    if bbox:
        if bbox[2] > width: width = bbox[2]
        
    img = Image.new("L", (width, fixed_height), 0)
    draw = ImageDraw.Draw(img)
    draw.text((0, 0), c, font=font, fill=255)
    
    pixels = list(img.getdata())
    max_size = max(max_size, len(pixels))
    char_data.append((c, width, pixels))

print(f"Max size needed: {max_size}")
print(f"Fixed height: {fixed_height}")

header_code = f"""
#ifndef MODERN_FONT_A8_H
#define MODERN_FONT_A8_H

#include <stdint.h>

typedef struct {{
    char ascii_value;
    unsigned int width;
    unsigned int height;
    unsigned char pixel_data[{max_size}];
}} modern_font_char_t;

const modern_font_char_t* get_modern_font_char(char c);

#endif
"""

struct_code = """
#include "modern_font_a8.h"
#include <stddef.h>

#if defined(__GNUC__)
#define BSP_ALIGN_VARIABLE(x) __attribute__((aligned(x)))
#else
#define BSP_ALIGN_VARIABLE(x)
#endif

const modern_font_char_t modern_font_array[] BSP_ALIGN_VARIABLE(128) = {
"""

for c, w, pixels in char_data:
    pixel_hex = ",".join([hex(p) for p in pixels])
    
    c_repr = repr(c)
    if c == "'": c_repr = "'\\''"
    elif c == "\\": c_repr = "'\\\\'"
    
    struct_code += f"    {{{c_repr}, {w}, {fixed_height}, {{{pixel_hex}}}}},\n"

struct_code += "};\n\n"
struct_code += f"const int modern_font_num_chars = {len(chars)};\n"

struct_code += """
const modern_font_char_t* get_modern_font_char(char c) {
    for (int i = 0; i < modern_font_num_chars; i++) {
        if (modern_font_array[i].ascii_value == c) {
            return &modern_font_array[i];
        }
    }
    return NULL;
}
"""

with open(r"C:\Users\jhoth\e2_studio\workspace\TRON_V_01\src\display_layer\modern_font_a8.h", "w") as f:
    f.write(header_code)
with open(r"C:\Users\jhoth\e2_studio\workspace\TRON_V_01\src\display_layer\modern_font_a8.c", "w") as f:
    f.write(struct_code)
print("Files generated successfully.")

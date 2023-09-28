// Libraries
#include <consts.h>

#include <raylib.h>

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

char font[128][4] = {
    [0x01] = {
        0b000, 
        0b111, 
        0b111, 
        0b000, 
    }, 
    [0x02] = {
        0b101, 
        0b111, 
        0b010, 
        0b000, 
    }, 
    ['A'] = {
        0b010, 
        0b101, 
        0b111, 
        0b101, 
    }, 
    ['B'] = {
        0b100, 
        0b111, 
        0b101, 
        0b110, 
    }, 
    ['C'] = {
        0b011, 
        0b100, 
        0b100, 
        0b011, 
    }, 
    ['D'] = {
        0b110, 
        0b101, 
        0b101, 
        0b110, 
    }, 
    ['E'] = {
        0b011, 
        0b100, 
        0b110, 
        0b111, 
    }, 
    ['F'] = {
        0b011, 
        0b100, 
        0b110, 
        0b100, 
    }, 
    ['G'] = {
        0b011, 
        0b100, 
        0b101, 
        0b111, 
    }, 
    ['H'] = {
        0b101, 
        0b101, 
        0b111, 
        0b101, 
    }, 
    ['I'] = {
        0b111, 
        0b010, 
        0b010, 
        0b111, 
    }, 
    ['J'] = {
        0b001, 
        0b001, 
        0b101, 
        0b110, 
    }, 
    ['K'] = {
        0b100, 
        0b101, 
        0b110, 
        0b101, 
    }, 
    ['L'] = {
        0b100, 
        0b100, 
        0b100, 
        0b011, 
    }, 
    ['M'] = {
        0b111, 
        0b111, 
        0b101, 
        0b101, 
    }, 
    ['N'] = {
        0b110, 
        0b101, 
        0b101, 
        0b101, 
    }, 
    ['O'] = {
        0b010, 
        0b101, 
        0b101, 
        0b010, 
    }, 
    ['P'] = {
        0b011, 
        0b101, 
        0b110, 
        0b100, 
    }, 
    ['Q'] = {
        0b011, 
        0b101, 
        0b011, 
        0b001, 
    }, 
    ['R'] = {
        0b011, 
        0b101, 
        0b110, 
        0b101, 
    }, 
    ['S'] = {
        0b011, 
        0b100, 
        0b011, 
        0b111, 
    }, 
    ['T'] = {
        0b111, 
        0b010, 
        0b010, 
        0b010, 
    }, 
    ['U'] = {
        0b101, 
        0b101, 
        0b101, 
        0b110, 
    }, 
    ['V'] = {
        0b101, 
        0b101, 
        0b110, 
        0b100, 
    }, 
    ['W'] = {
        0b101, 
        0b101, 
        0b111, 
        0b111, 
    }, 
    ['X'] = {
        0b101, 
        0b101, 
        0b010, 
        0b101, 
    }, 
    ['Y'] = {
        0b101, 
        0b101, 
        0b010, 
        0b010, 
    }, 
    ['Z'] = {
        0b111, 
        0b001, 
        0b100, 
        0b111, 
    }, 
    ['0'] = {
        0b111, 
        0b101, 
        0b101, 
        0b111, 
    }, 
    ['1'] = {
        0b110, 
        0b010, 
        0b010, 
        0b111, 
    }, 
    ['2'] = {
        0b111, 
        0b001, 
        0b110, 
        0b111, 
    }, 
    ['3'] = {
        0b111, 
        0b010, 
        0b001, 
        0b111, 
    }, 
    ['4'] = {
        0b101, 
        0b101, 
        0b111, 
        0b001, 
    }, 
    ['5'] = {
        0b111, 
        0b100, 
        0b011, 
        0b111, 
    }, 
    ['6'] = {
        0b111, 
        0b100, 
        0b111, 
        0b111, 
    }, 
    ['7'] = {
        0b111, 
        0b001, 
        0b010, 
        0b010, 
    }, 
    ['8'] = {
        0b111, 
        0b101, 
        0b111, 
        0b111, 
    }, 
    ['9'] = {
        0b111, 
        0b101, 
        0b111, 
        0b001, 
    }, 
    ['-'] = {
        0b000, 
        0b000, 
        0b111, 
        0b000, 
    }, 
    ['!'] = {
        0b010, 
        0b010, 
        0b000, 
        0b010, 
    }, 
    ['\"'] = {
        0b101, 
        0b000, 
        0b000, 
        0b000, 
    }, 
    ['#'] = {
        0b101, 
        0b111, 
        0b111, 
        0b101, 
    }, 
    ['$'] = {
        0b011, 
        0b110, 
        0b011, 
        0b110, 
    }, 
    ['%'] = {
        0b101, 
        0b010, 
        0b100, 
        0b101, 
    }, 
    ['&'] = {
        0b010, 
        0b101, 
        0b011, 
        0b111, 
    }, 
    ['('] = {
        0b010, 
        0b100, 
        0b100, 
        0b010, 
    }, 
    [')'] = {
        0b010, 
        0b001, 
        0b001, 
        0b010, 
    }, 
    ['*'] = {
        0b101, 
        0b010, 
        0b101, 
        0b000, 
    }, 
    ['+'] = {
        0b000, 
        0b010, 
        0b111, 
        0b010, 
    }, 
    [','] = {
        0b000, 
        0b000, 
        0b010, 
        0b100, 
    }, 
    ['.'] = {
        0b000, 
        0b000, 
        0b000, 
        0b010, 
    }, 
    ['/'] = {
        0b000, 
        0b001, 
        0b010, 
        0b100, 
    }, 
    ['<'] = {
        0b000, 
        0b010, 
        0b100, 
        0b010, 
    }, 
    ['='] = {
        0b000, 
        0b111, 
        0b000, 
        0b111, 
    }, 
    ['>'] = {
        0b000, 
        0b010, 
        0b001, 
        0b010, 
    }, 
    ['?'] = {
        0b111, 
        0b001, 
        0b000, 
        0b010, 
    }, 
    ['\\'] = {
        0b000, 
        0b100, 
        0b010, 
        0b001, 
    }, 
    ['^'] = {
        0b010, 
        0b101, 
        0b000, 
        0b000, 
    }, 
    ['_'] = {
        0b000, 
        0b000, 
        0b000, 
        0b111, 
    }, 
    ['\''] = {
        0b010, 
        0b010, 
        0b000, 
        0b000, 
    }, 
    [':'] = {
        0b000, 
        0b100, 
        0b000, 
        0b100, 
    }, 
    ['['] = {
        0b110, 
        0b100, 
        0b100, 
        0b110, 
    }, 
    [']'] = {
        0b011, 
        0b001, 
        0b001, 
        0b011, 
    }, 
    [' '] = {
        0b000, 
        0b000, 
        0b000, 
        0b000, 
    }, 
};

static Color bg = { 62, 55, 92, 255 }, fg = { 120, 132, 171, 255 };

void plot_alpha(unsigned char alpha) {
    bg.a = alpha, fg.a = alpha;
}

void plot(int pos_x, int pos_y, const char * fmt, ...) {
    // Formatting
    va_list args;
    va_start(args, fmt);
    char buf[256];
    vsnprintf(buf, 256, fmt, args);
    va_end(args);

    // Plots the text
    for (unsigned int i = 0; i < 256; ++i) {
        if (buf[i] == '\0') break;

        char c = toupper(buf[i]);
        for (int y = 0; y < 4; ++y) {
            for (int x = 1; x < 4; ++x) {
                if (font[c][y] & (1 << (x - 1))) {
                    DrawPixel(pos_x + i * 4 + (4 - x), pos_y + y, fg);
                }
            }
        }
    }
}

void plot_shaded(int pos_x, int pos_y, const char * fmt, ...) {
    // Formatting
    va_list args;
    va_start(args, fmt);
    char buf[256];
    vsnprintf(buf, 256, fmt, args);
    va_end(args);

    // Plots the text shading
    ++pos_x, ++pos_y;

    for (unsigned int i = 0; i < 256; ++i) {
        if (buf[i] == '\0') break;

        char c = toupper(buf[i]);
        for (int y = 0; y < 4; ++y) {
            for (int x = 1; x < 4; ++x) {
                if (font[c][y] & (1 << (x - 1))) {
                    DrawPixel(pos_x + i * 4 + (4 - x), pos_y + y, bg);
                }
            }
        }
    }

    // Plots the text foreground
    --pos_y;
    
    for (unsigned int i = 0; i < 256; ++i) {
        if (buf[i] == '\0') break;

        char c = toupper(buf[i]);
        for (int y = 0; y < 4; ++y) {
            for (int x = 1; x < 4; ++x) {
                if (font[c][y] & (1 << (x - 1))) {
                    DrawPixel(pos_x + i * 4 + (4 - x), pos_y + y, fg);
                }
            }
        }
    }
}
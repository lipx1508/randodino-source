#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WIDTH  512
#define HEIGHT 512

#define FB_WIDTH  128
#define FB_HEIGHT 128

#define TILE_SIZE 8

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define CONV_WORLD(x, y) ((x) + (y) * 16)
#define CONV_TILE(x, y) ((x) + (y) * 8)

#endif
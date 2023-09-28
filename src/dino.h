#ifndef DINO_H
#define DINO_H

// Libraries
#include <stdbool.h>

// Dino
typedef struct {
    int x,      y;
    int grid_x, grid_y;
    bool up, down, left, right; 

    unsigned int frame, prev;

    unsigned char steps;

    int keymap[4];

    bool transition, passed;
} dino_controller;

extern void dino_init();
extern void dino_update();
extern void dino_draw();

#endif
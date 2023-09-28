#ifndef WORLD_H
#define WORLD_H

// World
typedef struct {
    unsigned char tiles[16 * 16];

    struct {
        int x, y;
        int grid_x, grid_y;

        unsigned char id;
    } objs[10];

    unsigned char level;
} world_controller;

extern void world_init();
extern void world_update();
extern void world_draw();

extern void world_start();
extern void world_load();

#endif
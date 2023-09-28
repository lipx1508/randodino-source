// Libraries
#include <consts.h>
#include <dino.h>
#include <world.h>
#include <font.h>

#include <raylib.h>
#include <raymath.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Dino
dino_controller dino;

extern world_controller world;
extern bool             menu;

static Texture2D sprite;
static Sound     sounds[4];

static char text[26] = "";

static double time = 0.0;

bool ending = false;

static inline double lerp(double start, double end, double t) {
    return start + t * (end - start);
}

static void shuffle() {
    for (unsigned char i = 0; i < 4; ++i) {
        int j = i + rand() / (RAND_MAX / (4 - i) + 1);
        int tmp        = dino.keymap[j];
        dino.keymap[j] = dino.keymap[i];
        dino.keymap[i] = tmp;
    }
}

static bool is_solid(unsigned char tile) {
    return tile == 0 || tile > 6;
}

static bool is_collidingn(unsigned char this, int x, int y) {
    for (unsigned int i = 0; i < 10; ++i) {
        if (i != this && x == world.objs[i].grid_x && y == world.objs[i].grid_y)
            return true;
    }

    return false;
}

static bool is_colliding(int x, int y) {
    for (unsigned int i = 0; i < 10; ++i) {
        if (x != world.objs[i].grid_x || y != world.objs[i].grid_y)
            continue;

        switch (world.objs[i].id) {
            case CONV_TILE(6, 0): {
                dino.prev = GetTime() * 1000;
                --dino.steps;

                shuffle();
                PlaySound(sounds[3]);

                return false;
            }
            case CONV_TILE(3, 1): {
                if (dino.up && !is_solid(world.tiles[CONV_WORLD(x, y - 1)]) && 
                               !is_collidingn(i, x, y - 1)) {
                    PlaySound(sounds[1]);
                    --world.objs[i].grid_y;
                } else if (dino.down && !is_solid(world.tiles[CONV_WORLD(x, y + 1)]) && 
                                        !is_collidingn(i, x, y + 1)) {
                    PlaySound(sounds[1]);
                    ++world.objs[i].grid_y;
                } else if (dino.left && !is_solid(world.tiles[CONV_WORLD(x - 1, y)]) && 
                                        !is_collidingn(i, x - 1, y)) {
                    PlaySound(sounds[1]);
                    --world.objs[i].grid_x;
                } else if (dino.right && !is_solid(world.tiles[CONV_WORLD(x + 1, y)]) && 
                                         !is_collidingn(i, x + 1, y)) {
                    PlaySound(sounds[1]);
                    ++world.objs[i].grid_x;
                }

                return true;
            }
        }
    }

    if (is_solid(world.tiles[CONV_WORLD(x, y)])) {
        PlaySound(sounds[3]);
        return true;
    }
    
    return false;
}

void dino_init() {
    world.level = 0;
    world_load();

    sprite = LoadTexture("assets/dino.png");

    sounds[0] = LoadSound("assets/complete.ogg");
    sounds[1] = LoadSound("assets/rock.ogg");
    sounds[2] = LoadSound("assets/walk.ogg");
    sounds[3] = LoadSound("assets/wall.ogg");
}

void dino_update() {
    if (menu) return;

    // Input, movement and collision
    int keymap[4] = {
        KEY_UP, 
        KEY_DOWN, 
        KEY_LEFT, 
        KEY_RIGHT
    };

    dino.up   = IsKeyPressed(keymap[dino.keymap[0]]), dino.down =  IsKeyPressed(keymap[dino.keymap[1]]);
    dino.left = IsKeyPressed(keymap[dino.keymap[2]]), dino.right = IsKeyPressed(keymap[dino.keymap[3]]);

    if (!dino.transition) {
        if (dino.steps > 0) {
            if (dino.up) {
                if (is_colliding(dino.grid_x, dino.grid_y - 1)) {
                    dino.prev  = GetTime() * 1000;
                    dino.y    -= TILE_SIZE - 2;
                    shuffle();
                } else --dino.grid_y;
            } else if (dino.down) {
                if (is_colliding(dino.grid_x, dino.grid_y + 1)) {
                    dino.prev  = GetTime() * 1000;
                    dino.y    += TILE_SIZE - 2;
                    shuffle();
                } else ++dino.grid_y;
            } else if (dino.left) {
                if (is_colliding(dino.grid_x - 1, dino.grid_y)) {
                    dino.prev  = GetTime() * 1000;
                    dino.x    -= TILE_SIZE - 2;
                    shuffle();
                } else --dino.grid_x;
            } else if (dino.right) {
                if (is_colliding(dino.grid_x + 1, dino.grid_y)) {
                    dino.prev  = GetTime() * 1000;
                    dino.x    += TILE_SIZE - 2;
                    shuffle();
                } else ++dino.grid_x;
            }
        }

        if (dino.up || dino.down || dino.left || dino.right) {
            if (dino.steps == 0) {
                dino.frame      = 4;
                dino.transition = true;
                dino.prev       = GetTime() * 10;

                PlaySound(sounds[3]);
            } else {
                --dino.steps;
                PlaySound(sounds[2]);
            }
        }
    }

    // Updates the character position
    double target_x = dino.grid_x * TILE_SIZE;
    double target_y = dino.grid_y * TILE_SIZE;

    dino.x = Lerp(dino.x, target_x, 0.5);
    dino.y = Lerp(dino.y, target_y, 0.5);

    if (dino.x + 1 == target_x) dino.x = target_x;
    if (dino.y + 1 == target_y) dino.y = target_y;

    // Checkes the standing tile
    if (world.tiles[CONV_WORLD(dino.grid_x, dino.grid_y)] == CONV_TILE(5, 0) && !ending) {
        if (world.level == 6) {
            ending = true;
            PlaySound(sounds[0]);
        } else {
            ++world.level;
            world_load();
        }
    }

    // Level reset
    if (IsKeyPressed(KEY_R)) {
        world_start();
    }

    if (dino.transition && GetTime() * 10 - dino.prev >= 15) {
        dino.transition = false;
        dino.prev       = 0;

        world_start();
    }

    // Time metrics
    if (!ending) time = GetTime();
}

void dino_draw() {
    if (menu) return;

    // Debug mode stuff
    /* const char * c[] = { 
           "up", "dw", "lt", "rt", 
       };

       plot(0, 0,  "FPS: %d",         GetFPS());
       plot(0, 8,  "xy: %d %d",       dino.x, dino.y);
       plot(0, 16, "km: %s %s %s %s", c[dino.keymap[0]], c[dino.keymap[1]], c[dino.keymap[2]], c[dino.keymap[3]]);
    */

    // Updates frame
    if (!dino.transition) {
        unsigned int time = GetTime() * 1000;
        dino.frame = time % 600 > 300;

        if (dino.prev && (time - dino.prev) % 200 > 100) {
            dino.frame += 2;
            if (time - dino.prev > 600) {
                dino.prev = 0;
            }
        }
    }

    // Draws dino
    Rectangle rect = { 8 * dino.frame, 0, TILE_SIZE, TILE_SIZE };
    Vector2   pos  = { dino.x, dino.y };
    DrawTextureRec(sprite, rect, pos, WHITE);

    // Draws the key info
    int offset = sin(GetTime() * 2.5) + 1;

    int keymap[4] = {
        KEY_UP, 
        KEY_DOWN, 
        KEY_LEFT, 
        KEY_RIGHT
    };

    bool up   = IsKeyDown(keymap[dino.keymap[0]]), down =  IsKeyDown(keymap[dino.keymap[1]]);
    bool left = IsKeyDown(keymap[dino.keymap[2]]), right = IsKeyDown(keymap[dino.keymap[3]]);

    Rectangle key_rect[] = {
        { (dino.keymap[0] + 6 + up    * 4) * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE }, 
        { (dino.keymap[1] + 6 + down  * 4) * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE }, 
        { (dino.keymap[2] + 6 + left  * 4) * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE }, 
        { (dino.keymap[3] + 6 + right * 4) * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE }, 
    };
    Vector2 key_pos[] = {
        { dino.x,                      dino.y - TILE_SIZE - offset }, 
        { dino.x,                      dino.y + TILE_SIZE + offset }, 
        { dino.x - TILE_SIZE - offset, dino.y                      }, 
        { dino.x + TILE_SIZE + offset, dino.y                      }, 
    };

    DrawTextureRec(sprite, key_rect[0], key_pos[0], WHITE);
    DrawTextureRec(sprite, key_rect[1], key_pos[1], WHITE);
    DrawTextureRec(sprite, key_rect[2], key_pos[2], WHITE);
    DrawTextureRec(sprite, key_rect[3], key_pos[3], WHITE);
 
    // Simple UI
    const char * roman[] = {
        "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X"
    };

    if (!ending) {
        plot_shaded(4, 4 + offset, "\x01 %s \x01", roman[world.level]);

        if (dino.steps) 
            plot_shaded(100, 4 + offset, "\x01 %.2d \x01", dino.steps);
        else 
            plot_shaded(100, 4 + offset, "\x01 !! \x01");
    } else {
        char buf[24];
        snprintf(buf, 24, "%.2d:%.2d", ((int)time) % 3600, ((int)time) % 60);

        plot_shaded(4, 4 + offset, "\x01 %.24s \x01", buf);
    }

    plot_shaded(32, 109 + offset, ending ? "\x01 \x02 Finish! \x02 \x01" : "\x01 Restart [R] \x01");
}
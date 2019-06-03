#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "sprite.h"

// Number of different ways a cactus can look
#define CACTUS_VARIANT_COUNT 4

// Maximum number of cacti that can be on the screen at any time
#define MAX_CACTUS_COUNT 8

typedef struct Cactus Cactus;

struct Cactus {
    int x;
    int y;
    bool active; // See bird.h
    Sprite *sprite;
};

extern Cactus cacti[MAX_CACTUS_COUNT];
extern int cactus_count;

// see bird.h
void init_cacti(void);
void move_cacti(void);
void add_cactus(void);
void show_cacti(void);
void clear_cacti(void);

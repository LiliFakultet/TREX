#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "sprite.h"

#define CACTUS_VARIANT_COUNT 1
#define MAX_CACTUS_COUNT 8

typedef struct Cactus Cactus;

struct Cactus {
    int x;
    int y;
    bool active;
    Sprite *sprite;
};

extern Cactus cacti[MAX_CACTUS_COUNT];

void init_cacti(void);
void move_cacti(void);
void add_cactus(void);
void show_cacti(void);
void clear_cacti(void);

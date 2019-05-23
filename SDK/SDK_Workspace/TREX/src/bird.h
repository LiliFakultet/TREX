#pragma once

#include <stdbool.h>
#include "sprite.h"

#define MAX_BIRD_COUNT 2
#define BIRD_ANIMATION_COUNT 2

typedef struct Bird Bird;

struct Bird {
    int x;
    int y;
    bool active;
    int animation;
    Sprite *sprite;
};

extern Bird birds[MAX_BIRD_COUNT];

void init_birds(void);
void move_birds(void);
void animate_birds(void);
void add_bird(void);
void show_birds(void);
void clear_birds(void);

#pragma once

#include <stdint.h>
#include "vga.h"

typedef struct Sprite Sprite;

struct Sprite {
    const uint32_t *image;
    const int width;
    const int height;
};

void show_sprite(const Sprite *sprite, int x, int y);
void clear_sprite(const Sprite *sprite, int x, int y);

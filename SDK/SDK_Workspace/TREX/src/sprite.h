#pragma once

#include <stdint.h>
#include "fsl.h"

#define PUT_TO_FSL(address, value) \
	do {                           \
		putfsl(address, 0);        \
		putfsl(value, 0);          \
	} while(0)

typedef struct Sprite Sprite;

struct Sprite {
    const uint32_t *image;
    const int width;
    const int height;
};

//extern Xuint32 background[64 * 640 / 8];

void show_sprite(const Sprite *sprite, int x, int y);
void clear_sprite(const Sprite *sprite, int x, int y);

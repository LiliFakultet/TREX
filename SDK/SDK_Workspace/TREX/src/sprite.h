#pragma once

#include "fsl.h"

#define PUT_TO_FSL(address, value) \
	do {                           \
		putfsl(address, 0);        \
		putfsl(value, 0);          \
	} while(0)

typedef struct Sprite Sprite;

struct Sprite {
    const Xuint32 *image;
    const Xuint32 width;
    const Xuint32 height;
};

//extern Xuint32 background[64 * 640 / 8];

void show_sprite(const Sprite *sprite, Xuint32 x, Xuint32 y);
void clear_sprite(const Sprite *sprite, Xuint32 x, Xuint32 y);

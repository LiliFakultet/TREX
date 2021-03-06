#include "ground.h"
#include "vga.h"
#include "config.h"

#include <stdint.h>

static const uint32_t ground1[] = {
    0x00000000,
    0xFFFFFFFF,
    0x00FFFFFF,
    0xFFFF0FF0,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xF0FFF00F,
    0xFFFFFFFF
};

static const uint32_t ground2[] = {
    0x00000000,
    0xFFFFFFFF,
    0xFFF00FFF,
    0x0FFFFFFF,
    0xFFFFFFFF,
    0xFF00FFFF,
    0xFFFFFFFF,
    0xFFFFFF0F
};

static const uint32_t ground3[] = {
    0x00000000,
    0xFFFFFFFF,
    0xFFFFF00F,
    0xF0FFFFFF,
    0xFFFF0FFF,
    0xFFFFFFFF,
    0x00FFFFFF,
    0xFFFFFF00
};

static const uint32_t ground4[] = {
    0x00000000,
    0xFFFFFFFF,
    0xFF0FFFFF,
    0xFFFFF0FF,
    0x00FFFFFF,
    0xFFFFFFFF,
    0xFFF00FF0,
    0xFFFFFFFF
};

static const Sprite ground_sprites[] = {
		{ ground1, 1, 8 },
		{ ground2, 1, 8 },
		{ ground3, 1, 8 },
		{ ground4, 1, 8 }
};


static int initial_ground_variant;

void init_ground() {
	initial_ground_variant = 0;
}

void show_ground() {
	int i;
	int variant = initial_ground_variant;
	for (i = 0; i < DISPLAY_WIDTH; i++) {
		show_sprite(&ground_sprites[variant], i, GROUND_LEVEL + 8);
		variant = (variant + 1) % GROUND_VARIANT_COUNT;
	}
}

void animate_ground() {
	initial_ground_variant = (initial_ground_variant + 1) % GROUND_VARIANT_COUNT;
}

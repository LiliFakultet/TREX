#include <stdlib.h>
#include "cactus.h"

Cactus cacti[MAX_CACTUS_COUNT];
static int cactus_count;

static const uint32_t cactus0[] = {
	0xFFFFFFFF, 0xF00000FF, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFF000FF,
	0xFFFFFFFF, 0x0000000F, 0xFF00000F,
	0xF000FFFF, 0x0000000F, 0xFF00000F,
	0x00000FFF, 0x0000000F, 0xFF00000F,
	0x00000FFF, 0x0000000F, 0xFF00000F,
	0x00000FFF, 0x0000000F, 0xFF00000F,
	0x00000FFF, 0x0000000F, 0xFF00000F,
	0x00000FFF, 0x0000000F, 0xFF00000F,
	0x00000FFF, 0x0000000F, 0xFF00000F,
	0x00000FFF, 0x0000000F, 0xFF00000F,
	0x00000FFF, 0x0000000F, 0xFF00000F,
	0x00000FFF, 0x0000000F, 0xFF00000F,
	0x00000FFF, 0x0000000F, 0xFF00000F,
	0x00000000, 0x00000000, 0x000000FF,
	0x00000000, 0x00000000, 0x00000FFF,
	0xF0000000, 0x00000000, 0x0000FFFF,
	0xFF000000, 0x00000000, 0x000FFFFF,
	0xFFF00000, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF
};

static Sprite cactus_sprites[CACTUS_VARIANT_COUNT] = {{cactus0, 3, 36}};

void init_cacti() {
	int i;
	for (i = 0; i < MAX_CACTUS_COUNT; i++) {
		cacti[i].active = false;
	}

	cactus_count = 0;
}

void move_cacti() {
	int i;
	for (i = 0; i < MAX_CACTUS_COUNT; i++) {
		if (!cacti[i].active) {
			continue;
		}

		if (cacti[i].x > 0) {
			--(cacti[i].x);
		}
		else {
			cacti[i].active = false;
			--cactus_count;
		}
	}
}

void add_cactus() {
	int i;
	int available_index = -1;
	int variant;

	if (cactus_count == MAX_CACTUS_COUNT) {
		return;
	}

	for (i = 0; i < MAX_CACTUS_COUNT; i++) {
		if (!cacti[i].active) {
			available_index = i;
			break;
		}
	}

	variant = rand() % CACTUS_VARIANT_COUNT;

	cacti[available_index].active = true;
	cacti[available_index].sprite = &cactus_sprites[variant];
	cacti[available_index].x = 79 - cacti[available_index].sprite->width;
	cacti[available_index].y = 240;

	++cactus_count;
}

void show_cacti() {
	int i;
	for (i = 0; i < MAX_CACTUS_COUNT; i++) {
		if (cacti[i].active) {
			show_sprite(cacti[i].sprite, cacti[i].x, cacti[i].y);
		}
	}
}

void clear_cacti() {
	int i;
	for (i = 0; i < MAX_CACTUS_COUNT; i++) {
		if (cacti[i].active) {
			clear_sprite(cacti[i].sprite, cacti[i].x, cacti[i].y);
		}
	}
}

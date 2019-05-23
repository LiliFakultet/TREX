#include <stdint.h>
#include <stdlib.h>
#include "bird.h"

Bird birds[MAX_BIRD_COUNT];
static int bird_count;

const uint32_t bird1_sprite[] = {
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFF00FFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFF0000FF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFF00000, 0xFFFF0000, 0x00FFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFF00000, 0xFFFF0000, 0x00FFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xF0000000, 0xFFFF0000, 0x0000FFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xF0000000, 0xFFFF0000, 0x0000FFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFF0, 0x00000000, 0x00FF0000, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFF0, 0x00000000, 0x00FF0000, 0x000000FF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFF000, 0x00000000, 0x00FF0000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFF000, 0x00000000, 0x00FF0000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFF00000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFF00000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00FFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00FFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000, 0x00000000, 0x0000000F,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x00000000, 0x00000000, 0x0000000F,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0x00000000, 0x00000000, 0x0FFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF0000, 0x00000000, 0x00000000, 0x0FFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFF00, 0x00000000, 0x00000000, 0x00000FFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFF00, 0x00000000, 0x00000000, 0x00000FFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x0000000F, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};

const uint32_t bird2_sprite[] = {
	0xFFFFFFFF, 0xFFF0000F, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFF0000F, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xF000000F, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xF000000F, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFF0, 0x00000000, 0x0FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFF0, 0x00000000, 0x0FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFF000, 0x00000000, 0x0FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFF000, 0x00000000, 0x0FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFF00000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFF00000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFF0, 0x00000000, 0x00000000, 0x00FFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFF0, 0x00000000, 0x00000000, 0x00FFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xF0000000, 0x00000000, 0x00000000, 0x000000FF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xF0000000, 0x00000000, 0x00000000, 0x000000FF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFF00000, 0x00000000, 0x00000000, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFF00000, 0x00000000, 0x00000000, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFF00000, 0x00000000, 0x00000000, 0x0000FFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFF00000, 0x00000000, 0x00000000, 0x0000FFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFF00000, 0x00000000, 0x000000FF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFF00000, 0x00000000, 0x000000FF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFF00000, 0x0000FFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFF00000, 0x0000FFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFF00000, 0x00FFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFF00000, 0x00FFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFF0000F, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFF0000F, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFF0000F, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFF0000F, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFF00FFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};


static Sprite bird_sprites[MAX_BIRD_COUNT] = {
	{ bird1_sprite, 6, 29 },
	{ bird2_sprite, 6, 29 }
};

void init_birds(void) {
	int i;
	for (i = 0; i < MAX_BIRD_COUNT; i++) {
		birds[i].active = false;
	}

	bird_count = 0;
}

void move_birds(void) {
	int i;
	for (i = 0; i < MAX_BIRD_COUNT; i++) {
		if (!birds[i].active) {
			continue;
		}

		if (birds[i].x > 0) {
			--(birds[i].x);
		}
		else {
			birds[i].active = false;
			--bird_count;
		}
	}
}

void add_bird(void) {
	int i;
	int available_index = -1;
	int height;

	if (bird_count == MAX_BIRD_COUNT) {
		return;
	}

	for (i = 0; i < MAX_BIRD_COUNT; i++) {
		if (!birds[i].active) {
			available_index = i;
			break;
		}
	}

	height = 240 - 32 * (rand() % 3);

	birds[available_index].active = true;
	birds[available_index].sprite = &bird_sprites[0];
	birds[available_index].animation = 0;
	birds[available_index].x = 79 - birds[available_index].sprite->width;
	birds[available_index].y = height;

	++bird_count;
}

void animate_birds(void) {
	int i;
	for (i = 0; i < MAX_BIRD_COUNT; i++) {
		if (birds[i].active) {
			birds[i].animation = (birds[i].animation + 1) % BIRD_ANIMATION_COUNT;
			birds[i].sprite = &bird_sprites[birds[i].animation];
		}
	}
}

void show_birds(void) {
	int i;
	for (i = 0; i < MAX_BIRD_COUNT; i++) {
		if (birds[i].active) {
			show_sprite(birds[i].sprite, birds[i].x, birds[i].y);
		}
	}
}

void clear_birds(void) {
	int i;
	for (i = 0; i < MAX_BIRD_COUNT; i++) {
		if (birds[i].active) {
			clear_sprite(birds[i].sprite, birds[i].x, birds[i].y);
		}
	}
}

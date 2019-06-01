#include "cloud.h"
#include <stdlib.h>

Cloud clouds[MAX_CLOUD_COUNT];
int cloud_count;

// clang-format off

static const uint32_t cloud[] = {
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xF111FFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFF111, 0x11F11FFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFF1FF, 0xFFFF11FF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFF1FFFF, 0xFFFFF11F, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFF1FFFF, 0xFFFFF1F1, 0x11FFFFFF,
	0xFFFFFFFF, 0xF111FFFF, 0xFFFF1FFF, 0xFF1FFFFF,
	0xFFFFFFFF, 0xF1FFFFFF, 0xFFFFFFFF, 0xFFF11FFF,
	0xFFFF1111, 0x1FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFF1FFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFF1F,
	0x1111FFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFF1,
	0x1FFFFF11, 0x11111111, 0x11111111, 0x11111111,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
	0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};

// clang-format on

static Sprite cloud_sprite = {cloud, 4, 16};

void init_clouds() {
    int i;

    for (i = 0; i < MAX_CLOUD_COUNT; i++) {
        clouds[i].active = false;
    }

    cloud_count = 0;
}

void move_clouds() {
    int i;
    for (i = 0; i < MAX_CLOUD_COUNT; i++) {
        if (!clouds[i].active) {
            continue;
        }

        if (clouds[i].x > 0) {
            --(clouds[i].x);
        }
        else {
            clouds[i].active = false;
            --cloud_count;
        }
    }
}

void add_cloud(void) {
    int i;
    int available_index = -1;
    int height;

    if (cloud_count == MAX_CLOUD_COUNT) {
        return;
    }

    for (i = 0; i < MAX_CLOUD_COUNT; i++) {
        if (!clouds[i].active) {
            available_index = i;
            break;
        }
    }

    // Select one of the three possible heights at which a cloud can appear
    height = 240 - 24 * (rand() % 3) - 128;

    clouds[available_index].active = true;
    clouds[available_index].sprite = &cloud_sprite;
    clouds[available_index].x = 79 - clouds[available_index].sprite->width;
    clouds[available_index].y = height;

    ++cloud_count;
}

void show_clouds(void) {
    int i;
    for (i = 0; i < MAX_CLOUD_COUNT; i++) {
        if (clouds[i].active) {
            show_sprite(clouds[i].sprite, clouds[i].x, clouds[i].y);
        }
    }
}

void clear_clouds(void) {
    int i;
    for (i = 0; i < MAX_CLOUD_COUNT; i++) {
        if (clouds[i].active) {
            clear_sprite(clouds[i].sprite, clouds[i].x, clouds[i].y);
        }
    }
}

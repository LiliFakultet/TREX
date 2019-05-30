#pragma once

#include <stdbool.h>
#include "sprite.h"

#define MAX_CLOUD_COUNT 4

typedef struct Cloud Cloud;

struct Cloud {
	int x;
	int y;
	bool active;
	Sprite *sprite;
};

extern Cloud clouds[MAX_CLOUD_COUNT];
extern int cloud_count;

void init_clouds(void);
void move_clouds(void);
void add_cloud(void);
void show_clouds(void);
void clear_clouds(void);

#include <stdlib.h>
#include "collision.h"
#include "player.h"
#include "cactus.h"
#include "sprite.h"
#include "bird.h"

bool check_collisions(void) {
	int i;
	const int player_height = player.sprites[player.animation]->height;
	const int player_width = player.sprites[player.animation]->width;

	for (i = 0; i < MAX_CACTUS_COUNT; i++) {
		const int cactus_height = cacti[i].sprite->height;
		const int cactus_width = cacti[i].sprite->width;

		if (!cacti[i].active) {
			continue;
		}

		if (player.x < cacti[i].x + cactus_width
			&& player.x + player_width > cacti[i].x
			&& player.y < cacti[i].y + cactus_height
			&& player.y + player_height > cacti[i].y) {

			return true;
		}
	}

	for (i = 0; i < MAX_BIRD_COUNT; i++) {
		const int bird_height = birds[i].sprite->height;
		const int bird_width = birds[i].sprite->width;

		if (!birds[i].active) {
			continue;
		}

		if (player.x < birds[i].x + bird_width
			&& player.x + player_width > birds[i].x
			&& player.y < birds[i].y + bird_height
			&& player.y + player_height > birds[i].y) {

			return true;
		}

	}

	return false;
}

#include <stdlib.h>
#include "collision.h"
#include "player.h"
#include "cactus.h"
#include "sprite.h"
// tice

bool check_collisions(void) {
	int i;
	for (i = 0; i < MAX_CACTUS_COUNT; i++) {
		int h_span;
		int v_span;

		if (!cacti[i].active) {
			continue;
		}

		h_span = abs(player.x - cacti[i].x);
		v_span = abs(player.y - cacti[i].y);

		// TODO: umesto return true treba da se proveri pixel po pixel kolizija sprite-ova tako da 0xF ne izaziva koliziju
		if (player.sprites[player.animation]->width >= h_span && player.sprites[player.animation]->height >= v_span) {
			return true;
		}
		else if (cacti[i].sprite->width >= h_span && cacti[i].sprite->height >= v_span) {
			return true;
		}

	}

	return false;
}

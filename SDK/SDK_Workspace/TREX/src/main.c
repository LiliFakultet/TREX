#include <stdbool.h>
#include <stdlib.h>
#include "platform.h"
#include "player.h"
#include "sprite.h"
#include "cactus.h"
#include "collision.h"
#include "input.h"
#include "bird.h"
#include "config.h"
#include "vga.h"
#include "cloud.h"
#include "ground.h"

volatile static bool game_running = false;
volatile static bool request_reset = false;
volatile static int ticks = 0;
volatile static int score = 0;
volatile static int high_score = 0;
volatile static int enemy_delay = INITIAL_ENEMY_DELAY;
volatile bool cheat_mode = false;
volatile bool parna_zemlja = false;

static void reset() {
	int stop_time;

	show_ground();
	show_clouds();
    show_cacti();
    show_birds();
    show_player();
	game_running = false;

	print_high_score(high_score);

	stop_time = ticks + 60;
	while (ticks != stop_time) {

	}

    while (get_key() != NO_INPUT) {

	}

    while (get_key() != UP_JOY && get_key() != MIDDLE_JOY) {

    }

    clear_text_screen();

    srand(ticks);

	clear_clouds();
    clear_player();
    clear_cacti();
    clear_birds();

    init_ground();
    init_clouds();
    init_cacti();
    init_birds();
    init_player(10, GROUND_LEVEL);
    player.state = PLAYER_STATE_RUNNING;

    ticks = 0;
    score = 0;
    enemy_delay = 0;
    game_running = true;
}

static void update_score() {
	if (score < NORMAL_SPEED_THRESHOLD) {
		if (ticks % LOW_SPEED_SCORE_DIVISOR == 0) {
			++score;
		}
		enemy_delay = LOW_SPEED;
	}
	else if (score < HIGH_SPEED_THRESHOLD) {
		if (ticks % NORMAL_SPEED_SCORE_DIVISOR == 0) {
			++score;
		}
		enemy_delay = NORMAL_SPEED;
	}
	else if (score < INSANE_SPEED_THRESHOLD) {
		if (ticks % HIGH_SPEED_SCORE_DIVISOR == 0) {
			++score;
		}
		enemy_delay = HIGH_SPEED;
	}
	else {
		if (ticks % INSANE_SPEED_SCORE_DIVISOR == 0) {
			++score;
		}
		enemy_delay = INSANE_SPEED;
	}

	if (score > high_score) {
		high_score = score;
	}

	print_score(score);
}

void vga_interrupt_handler(void *arg) {
    (void)arg;

    ++ticks;

    if (!game_running) {
        return;
    }

    if (get_key() == LEFT_JOY) {
    	cheat_mode = true;
		print_cheat_mode();
    }
    else if (get_key() == RIGHT_JOY) {
    	cheat_mode = false;
		clear_cheat_mode();
    }

    if (score % 1000 > 500) {
    	night_mode();
    }
    else {
    	day_mode();
    }

    update_score();

    clear_clouds();
    clear_player();
    clear_cacti();
    clear_birds();

    if (ticks % SPAWN_DELAY == 0) {
    	if (rand() % (4 * cactus_count) == 0) {
        	add_cactus();
    	}
    	else if (score > 200 && rand() % 8 == 0) {
        	add_bird();
    	}
    }

    if (ticks % (SPAWN_DELAY * 3) == 0 && rand() % 2 == 0) {
    	add_cloud();
    }

	if (ticks % PLAYER_DELAY == 0) {
	    handle_input();
	}

    if (ticks % enemy_delay == 0) {
        move_cacti();
    	move_birds();
    }

    if (ticks % ANIMATION_DELAY == 0) {
        animate_player();
    }

    if (ticks % (enemy_delay * 4) == 0) {
    	animate_ground();
        show_ground();
    }

    if (ticks % BIRD_ANIMATION_DELAY == 0) {
        animate_birds();
    }

    if (ticks % (enemy_delay * 10) == 0) {
    	move_clouds();
    }

    if (check_collisions() && !cheat_mode) {
    	player.state = PLAYER_STATE_DEAD;
    	animate_player();
    	request_reset = true;
    	game_running = false;

    	print_game_over();
    }

    show_clouds();
    show_cacti();
    show_birds();
    show_player();
}

int main() {
    init_platform();
    init_vga();
	init_vga_interrupt(vga_interrupt_handler);
    init_player(10, GROUND_LEVEL);
    init_cacti();
    init_birds();
    init_clouds();
    init_ground();

    score = 0;
    high_score = 0;
    reset_score_text();

    show_ground();

    request_reset = true;

    while (1) {
    	if (request_reset) {
    		request_reset = false;
    		reset();
    	}
    }
}

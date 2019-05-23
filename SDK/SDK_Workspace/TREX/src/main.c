#include <stdbool.h>
#include <stdlib.h>
#include "platform.h"
#include "player.h"
#include "sprite.h"
#include "cactus.h"
#include "collision.h"
#include "input.h"
#include "bird.h"

#include "vga.h"

#define ANIMATION_DELAY 2
#define ENEMY_DELAY 4
#define CACTUS_SPAWN_DELAY ((ENEMY_DELAY) * (8))
#define BIRD_SPAWN_DELAY ((ENEMY_DELAY) * (32))
#define PLAYER_DELAY 3
#define BIRD_ANIMATION_DELAY 20

volatile static bool game_running = false;
volatile static int ticks = 0;
volatile static int score = 0;
volatile static int high_score = 0;
static char score_text[14] = "         00000";

static void reset() {
    show_player();
    show_cacti();
    show_birds();
	game_running = false;

	if (high_score > 0) {
		score_text[7] = '0' + high_score % 10;
		score_text[6] = '0' + high_score / 10  % 10;
		score_text[5] = '0' + high_score / 100 % 10;
		score_text[4] = '0' + high_score / 1000 % 10;
		score_text[3] = '0' + high_score / 10000 % 10;
		score_text[1] = 'I';
		score_text[0] = 'H';
	}

//	print_string(score_text, 14);
//
//	set_cursor(6000);
//	print_string("GAME OVER", 9);
	//set_cursor(4713);

	// TODO: izbaci busy wait iz handlera
    while (get_key() != NO_INPUT) {

	}

    while (get_key() != UP_JOY && get_key() != MIDDLE_JOY) {

    }
    srand(ticks);

    clear_player();
    clear_cacti();
    clear_birds();
    init_player(10, 240);
    init_cacti();
    init_birds();

    ticks = 0;
    player.state = PLAYER_STATE_RUNNING;
    game_running = true;
}

void vga_interrupt_handler(void *arg) {
    (void)arg;

    ++ticks;

    if (!game_running) {
        return;
    }

    score = ticks / 20;
    if (score > high_score) {
    	high_score = score;
    }

    score_text[13] = '0' + score % 10;
    score_text[12] = '0' + score / 10  % 10;
    score_text[11] = '0' + score / 100 % 10;
    score_text[10] = '0' + score / 1000 % 10;
    score_text[9]  = '0' + score / 10000 % 10;
	print_string(score_text, 14);

    clear_player();
    clear_cacti();
    clear_birds();

    if (ticks % CACTUS_SPAWN_DELAY == 0 && rand() % 10 == 0) {
    	add_cactus();
    }

    if (ticks % BIRD_SPAWN_DELAY == 0 && rand() % 10 == 0) {
    	add_bird();
    }

	if (ticks % PLAYER_DELAY == 0) {
	    handle_input();
	}

    if (ticks % ENEMY_DELAY == 0) {
        move_cacti();
    	move_birds();
    }

    if (ticks % ANIMATION_DELAY == 0) {
        animate_player();
    }

    if (ticks % BIRD_ANIMATION_DELAY == 0) {
        animate_birds();
    }

    if (check_collisions()) {
    	player.state = PLAYER_STATE_DEAD;
    	animate_player();
    	reset();
    }

    show_player();
    show_cacti();
    show_birds();
}

int main() {
    init_platform();
    init_vga();
	init_vga_interrupt(vga_interrupt_handler);
    init_player(10, 240);
    init_cacti();
    init_birds();

    player.state = PLAYER_STATE_RUNNING;
    reset();

    while (1) {

    }
}

#include <stdbool.h>
#include <stdlib.h>
#include "bird.h"
#include "cactus.h"
#include "cloud.h"
#include "collision.h"
#include "config.h"
#include "ground.h"
#include "input.h"
#include "platform.h"
#include "player.h"
#include "sprite.h"
#include "vga.h"

volatile static bool game_running = false;
volatile static bool request_reset = false;
volatile static int ticks = 0;
volatile static int score = 0;
volatile static int high_score = 0;
volatile static int enemy_delay = INITIAL_ENEMY_DELAY;
volatile static bool cheat_mode = false;

// Check if any entities need to update their animation and do that if they do
static void update_animations(void) {
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
}

// Check if any entities need to move and move them if they do
static void update_positions(void) {
    if (ticks % PLAYER_DELAY == 0) {
        handle_input();
    }

    if (ticks % enemy_delay == 0) {
        move_cacti();
        move_birds();
    }

    if (ticks % (enemy_delay * 10) == 0) {
        move_clouds();
    }
}

// Update score and speed up the game if necessary
static void update_score(void) {
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

// Check if any new entities should be created and add them if they should
// All timing and spawn chance related things were experimentally determined
// and have no underlying reason for being that way
static void spawn_new_entities(void) {
    if (ticks % SPAWN_DELAY == 0) {
        if (rand() % (4 * cactus_count) == 0) {
            add_cactus();
        }
        else if (score > 200 && rand() % 5 == 0) {
            add_bird();
        }
    }

    if (ticks % (SPAWN_DELAY * 3) == 0 && rand() % 2 == 0) {
        add_cloud();
    }
}

static void init_entities(void) {
    init_ground();
    init_clouds();
    init_cacti();
    init_birds();
    init_player(10, GROUND_LEVEL);
}

// NOTE: ground is never cleared because it's always visible and calling
// show_ground again writes over the last version.
static void clear_entities(void) {
    clear_clouds();
    clear_player();
    clear_cacti();
    clear_birds();
}

// NOTE: does not show ground. This is done manually
static void show_entities(void) {
    show_clouds();
    show_cacti();
    show_birds();
    show_player();
}

static void reset(void) {
    int stop_time;

    show_ground();
    show_entities();
    game_running = false;

    print_high_score(high_score);

    // Wait for 1s before allowing the game to continue
    stop_time = ticks + 60;
    while (ticks != stop_time) {
    }

    // Wait until the player releases the joystick (so that holding a button
    // doesn't automatically reset)
    while (get_key() != NO_INPUT) {
    }

    // Wait until any regular key is pressed and start the game
    while (get_key() != UP_JOY && get_key() != MIDDLE_JOY) {
    }

    clear_text_screen();

    // Sets the seed for the PRNG based on time that passed since the last
    // reset. Since player input is nondeterministic this should be a good
    // enough source of randomness.
    srand(ticks);

    clear_entities();
    init_entities();
    player.state = PLAYER_STATE_RUNNING;

    ticks = 0;
    score = 0;
    enemy_delay = 0;
    game_running = true;
}

void vga_interrupt_handler(void *arg) {
    (void)arg;

    ++ticks;

    if (!game_running) {
        return;
    }

    // Handle turning cheat mode on and off
    if (get_key() == LEFT_JOY) {
        cheat_mode = true;
        print_cheat_mode();
    }
    else if (get_key() == RIGHT_JOY) {
        cheat_mode = false;
        clear_cheat_mode();
    }

    // Handle day/night transition
    if (score % 1000 > 500) {
        night_mode();
    }
    else {
        day_mode();
    }

    update_score();

    clear_entities();

    spawn_new_entities();

    update_positions();

    update_animations();

    // Check if the player died
    if (check_collisions() && !cheat_mode) {
        player.state = PLAYER_STATE_DEAD;
        animate_player();
        request_reset = true;
        game_running = false;

        print_game_over();
    }

    show_entities();
}

int main(void) {
    init_platform();
    init_vga();
    init_vga_interrupt(vga_interrupt_handler);
    init_entities();

    score = 0;
    high_score = 0;
    reset_score_text();

    request_reset = true;

    while (1) {
        if (request_reset) {
            request_reset = false;
            reset();
        }
    }
}

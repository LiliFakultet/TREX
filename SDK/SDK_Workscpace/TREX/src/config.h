#pragma once

#define ANIMATION_DELAY 10
#define INITIAL_ENEMY_DELAY 5
#define SPAWN_DELAY ((4) * (25))
#define PLAYER_DELAY 3
#define BIRD_ANIMATION_DELAY 20

// y location
#define GROUND_LEVEL 240

#define JUMP_STEP 5
#define JUMP_THRESHOLD 52
#define JUMP_HEIGHT 82

// Cursor locations for various text elements
#define SCORE_LOCATION 4713
#define GAME_OVER_LOCATION 7180
#define CHEAT_MODE_LOCATION 4500

// Defines the delay between frame updates for various speeds
#define LOW_SPEED 5
#define NORMAL_SPEED 4
#define HIGH_SPEED 3
#define INSANE_SPEED 2

// Controls how quickly score accumulates with respect to speed
#define LOW_SPEED_SCORE_DIVISOR 15
#define NORMAL_SPEED_SCORE_DIVISOR 10
#define HIGH_SPEED_SCORE_DIVISOR 7
#define INSANE_SPEED_SCORE_DIVISOR 3

// Defines the score at which speed increases
#define NORMAL_SPEED_THRESHOLD 100
#define HIGH_SPEED_THRESHOLD 1000
#define INSANE_SPEED_THRESHOLD 2000

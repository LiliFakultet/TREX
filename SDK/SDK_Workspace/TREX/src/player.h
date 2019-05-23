#pragma once

#include <stdint.h>
#include "sprite.h"

enum PlayerAnimation {
    PLAYER_ANIMATION_IDLE,
    PLAYER_ANIMATION_RUNNING_1,
    PLAYER_ANIMATION_RUNNING_2,
    PLAYER_ANIMATION_DUCKING_1,
    PLAYER_ANIMATION_DUCKING_2,
    PLAYER_ANIMATION_DEAD,
    PLAYER_ANIMATION_COUNT
};

enum PlayerState {
    PLAYER_STATE_IDLE,
    PLAYER_STATE_RUNNING,
    PLAYER_STATE_JUMPING,
    PLAYER_STATE_DUCKING,
    PLAYER_STATE_DEAD
};

typedef struct Player Player;
typedef enum PlayerState PlayerState;
typedef enum PlayerAnimation PlayerAnimation;

struct Player {
    int x;
    int y;
    PlayerState state;
    PlayerAnimation animation;
    Sprite *sprites[PLAYER_ANIMATION_COUNT];
};

extern Player player;

void init_player(int x, int y);
void show_player(void);
void clear_player(void);
void animate_player(void);

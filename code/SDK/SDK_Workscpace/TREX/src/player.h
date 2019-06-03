#pragma once

#include <stdint.h>
#include "sprite.h"

/* All possible animations the dinosaur can be in during the game.
 * This can be used to directly index an array of sprites.
 */
enum PlayerAnimation {
    PLAYER_ANIMATION_IDLE,
    PLAYER_ANIMATION_RUNNING_1,
    PLAYER_ANIMATION_RUNNING_2,
    PLAYER_ANIMATION_DUCKING_1,
    PLAYER_ANIMATION_DUCKING_2,
    PLAYER_ANIMATION_DEAD,
    PLAYER_ANIMATION_COUNT // Has to be the last entry in the enum
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

/* Holds all data required to handle the player.
 * sprites is an array of pointers to all sprites the player has, the currently
 * active sprite is located at player.sprites[player.animation]
 */
struct Player {
    int x;
    int y;
    PlayerState state;
    PlayerAnimation animation;
    Sprite *sprites[PLAYER_ANIMATION_COUNT];
};

extern Player player;

/* Initialize the player to the initial state and animation and sets his
 * location to the desired coordinates
 */
void init_player(int x, int y);

/* Wrappers for easier use of show_sprite and clear_sprite
 */
void show_player(void);
void clear_player(void);

/* Updates the currently active sprite based on the player state
 */
void animate_player(void);

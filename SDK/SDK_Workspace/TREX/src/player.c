#include "player.h"

#define PLAYER_WIDTH 4
#define PLAYER_HEIGHT 32

static const Xuint32 player_idle[] = {
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xF0000000, 0x0000FFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xF0000000, 0x0000FFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00110000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00110000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x000FFFFF,
    0xFF00FFFF, 0xFFFFFFF0, 0x00000FFF, 0xFFFFFFFF,
    0xFF00FFFF, 0xFFFFFFF0, 0x00000FFF, 0xFFFFFFFF,
    0xFF00FFFF, 0xFFFFF000, 0x00000FFF, 0xFFFFFFFF,
    0xFF000FFF, 0xFFF00000, 0x00000000, 0xFFFFFFFF,
    0xFF00000F, 0xF0000000, 0x00000FF0, 0xFFFFFFFF,
    0xFF00000F, 0xF0000000, 0x00000FF0, 0xFFFFFFFF,
    0xFF000000, 0x00000000, 0x00000FFF, 0xFFFFFFFF,
    0xFFF00000, 0x00000000, 0x00000FFF, 0xFFFFFFFF,
    0xFFFF0000, 0x00000000, 0x00000FFF, 0xFFFFFFFF,
    0xFFFF0000, 0x00000000, 0x0000FFFF, 0xFFFFFFFF,
    0xFFFFF000, 0x00000000, 0x0000FFFF, 0xFFFFFFFF,
    0xFFFFFFF0, 0x00000000, 0x000FFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x00000000, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x00000000, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF0000FF0, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF000FFFF, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF00FFFFF, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF00FFFFF, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF000FFFF, 0x000FFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};

static const Xuint32 player_dead[] = {
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xF0000000, 0x0000FFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xF0000000, 0x0000FFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00111000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00101000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00111000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x000FFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x000FFFFF,
    0xFF00FFFF, 0xFFFFFFF0, 0x00000FFF, 0xFFFFFFFF,
    0xFF00FFFF, 0xFFFFFFF0, 0x00000FFF, 0xFFFFFFFF,
    0xFF00FFFF, 0xFFFFF000, 0x00000FFF, 0xFFFFFFFF,
    0xFF000FFF, 0xFFF00000, 0x00000000, 0xFFFFFFFF,
    0xFF00000F, 0xF0000000, 0x00000FF0, 0xFFFFFFFF,
    0xFF00000F, 0xF0000000, 0x00000FF0, 0xFFFFFFFF,
    0xFF000000, 0x00000000, 0x00000FFF, 0xFFFFFFFF,
    0xFFF00000, 0x00000000, 0x00000FFF, 0xFFFFFFFF,
    0xFFFF0000, 0x00000000, 0x00000FFF, 0xFFFFFFFF,
    0xFFFF0000, 0x00000000, 0x0000FFFF, 0xFFFFFFFF,
    0xFFFFF000, 0x00000000, 0x0000FFFF, 0xFFFFFFFF,
    0xFFFFFFF0, 0x00000000, 0x000FFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x00000000, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x00000000, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF000FFF0, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF00FFFFF, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF0FFFFFF, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF0FFFFFF, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF000FFFF, 0x000FFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};

static const Xuint32 player_running1[] = {
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xF0000000, 0x0000FFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xF0000000, 0x0000FFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00110000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00110000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x000FFFFF,
    0xFF00FFFF, 0xFFFFFFF0, 0x00000FFF, 0xFFFFFFFF,
    0xFF00FFFF, 0xFFFFFFF0, 0x00000FFF, 0xFFFFFFFF,
    0xFF00FFFF, 0xFFFFF000, 0x00000FFF, 0xFFFFFFFF,
    0xFF000FFF, 0xFFF00000, 0x00000000, 0xFFFFFFFF,
    0xFF00000F, 0xF0000000, 0x00000FF0, 0xFFFFFFFF,
    0xFF00000F, 0xF0000000, 0x00000FF0, 0xFFFFFFFF,
    0xFF000000, 0x00000000, 0x00000FFF, 0xFFFFFFFF,
    0xFFF00000, 0x00000000, 0x00000FFF, 0xFFFFFFFF,
    0xFFFF0000, 0x00000000, 0x00000FFF, 0xFFFFFFFF,
    0xFFFF0000, 0x00000000, 0x0000FFFF, 0xFFFFFFFF,
    0xFFFFF000, 0x00000000, 0x0000FFFF, 0xFFFFFFFF,
    0xFFFFFFF0, 0x00000000, 0x000FFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x00000000, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x00000000, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF000FFF0, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF00FFFFF, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF0FFFFFF, 0x000FFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF0FFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF000FFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};

static const Xuint32 player_running2[] = {
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xF0000000, 0x0000FFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xF0000000, 0x0000FFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00110000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00110000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000FFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x0000000F, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x000FFFFF,
    0xFF00FFFF, 0xFFFFFFF0, 0x00000FFF, 0xFFFFFFFF,
    0xFF00FFFF, 0xFFFFFFF0, 0x00000FFF, 0xFFFFFFFF,
    0xFF00FFFF, 0xFFFFF000, 0x00000FFF, 0xFFFFFFFF,
    0xFF000FFF, 0xFFF00000, 0x00000000, 0xFFFFFFFF,
    0xFF00000F, 0xF0000000, 0x00000FF0, 0xFFFFFFFF,
    0xFF00000F, 0xF0000000, 0x00000FF0, 0xFFFFFFFF,
    0xFF000000, 0x00000000, 0x00000FFF, 0xFFFFFFFF,
    0xFFF00000, 0x00000000, 0x00000FFF, 0xFFFFFFFF,
    0xFFFF0000, 0x00000000, 0x00000FFF, 0xFFFFFFFF,
    0xFFFF0000, 0x00000000, 0x0000FFFF, 0xFFFFFFFF,
    0xFFFFF000, 0x00000000, 0x0000FFFF, 0xFFFFFFFF,
    0xFFFFFFF0, 0x00000000, 0x000FFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x00000000, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x00000000, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF00FFFF0, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF0FFFFFF, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xF000FFFF, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x0FFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0x000FFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};

static const Xuint32 player_ducking1[] = {
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFF00FFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x0000FFFF,
    0xFF000FFF, 0xFF000000, 0x0000000F, 0xF0000000, 0x000000FF,
    0xFF000000, 0x00000000, 0x00000000, 0x000FF000, 0x000000FF,
    0xFFF00000, 0x00000000, 0x00000000, 0x000FF000, 0x000000FF,
    0xFFFF0000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF,
    0xFFFF0000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF,
    0xFFFFF000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF,
    0xFFFFFF00, 0x00000000, 0x00000000, 0x0000000F, 0xFFFFFFFF,
    0xFFFFFFF0, 0x00000000, 0x00000000, 0xFF000000, 0x000FFFFF,
    0xFFFFFFFF, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x00000000, 0x0FFF0FFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x00FFFF00, 0xFFFF0000, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x0FFFFF0F, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x0FFFFF00, 0x0FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x0FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x000FFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};

static const Xuint32 player_ducking2[] = {
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFF00FFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFF000000, 0x0000FFFF,
    0xFF000FFF, 0xFF000000, 0x0000000F, 0xF0000000, 0x000000FF,
    0xFF000000, 0x00000000, 0x00000000, 0x000FF000, 0x000000FF,
    0xFFF00000, 0x00000000, 0x00000000, 0x000FF000, 0x000000FF,
    0xFFFF0000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF,
    0xFFFF0000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF,
    0xFFFFF000, 0x00000000, 0x00000000, 0x00000000, 0x000000FF,
    0xFFFFFF00, 0x00000000, 0x00000000, 0x0000000F, 0xFFFFFFFF,
    0xFFFFFFF0, 0x00000000, 0x00000000, 0xFF000000, 0x000FFFFF,
    0xFFFFFFFF, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x00000000, 0x00FF0FFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x0FFFFF00, 0x00FF0000, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x0FFFFF00, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0x000FFF0F, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFF0F, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFF00, 0x0FFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};

static Sprite ducking1 = {
    player_ducking1,
    5,
    20
};

static Sprite ducking2 = {
    player_ducking2,
    5,
    20
};

static Sprite idle = {
    player_idle,
    PLAYER_WIDTH,
    PLAYER_HEIGHT
};

static Sprite dead = {
    player_dead,
    PLAYER_WIDTH,
    PLAYER_HEIGHT
};

static Sprite running1 = {
    player_running1,
    PLAYER_WIDTH,
    PLAYER_HEIGHT
};

static Sprite running2 = {
    player_running2,
    PLAYER_WIDTH,
    PLAYER_HEIGHT
};

Player player;

void init_player(uint32_t x, uint32_t y) {
    player.x = x;
    player.y = y;
    player.state = PLAYER_STATE_IDLE;
    player.animation = PLAYER_ANIMATION_IDLE;

    player.sprites[PLAYER_ANIMATION_IDLE] = &idle;
    player.sprites[PLAYER_ANIMATION_RUNNING_1] = &running1;
    player.sprites[PLAYER_ANIMATION_RUNNING_2] = &running2;
    player.sprites[PLAYER_ANIMATION_DUCKING_1] = &ducking1;
    player.sprites[PLAYER_ANIMATION_DUCKING_2] = &ducking2;
    player.sprites[PLAYER_ANIMATION_DEAD] = &dead;
}

void show_player() {
    show_sprite(player.sprites[player.animation], player.x, player.y);
}

void clear_player() {
    clear_sprite(player.sprites[player.animation], player.x, player.y);
}

void animate_player() {
    switch (player.state) {
    case PLAYER_STATE_IDLE:
    case PLAYER_STATE_JUMPING:
        player.animation = PLAYER_ANIMATION_IDLE;
        break;

    case PLAYER_STATE_RUNNING:
        if (player.animation != PLAYER_ANIMATION_RUNNING_1) {
            player.animation = PLAYER_ANIMATION_RUNNING_1;
        }
        else {
            player.animation = PLAYER_ANIMATION_RUNNING_2;
        }
        break;

    case PLAYER_STATE_DUCKING:
        if (player.animation != PLAYER_ANIMATION_DUCKING_1) {
            player.animation = PLAYER_ANIMATION_DUCKING_1;
        }
        else {
            player.animation = PLAYER_ANIMATION_DUCKING_2;
        }
        break;

    case PLAYER_STATE_DEAD:
        player.animation = PLAYER_ANIMATION_DEAD;
    }
}

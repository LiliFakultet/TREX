#include <stdbool.h>
#include "xio.h"
#include "xil_io.h"
#include "xparameters.h"
#include "input.h"
#include "player.h"
#include "config.h"

Xuint32 get_key() {
	return XIo_In32(XPAR_MY_PERIPHERAL_0_BASEADDR);
}

void handle_input() {
    static bool jumping = false;

    if (get_key() == UP_JOY && player.y == GROUND_LEVEL) {
        jumping = true;
        player.state = PLAYER_STATE_JUMPING;
    }

    if (get_key() == MIDDLE_JOY) {
        player.state = PLAYER_STATE_DUCKING;
        jumping = false;
    }
    else {
        if (player.y == GROUND_LEVEL) {
            player.state = PLAYER_STATE_RUNNING;
        }
        else {
            player.state = PLAYER_STATE_JUMPING;
        }
    }

    if (jumping) {
        if (player.y > GROUND_LEVEL - JUMP_HEIGHT) {
        	if (player.y > GROUND_LEVEL - JUMP_THRESHOLD) {
        		player.y -= JUMP_STEP;
        	}
        	else if (get_key() == UP_JOY) {
        		player.y -= JUMP_STEP;
        	}
        	else {
        		jumping = false;
        	}
        }
        else {
            jumping = false;
        }
    }

    if (!jumping) {
        if (player.y < GROUND_LEVEL) {
            player.y += JUMP_STEP;
        }
        else if (player.state == PLAYER_STATE_JUMPING) {
            player.state = PLAYER_STATE_RUNNING;
        }
    }
}

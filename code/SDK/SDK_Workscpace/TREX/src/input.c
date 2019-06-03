#include "input.h"
#include <stdbool.h>
#include "config.h"
#include "player.h"
#include "xil_io.h"
#include "xio.h"
#include "xparameters.h"

uint32_t get_key() {
    return XIo_In32(XPAR_MY_PERIPHERAL_0_BASEADDR);
}

void handle_input() {
    static bool jumping = false;

    // Start a jump
    if (get_key() == UP_JOY && player.y == GROUND_LEVEL) {
        jumping = true;
        player.state = PLAYER_STATE_JUMPING;
    }

    // Ducking always stops a jump
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

    // Rise
    if (jumping) {
        if (player.y > GROUND_LEVEL - JUMP_HEIGHT) {
            // JUMP_THRESHOLD is the minimum jump distance (unless interrupted
            // by ducking). After the threshold has been reached, the dinosaur
            // will only continue to climb higher if the up key hasn't been
            // released.
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

    // Fall
    if (!jumping) {
        if (player.y < GROUND_LEVEL) {
            player.y += JUMP_STEP;
        }
        else if (player.state == PLAYER_STATE_JUMPING) {
            player.state = PLAYER_STATE_RUNNING;
        }
    }
}

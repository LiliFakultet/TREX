#pragma once

#include <stdbool.h>
#include "sprite.h"

/* Almost every entity has a common set of operations which work very similarly.
 * The principles explained here are valid for pretty much any:
 *     init_*
 *     show_*
 *     clear_*
 *     animate_*
 *     move_*
 * They won't be documented individually
 */

// Maximum number of birds that can be on the screen at any time
#define MAX_BIRD_COUNT 3

#define BIRD_ANIMATION_COUNT 2

typedef struct Bird Bird;

/* Holds all data required to handle a bird.
 * active refers to whether or not a bird exists at that position in the birds
 * array.
 * animation is the index of the current sprite for that bird (0 or 1)
 */
struct Bird {
    int x;
    int y;
    bool active;
    int animation;
    Sprite *sprite;
};

extern Bird birds[MAX_BIRD_COUNT];

/* Initializes the birds array and marks all birds as inactive (none exist yet)
 */
void init_birds(void);

/* Move all birds one step to the left. Any bird that reaches the screen edge
 * disappears and is marked inactive.
 */
void move_birds(void);

/* Flap all birds' wings. This just flips the animation animation between 0 and 1
 */
void animate_birds(void);

/* Generate a new bird at a random height. If MAX_BIRD_COUNT has been reached
 * the function fails silently and has no effect.
 */
void add_bird(void);

/* sprite_show and sprite_clear wrappers that show/hide all living birds
 */
void show_birds(void);
void clear_birds(void);

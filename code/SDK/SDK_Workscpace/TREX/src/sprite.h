#pragma once

#include <stdint.h>
#include "vga.h"

typedef struct Sprite Sprite;

/* Represents an image that can be drawn on the screen.
 * image is an array of size (height * width) and holds the compressed image
 * exported by our Python script.
 * height is in pixels, width is the width in pixels divided by 8
 */
struct Sprite {
    const uint32_t *image;
    const int width;
    const int height;
};

/* Draw a sprite at the given coordinates. x and y refer to the bottom left
 * corner of the sprite.
 */
void show_sprite(const Sprite *sprite, int x, int y);

/* Clear sprite from given coordinates. The rectangle that used to be the sprite
 * gets filled with the background color (index 15 in the pallete).
 */
void clear_sprite(const Sprite *sprite, int x, int y);

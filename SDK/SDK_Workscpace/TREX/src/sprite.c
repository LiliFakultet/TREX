#include "sprite.h"
#include "vga.h"

void show_sprite(const Sprite *sprite, int x, int y) {
    int i;
    int j;

    /* Our sprite origin is in the bottom left corner to make positioning
     * easier, but we draw them relative to the top left corner. This moves
     * the origin point up.
     */
    y -= sprite->height;

    for (i = 0; i < sprite->width; i++) {
        for (j = 0; j < sprite->height; j++) {
            const int index = (y + j) * DISPLAY_WIDTH + (x + i);
            const uint32_t sprite_color = sprite->image[j * sprite->width + i];

            PUT_TO_FSL(index, sprite_color);
        }
    }
}

void clear_sprite(const Sprite *sprite, int x, int y) {
    int i;
    int j;

    y -= sprite->height;

    for (i = 0; i < sprite->width; i++) {
        for (j = 0; j < sprite->height; j++) {
            const int index = (y + j) * DISPLAY_WIDTH + (x + i);

            PUT_TO_FSL(index, 0xFFFFFFFF);
        }
    }
}

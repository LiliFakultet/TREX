#include "sprite.h"
#include "fsl.h"

//Xuint32 background[480 * 640 / 8];

void show_sprite(const Sprite *sprite, int x, int y) {
	int i;
	int j;

    y -= sprite->height;

    for (i = 0; i < sprite->width; i++) {
        for (j = 0; j < sprite->height; j++) {
        	int offset;

            const int index = (y + j) * (640 / 8) + (x + i);
            const uint32_t sprite_color = sprite->image[j * sprite->width + i];
            uint32_t out_color = 0;
            for (offset = 28; offset >= 0; offset -= 4) {
            	uint8_t nibble = (sprite_color >> offset) & 0xF;
                if (nibble == 0xF) {
                    //nibble = (background[index] >> offset) & 0xF;
                }

                out_color = (out_color << 4) | nibble;
            }

            PUT_TO_FSL(index, out_color);
        }
    }
}

void clear_sprite(const Sprite *sprite, int x, int y) {
	int i;
	int j;

    y -= sprite->height;

    for (i = 0; i < sprite->width; i++) {
        for (j = 0; j < sprite->height; j++) {
        	const int index = (y + j) * (640 / 8) + (x + i);
            //PUT_TO_FSL(index, background[index]);
        	PUT_TO_FSL(index, 0xFFFFFFFF);
        }
    }
}

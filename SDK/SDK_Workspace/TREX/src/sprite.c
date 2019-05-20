#include "sprite.h"
#include "fsl.h"

Xuint32 background[480 * 640 / 8];

void show_sprite(const Sprite *sprite, Xuint32 x, Xuint32 y) {
	Xuint32 i;
	Xuint32 j;

    y -= sprite->height;

    for (i = 0; i < sprite->width; i++) {
        for (j = 0; j < sprite->height; j++) {
        	Xint32 offset;

            const Xuint32 index = (y + j) * (640 / 8) + (x + i);
            const Xuint32 sprite_color = sprite->image[j * sprite->width + i];
            Xuint32 out_color = 0;
            for (offset = 28; offset >= 0; offset -= 4) {
            	Xuint8 nibble = (sprite_color >> offset) & 0xF;
                if (nibble == 0xF) {
                    //nibble = (background[index] >> offset) & 0xF;
                }

                out_color = (out_color << 4) | nibble;
            }

            PUT_TO_FSL(index, out_color);
        }
    }
}

void clear_sprite(const Sprite *sprite, Xuint32 x, Xuint32 y) {
	Xuint32 i;
	Xuint32 j;

    y -= sprite->height;

    for (i = 0; i < sprite->width; i++) {
        for (j = 0; j < sprite->height; j++) {
        	Xuint32 index = (y + j) * (640 / 8) + (x + i);
            //PUT_TO_FSL(index, background[index]);
        	PUT_TO_FSL(index, 0xFFFFFFFF);
        }
    }
}

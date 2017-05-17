/*
 * SI_draw.h
 *
 *  Created on: 16.06.2015.
 *      Author: student
 */

#ifndef SI_DRAW_H_
#define SI_DRAW_H_

#include "SI_defines.h"
#include "SI_globals.h"

#define ROW 26
#define COL 3


void draw_square(Xuint32, Xuint8, Xuint8);
void draw_invader(Xuint32, Xuint8, Xuint8, Xuint8);
void draw_ship(Xuint32, Xuint8, Xuint8);
void draw_projectile(Xuint32, Xuint8, Xuint8);
void draw_invader_projectile(Xuint32, Xuint8, Xuint8);
void erase_projectile(Xuint32, Xuint8, Xuint8);
void erase_square(Xuint32, Xuint8, Xuint8);
void clear_graphics_screen(Xuint32);
void draw_X(Xuint32, Xuint8, Xuint8);
void erase_X(Xuint32, Xuint8, Xuint8);
void draw_red(Xuint32, Xuint8, Xuint8, Xuint8);
void draw_asteroid(Xuint32 BaseAddress, Xuint8 x_crdnt, Xuint8 y_crdnt);
void draw_bitmap(Xuint32 BaseAddress, Xuint8 x_crdnt,Xuint8 y_crdnt, Xuint32 bitmap[ROW][COL]);

#endif /* SI_DRAW_H_ */


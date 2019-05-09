/*
 * SI_logic.h
 *
 *  Created on: 16.06.2015.
 *      Author: student
 */

#ifndef SI_LOGIC_H_
#define SI_LOGIC_H_

#include "SI_defines.h"
#include "SI_globals.h"
#include "SI_draw.h"

Xint8 ship_hit_projectile(int);
void move_spaceship(Xuint8*);
Xint8 projectile_hit_invader(int, int);
void move_projectile_from_ship();
void move_projectile_from_invader();
Xint8 invader_hit_projectile(int, int);
void move_invaders_row(Xuint8*, Xuint8*, Xuint8*, int);
Xint8 invader_hit_projectile_down(int, int);
Xint8 projectile_hit_projectile(int, int);
Xint8 projectile_hit_ship(int, int);
void move_invaders_down(Xuint8*, Xuint8);
void shoot_projectile_from_ship(Xuint8);
void shoot_projectile_from_invader(Xuint8, Xuint8*);
void generate_init_invaders_positions();




/*
 * generate_field , generate_player , fire_shot , destroy_asteriod , destroy_player , get_player_angle
 *
 * */


#endif /* SI_LOGIC_H_ */

/*
 * SI_init.h
 *
 *  Created on: 16.06.2015.
 *      Author: student
 */

#ifndef SI_INIT_H_
#define SI_INIT_H_

#include "SI_globals.h"
#include "SI_defines.h"
#include <stdlib.h>
#include <time.h>

void vga_interrupt_handler(void*);
void init_interrupt_controller();

#endif /* SI_INIT_H_ */

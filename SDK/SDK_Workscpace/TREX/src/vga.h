#pragma once

#include "fsl.h"

#define DISPLAY_HEIGHT 480
#define DISPLAY_WIDTH 80

#define PUT_TO_FSL(address, value) \
	do {                           \
		putfsl(address, 0);        \
		putfsl(value, 0);          \
	} while(0)


void init_vga(void);
void init_vga_interrupt(void (*irq_handler)(void *));

void clear_text_screen(void);
void reset_score_text();
void print_score(int score);
void print_high_score(int high_score);
void print_game_over();
void print_cheat_mode();
void clear_cheat_mode();

void clear_graphics_screen(void);
void night_mode(void);
void day_mode(void);

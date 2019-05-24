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
void print_string(const char *string, int length);
void set_cursor(int position);

void clear_graphics_screen(void);
void night_mode(void);
void day_mode(void);

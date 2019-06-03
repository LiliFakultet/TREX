#pragma once

#include "fsl.h"

#define DISPLAY_HEIGHT 480 // Height in pixels
#define DISPLAY_WIDTH 80   // Width in addressible locations. 640 / 8 = 80

// Macro for writing data to VGA graphical memory through the FSL.
// inherited from previous project
#define PUT_TO_FSL(address, value) \
    do {                           \
        putfsl(address, 0);        \
        putfsl(value, 0);          \
    } while (0)

// Initialize VGA mode and colors
void init_vga(void);

// Sets up and enables interrupts
void init_vga_interrupt(void (*irq_handler)(void *));

// A bit of a lie: this clears the text but also prints the "no connection"
// message that's always on the screen
void clear_text_screen(void);

// Resets the string that holds the score. Should be done in main to clear
// high score when a hardware reset happens
void reset_score_text();

void print_score(int score);
void print_high_score(int high_score);

void print_game_over();

// Displays whether the no collision mode is active
void print_cheat_mode();
void clear_cheat_mode();

void clear_graphics_screen(void);
void night_mode(void); // Swaps colour pallete to make the game dark
void day_mode(void);   // Swaps colour pallete to make the game light

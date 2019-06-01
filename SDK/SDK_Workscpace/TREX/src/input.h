#pragma once

// Inherited from previous projects
#define LEFT_JOY 23
#define MIDDLE_JOY 27
#define RIGHT_JOY 29
#define DOWN_JOY 30
#define UP_JOY 15
#define NO_INPUT 31

// Checks joystick input and returns one of the values defined above
Xuint32 get_key();

// Move player based on current input
void handle_input();

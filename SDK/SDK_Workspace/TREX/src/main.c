#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"
#include "player.h"
#include "sprite.h"
#include "cactus.h"
#include "xparameters.h"
#include "xil_io.h"
#include "xio.h"
#include "xintc.h"
#include "collision.h"
#include "input.h"

#define ANIMATION_DELAY 2
#define CACTUS_DELAY 4
#define CACTUS_CREATION_DELAY ((CACTUS_DELAY) * (8))
#define PLAYER_DELAY 3

#define GRAPHICS_MEM_OFF 0x2000000
#define TEXT_MEM_OFF 0x1000000

#define VGA_PERIPH_MEM_mWriteMemory(Address, Data) \
 	Xil_Out32(Address, (Xuint32)(Data))

static XIntc xintc;
static Xuint32 cursor_position;

void clear_text_screen(Xuint32 BaseAddress)
{
   	int i;

    for (i = 0; i < 4800; i++)
    {
        VGA_PERIPH_MEM_mWriteMemory(BaseAddress + TEXT_MEM_OFF + i*4, 0x20);
    }
}

void print_string(Xuint32 BaseAddress, char string_s[], int lenght)
{
    int i;

    for (i = 0; i < lenght; i++)
    {
        VGA_PERIPH_MEM_mWriteMemory(BaseAddress + TEXT_MEM_OFF + cursor_position + i*4, (string_s[i]-0x40));
    }
}

void set_cursor(Xuint32 new_value)
{
    cursor_position = new_value;
}

#define PUT_TO_FSL(address, value) \
	do {                           \
		putfsl(address, 0);        \
		putfsl(value, 0);          \
	} while(0)

static void clear_graphics_screen(Xuint32 BaseAddress)
{
	int i;
	for (i = 0; i < 9600*4; i++){
	    PUT_TO_FSL(i, 0xFFFFFFFF);
	}
}

volatile static bool game_running = false;
volatile int ticks = 0;
volatile int score = 0;
volatile int high_score = 0;

char score_text[14] = "         00000";
void vga_interrupt_handler(void *arg) {
    (void)arg;

    ++ticks;

    if (!game_running) {
        return;
    }

    score = ticks / 20;
    if (score > high_score) {
    	high_score = score;
    }

    clear_player();
    clear_cacti();

    if (ticks % CACTUS_CREATION_DELAY == 0 && rand() % 10 == 0) {
    	add_cactus();
    }

	if (ticks % PLAYER_DELAY == 0) {
	    handle_input();
	}

    if (ticks % CACTUS_DELAY == 0) {
        move_cacti();
    }

    if (check_collisions()) {
        game_running = false;
        player.state = PLAYER_STATE_DEAD;
        animate_player();
        show_player();
        show_cacti();

        score_text[7] = '0' + high_score % 10;
        score_text[6] = '0' + high_score / 10  % 10;
        score_text[5] = '0' + high_score / 100 % 10;
        score_text[4] = '0' + high_score / 1000 % 10;
        score_text[3] = '0' + high_score / 10000 % 10;
        score_text[1] = 'I';
        score_text[0] = 'H';

    	print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, score_text, 5);
        while (get_key() != NO_INPUT) {

		}
        while (get_key() != UP_JOY && get_key() != MIDDLE_JOY) {

        }

        ticks = 0;
        game_running = true;
        player.state = PLAYER_STATE_RUNNING;

        clear_player();
        clear_cacti();

        init_player(10, 240);
        init_cacti();

    }

    if (ticks % ANIMATION_DELAY == 0) {
        animate_player();
    }

    score_text[13] = '0' + score % 10;
    score_text[12] = '0' + score / 10  % 10;
    score_text[11] = '0' + score / 100 % 10;
    score_text[10] = '0' + score / 1000 % 10;
    score_text[9] = '0' + score / 10000 % 10;
	print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, score_text, 14);

    show_player();
    show_cacti();
}

static
void init_interrupt_controller()
{
	XStatus Status;
	XIo_Out32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x54, 479);
	XIo_Out32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x58, 1);

	//initialize interrupt controller
	Status = XIntc_Initialize (&xintc, XPAR_INTC_0_DEVICE_ID);
	if (Status != XST_SUCCESS)
		xil_printf ("\r\nInterrupt controller initialization failure");
	else
		xil_printf("\r\nInterrupt controller initialized");

	// Connect interrupt_handler
	Status = XIntc_Connect (&xintc, 0, (XInterruptHandler) vga_interrupt_handler, (void *)0);

	if (Status != XST_SUCCESS)
		xil_printf ("\r\nRegistering MY_TIMER Interrupt Failed");
	else
		xil_printf("\r\nMY_TIMER Interrupt registered");

	//Start the interrupt controller in real mode
	Status = XIntc_Start(&xintc, XIN_REAL_MODE);

	//Enable interrupt controller
	XIntc_Enable (&xintc, 0);
	microblaze_enable_interrupts();
}

static void init_colors()
{
	/* Define colors */
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x10, 0x555555);	//color 0
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x14, 0xDDDDDD);	//color 1
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x18, 0xFF0000);	//color 2
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x1C, 0xFF0000);	//color 3 siva
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x20, 0xFF0000);	//color 4
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x24, 0xFF00FF);	//color 5
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x28, 0xFF00FF);	//color 6
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x2C, 0xFF00FF);	//color 7
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x30, 0xFF00FF);	//color 8
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x34, 0xFF00FF);	//color 9
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x38, 0xFF00FF);	//color 10 A
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x3C, 0xFF00FF);	//color 11 B
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x40, 0xFF00FF);	//color 12 C
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x44, 0xFF00FF);	//color 13 D
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x48, 0x555555);	// Text color
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x4C, 0xFFFFFF);	//color 15 F
}

int main() {
    init_platform();
    init_colors();
    //display and text mode
    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 3);
	clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
	clear_graphics_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);

	init_interrupt_controller();

    init_player(10, 240);
    init_cacti();

    add_cactus();

    show_player();
    show_cacti();

    set_cursor(4713);
    print_string(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR, score_text, 14);

    while (get_key() != UP_JOY && get_key() != MIDDLE_JOY) {

    }

    srand(ticks);
    ticks = 0;
    game_running = true;
    player.state = PLAYER_STATE_RUNNING;

    while (1) {

    }
}

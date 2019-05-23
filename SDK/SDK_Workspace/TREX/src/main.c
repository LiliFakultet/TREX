#include <stdbool.h>
#include <stdlib.h>
#include "platform.h"
#include "player.h"
#include "sprite.h"
#include "cactus.h"
#include "xparameters.h"
#include "xil_io.h"
#include "xio.h"
#include "xintc.h"

#define ANIMATION_DELAY 2
#define CACTUS_DELAY 4
#define CACTUS_CREATION_DELAY ((CACTUS_DELAY) * (4))
#define PLAYER_DELAY 3

#define LEFT_JOY 23
#define MIDDLE_JOY 27
#define RIGHT_JOY 29
#define DOWN_JOY 30
#define UP_JOY 15

#define GRAPHICS_MEM_OFF 0x2000000
#define TEXT_MEM_OFF 0x1000000

#define VGA_PERIPH_MEM_mWriteMemory(Address, Data) \
 	Xil_Out32(Address, (Xuint32)(Data))

static XIntc xintc;

#define PUT_TO_FSL(address, value) \
	do {                           \
		putfsl(address, 0);        \
		putfsl(value, 0);          \
	} while(0)

static Xuint32 get_key() {
	return XIo_In32(XPAR_MY_PERIPHERAL_0_BASEADDR);
}

static void handle_input() {
    static bool jumping = false;

    if (get_key() == UP_JOY && player.y == 240) {
        jumping = true;
        player.state = PLAYER_STATE_JUMPING;
    }

    if (get_key() == MIDDLE_JOY) {
        player.state = PLAYER_STATE_DUCKING;
        jumping = false;
    }
    else {
        if (player.y == 240) {
            player.state = PLAYER_STATE_RUNNING;
        }
        else {
            player.state = PLAYER_STATE_JUMPING;
        }
    }

    if (jumping) {
        if (player.y > 480 / 2 - 100) {
            player.y -= 5;
        }
        else {
            jumping = false;
        }
    }

    if (!jumping) {
        if (player.y < 480 / 2) {
            player.y += 5;
        }
        else if (player.state == PLAYER_STATE_JUMPING) {
            player.state = PLAYER_STATE_RUNNING;
        }
    }
}

static void clear_graphics_screen(Xuint32 BaseAddress)
{
	int i;
	for (i = 0; i < 9600*4; i++){
	    PUT_TO_FSL(i, 0xFFFFFFFF);
	}
}

static void clear_text_screen(Xuint32 BaseAddress)
{
   	int i;

    for (i = 0; i < 4800; i++)
    {
        VGA_PERIPH_MEM_mWriteMemory(BaseAddress + TEXT_MEM_OFF + i*4, 0x20);
    }
}

volatile static bool game_running = false;
volatile int ticks = 0;
void vga_interrupt_handler(void *arg) {
    (void)arg;

    if (!game_running) {
        return;
    }

    clear_player();
    clear_cacti();

//    if (ticks % ANIMATION_DELAY == 0) {
//    	animate_player();
//
//        if (player.x < 80) {
//        	++(player.x);
//        }
//        else {
//        	player.x = 0;
//        }
//
//    }

    if (ticks % CACTUS_CREATION_DELAY == 0 && rand() % 10 == 0) {
    	add_cactus();
    }

	if (ticks % PLAYER_DELAY == 0) {
	    handle_input();
	}

    if (ticks % CACTUS_DELAY == 0) {
        move_cacti();
    }

    if (ticks % ANIMATION_DELAY == 0) {
        animate_player();
    }

    show_player();
    show_cacti();

    ++ticks;
}

static
void init_interrupt_controller()
{
	XStatus Status;
	XIo_Out32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x54, 479); //init terminal counter on 524
	XIo_Out32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x58, 1);		//enable timer

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
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x18, 0xFF00FF);	//color 2
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x1C, 0xFF00FF);	//color 3 siva
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x20, 0xFF00FF);	//color 4
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x24, 0xFF00FF);	//color 5
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x28, 0xFF00FF);	//color 6
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x2C, 0xFF00FF);	//color 7
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x30, 0xFF00FF);	//color 8
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x34, 0xFF00FF);	//color 9
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x38, 0xFF00FF);	//color 10 A
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x3C, 0xFF00FF);	//color 11 B
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x40, 0xFF00FF);	//color 12 C
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x44, 0xFF00FF);	//color 13 D
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x48, 0xFF00FF);	//color 14 E
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

    while (get_key() != UP_JOY && get_key() != MIDDLE_JOY) {

    }
    game_running = true;
    player.state = PLAYER_STATE_RUNNING;

    while (1) {

    }
}

/*
 * Copyright (c) 2009-2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "fsl.h"
#include "xintc.h"
#include "xio.h"

#define VGA_PERIPH_MEM_mWriteMemory(Address, Data) \
 	Xil_Out32(Address, (Xuint32)(Data))
#define VGA_PERIPH_MEM_mReadMemory(Address) \
 	Xil_In32(Address)

#define LEFT_JOY 23
#define MIDDLE_JOY 27
#define RIGHT_JOY 29
#define DOWN_JOY 30
#define UP_JOY 15


#define PUT_TO_FSL(address, value) \
	do{ \
		putfsl(address, 0); \
		putfsl(value, 0); \
	}while(0)


void vga_interrupt_handler(void *BaseAddress);

XIntc Intc;

void init_interrupt_controller()
{
	XStatus Status;

	XIo_Out32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x54, 0x1E0); //init terminal counter on 524
	XIo_Out32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x58, 1);		//enable timer

	//initialize interrupt controller
	Status = XIntc_Initialize (&Intc, XPAR_INTC_0_DEVICE_ID);
	if (Status != XST_SUCCESS)
		xil_printf ("\r\nInterrupt controller initialization failure");
	else
		xil_printf("\r\nInterrupt controller initialized");

	// Connect interrupt_handler
	Status = XIntc_Connect (&Intc, 0, (XInterruptHandler) vga_interrupt_handler, (void *)0);

	if (Status != XST_SUCCESS)
		xil_printf ("\r\nRegistering MY_TIMER Interrupt Failed");
	else
		xil_printf("\r\nMY_TIMER Interrupt registered");

	//Start the interrupt controller in real mode
	Status = XIntc_Start(&Intc, XIN_REAL_MODE);

	//Enable interrupt controller
	XIntc_Enable (&Intc, 0);
	microblaze_enable_interrupts();
}

/* color - indeksira 8 piksela, svaki ima boju [0-15]
 * x - [0..79]
 * y - [0..479]
 */
void draw_bitmap(Xuint32 color, Xuint32 x_crdnt, Xuint32 y_crdnt)
{
	PUT_TO_FSL(y_crdnt * (640 / 8) + x_crdnt, color);
}

void init_colors()
{
	/* Define colors */
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x10, 0x000000);	//color 0
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x14, 0x808080);	//color 1
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x18, 0xffffff);	//color 2
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x1C, 0xa0a0a0);	//color 3 siva
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x20, 0x00ffff);	//color 4
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x24, 0xff00ff);	//color 5
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x28, 0xffff00);	//color 6
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x2C, 0x000000);	//color 7
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x30, 0xffffff);	//color 8
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x34, 0xff1493);	//color 9
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x38, 0xff6666);	//color 10 A
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x3C, 0x556b2f);	//color 11 B
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x40, 0x191970);	//color 12 C
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x44, 0xb8860b);	//color 13 D
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x48, 0xffe4c4);	//color 14 E
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x4C, 0xd2691e);	//color 15 F
}

void clear_graphics_screen(Xuint32 BaseAddress)
{
	int i;
	for (i = 0; i < 9600*4; i++){
	    PUT_TO_FSL(i, 0x33333333);
	}
}

void clear_text_screen(Xuint32 BaseAddress)
{
   	int i;

    for (i = 0; i < 4800; i++)
    {
        VGA_PERIPH_MEM_mWriteMemory(BaseAddress + 0x1000000 + i*4, 0x20);
    }
}

volatile int j = 0;
void vga_interrupt_handler(void *BaseAddress) {
	int i;
	for (i = 0; i < 80; i++) {
		draw_bitmap(0x33333333, i, j);
	}

	j++;
	if (j == 480) {
		j = 0;
	}

	for (i = 0; i < 80; i++) {
		draw_bitmap(0x55555555, i, j);
	}

	int input= Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR);
	switch (input) {
	case UP_JOY:
		print("up");
		break;
	case MIDDLE_JOY:
		print("down");
		break;
	}
}

int main()
{
    init_platform();
	init_colors();
	clear_graphics_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);
	init_interrupt_controller();


	clear_text_screen(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR);

	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0b11); //display and text mode


	int i;
    while (1) {
    }

    return 0;
}
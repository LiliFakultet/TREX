#include "vga.h"
#include "xintc.h"
#include "xparameters.h"
#include "xio.h"
#include "xil_io.h"
#include "fsl.h"

#define GRAPHICS_MEM_OFF 0x2000000
#define TEXT_MEM_OFF 0x1000000

static XIntc xintc;
static Xuint32 cursor_position;

#define VGA_PERIPH_MEM_mWriteMemory(Address, Data) Xil_Out32((Address), (Xuint32)(Data))

// TODO: izmeni i boju teksta
void night_mode(void) {
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x10, 0xDDDDDD);	// Main color
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x14, 0x555555);	// Detail color
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x4C, 0x000000);	// Background color
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x48, 0xDDDDDD);	// Text color
}

void day_mode(void) {
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x10, 0x555555);	// Main color
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x14, 0xDDDDDD);	// Detail color
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x4C, 0xFFFFFF);	// Background color
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x48, 0x555555);	// Text color
}

void init_vga(void) {
    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 3); // Text and graphics mode
    day_mode();

    // Other colors are unused for now:
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x18, 0xFF00FF);
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x1C, 0xFF00FF);
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x20, 0xFF00FF);
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x24, 0xFF00FF);
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x28, 0xFF00FF);
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x2C, 0xFF00FF);
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x30, 0xFF00FF);
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x34, 0xFF00FF);
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x38, 0xFF00FF);
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x3C, 0xFF00FF);
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x40, 0xFF00FF);
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x44, 0xFF00FF);

	clear_text_screen();
	clear_graphics_screen();

	set_cursor(4713);
}

void init_vga_interrupt(void (*irq_handler)(void *)) {
	XIo_Out32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x54, 479);
	XIo_Out32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x58, 1);

	XIntc_Initialize (&xintc, XPAR_INTC_0_DEVICE_ID);
	XIntc_Connect (&xintc, 0, (XInterruptHandler) irq_handler, NULL);
	XIntc_Start(&xintc, XIN_REAL_MODE);
	XIntc_Enable (&xintc, 0);

	microblaze_enable_interrupts();
}

void clear_text_screen(void) {
   	int i;

    for (i = 0; i < 4800; i++) {
        VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + TEXT_MEM_OFF + 4 * i, 0x20);
    }
}

void clear_graphics_screen(void) {
	int i;
	for (i = 0; i < DISPLAY_HEIGHT * DISPLAY_WIDTH; i++){
	    PUT_TO_FSL(i, 0xFFFFFFFF);
	}
}

void set_cursor(int position) {
    cursor_position = position;
}

void print_string(const char *string, int length) {
	int i;
	for (i = 0; i < length; i++) {
		VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + TEXT_MEM_OFF + cursor_position + 4 * i, (string[i] - 0x40));
	}
}

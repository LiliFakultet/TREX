#include "vga.h"
#include "config.h"
#include "fsl.h"
#include "xil_io.h"
#include "xintc.h"
#include "xio.h"
#include "xparameters.h"

#define GRAPHICS_MEM_OFF 0x2000000
#define TEXT_MEM_OFF 0x1000000

static XIntc xintc;
static Xuint32 cursor_position;
static char score_text[14] = "         00000";

#define VGA_PERIPH_MEM_mWriteMemory(Address, Data) Xil_Out32((Address), (Xuint32)(Data))

static void set_cursor(int position) {
    cursor_position = position;
}

static void print_string(const char *string, int length) {
    int i;
    for (i = 0; i < length; i++) {
        VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + TEXT_MEM_OFF + cursor_position + 4 * i,
                                    (string[i] - 0x40));
    }
}

void night_mode(void) {
    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x10, 0xDDDDDD); // Main color
    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x14, 0x555555); // Detail color
    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x4C, 0x000000); // Background color
    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x48, 0xDDDDDD); // Text color
}

void day_mode(void) {
    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x10, 0x555555); // Main color
    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x14, 0xDDDDDD); // Detail color
    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x4C, 0xFFFFFF); // Background color
    VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x48, 0x555555); // Text color
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
}

void init_vga_interrupt(void (*irq_handler)(void *)) {
    XIo_Out32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x54, 479); // TC value for interrupt
    XIo_Out32(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x58, 1);   // Enable interrupt

    XIntc_Initialize(&xintc, XPAR_INTC_0_DEVICE_ID);
    XIntc_Connect(&xintc, 0, (XInterruptHandler)irq_handler, NULL);
    XIntc_Start(&xintc, XIN_REAL_MODE);
    XIntc_Enable(&xintc, 0);

    microblaze_enable_interrupts();
}

void clear_text_screen(void) {
    int i;

    for (i = 0; i < 4800; i++) {
        VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + TEXT_MEM_OFF + 4 * i, 0x20);
    }

    set_cursor(11550);
    print_string("UNABLE TO CONNECT TO THE INTERNET", 33);
    set_cursor(13470);
    print_string("GOOGLE CHROME CAN'T DISPLAY THE WEBPAGE BECAUSE YOUR FPGA", 57);
    set_cursor(14430);
    print_string("ISN'T CONNECTED TO THE INTERNET.", 32);
}

void clear_graphics_screen(void) {
    int i;
    for (i = 0; i < DISPLAY_HEIGHT * DISPLAY_WIDTH; i++) {
        PUT_TO_FSL(i, 0xFFFFFFFF);
    }
}

void print_score(int score) {
    int i;

    for (i = 0; i < 5; i++) {
        score_text[13 - i] = '0' + score % 10;
        score /= 10;
    }

    set_cursor(SCORE_LOCATION);
    print_string(score_text, 14);
}

void print_high_score(int high_score) {
    int i;

    if (high_score == 0) {
        return;
    }

    for (i = 0; i < 5; i++) {
        score_text[7 - i] = '0' + high_score % 10;
        high_score /= 10;
    }

    score_text[0] = 'H';
    score_text[1] = 'I';

    set_cursor(SCORE_LOCATION);
    print_string(score_text, 14);
}

void reset_score_text() {
    int i;
    for (i = 0; i < 14; i++) {
        score_text[i] = ' ';
    }
}

void print_game_over() {
    set_cursor(GAME_OVER_LOCATION);
    print_string("GAME OVER", 9);
}

void print_cheat_mode() {
    set_cursor(CHEAT_MODE_LOCATION);
    print_string("NO COLLISIONS", 13);
}

void clear_cheat_mode() {
    set_cursor(CHEAT_MODE_LOCATION);
    print_string("             ", 13);
}

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <include/interrupts/isr.h>
#include "input.h"

uint8_t mouse_pointer[] = {
    0b11111111, 0b11100000,
    0b11111111, 0b10000000,
    0b11111110, 0b00000000,
    0b11111100, 0b00000000,
    0b11111000, 0b00000000,
    0b11110000, 0b00000000,
    0b11100000, 0b00000000,
    0b11000000, 0b00000000,
    0b11000000, 0b00000000,
    0b10000000, 0b00000000,
    0b10000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
    0b00000000, 0b00000000,
};

int mouse_x = 0, mouse_y = 0;
int mouse_x_old = 0, mouse_y_old = 0;
mouse_status g_status;
int mouse_possessed_task_id = 0;

int mouse_get_x() {
    return mouse_x;
}

int mouse_get_y() {
    return mouse_y;
}

void mouse_wait(bool type) {
    uint32_t Timeout = 100000;
    if (type == false) {

        while (Timeout--) {
            if ((inportb(PS2_CMD_PORT) & 1) == 1) {
                return;
            }
        }
        return;
    } else {
        while (Timeout--) {
            if ((inportb(PS2_CMD_PORT) & 2) == 0) {
                return;
            }
        }
    }
}

void mouse_write(uint8_t data) {
    mouse_wait(true);
    outportb(PS2_CMD_PORT, 0xD4);
    mouse_wait(true);

    outportb(MOUSE_DATA_PORT, data);
}

uint8_t mouse_read() {
    mouse_wait(false);
    return inportb(MOUSE_DATA_PORT);
}

void get_mouse_status(char StatusByte, mouse_status *status) {
    memset(status, 0, sizeof(mouse_status));
    if (StatusByte & 0x01)
        status->left_button = 1;
    if (StatusByte & 0x02)
        status->right_button = 1;
    if (StatusByte & 0x04)
        status->middle_button = 1;
    if (StatusByte & 0x08)
        status->always_1 = 1;
    if (StatusByte & 0x10)
        status->x_sign = 1;
    if (StatusByte & 0x20)
        status->y_sign = 1;
    if (StatusByte & 0x40)
        status->x_overflow = 1;
    if (StatusByte & 0x80)
        status->y_overflow = 1;
}

void mouse_handler(registers *r) {
    static uint8_t mouse_cycle = 0;
    static char mouse_byte[3];

    switch (mouse_cycle) {
        case 0:
            mouse_byte[0] = mouse_read();
            get_mouse_status(mouse_byte[0], &g_status);
            mouse_cycle++;
            break;
        case 1:
            mouse_byte[1] = mouse_read();
            mouse_cycle++;
            break;
        case 2:
            mouse_byte[2] = mouse_read();
            mouse_x = mouse_x + mouse_byte[1];
            mouse_y = mouse_y - mouse_byte[2];

            if (mouse_x < 0)
                mouse_x = 0;
            if (mouse_y < 0)
                mouse_y = 0;
            if (mouse_x > 800)
                mouse_x = 800 - 1;
            if (mouse_y > 600)
                mouse_y = 600 - 1;

            mouse_x_old = mouse_x;
            mouse_y_old = mouse_y;
            mouse_cycle = 0;
            break;
    }
    isr_end_interrupt(IRQ_BASE + 12);
}


/**
 * available rates 10, 20, 40, 60, 80, 100, 200
 */
void set_mouse_rate(uint8_t rate) {
    uint8_t status;

    outportb(MOUSE_DATA_PORT, MOUSE_CMD_SAMPLE_RATE);
    status = mouse_read();
    if(status != MOUSE_ACKNOWLEDGE) {
        return;
    }
    outportb(MOUSE_DATA_PORT, rate);
    status = mouse_read();
    if(status != MOUSE_ACKNOWLEDGE) {
        return;
    }
}

void init_mouse() {
    uint8_t status;

    mouse_x = 5;
    mouse_y = 2;

    mouse_wait(true);
    outportb(PS2_CMD_PORT, 0xA8);

    outportb(MOUSE_DATA_PORT, MOUSE_CMD_MOUSE_ID);
    status = mouse_read();
    set_mouse_rate(80);

    outportb(MOUSE_DATA_PORT, MOUSE_CMD_RESOLUTION);
    outportb(MOUSE_DATA_PORT, 0);

    mouse_wait(true);
    outportb(PS2_CMD_PORT, 0x20);
    mouse_wait(false);

    status = (inportb(MOUSE_DATA_PORT) | 2);

    mouse_wait(true);
    outportb(PS2_CMD_PORT, MOUSE_DATA_PORT);
    mouse_wait(true);
    outportb(MOUSE_DATA_PORT, status);

    mouse_write(MOUSE_CMD_SET_DEFAULTS);
    status = mouse_read();

    mouse_write(MOUSE_CMD_ENABLE_PACKET_STREAMING);
    status = mouse_read();
    if(status != MOUSE_ACKNOWLEDGE) {
        return;
    }

    isr_register_interrupt_handler(IRQ_BASE + 12, mouse_handler);
}

static char key_buffer[256];

int keyboard_x;

#define back_space 0x0E
#define enter 0x1C

const char keyboard_map[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',
  	'9', '0', '-', '=', '\b',
  	'\t',
  	'q', 'w', 'e', 'r',
  	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
  	  0,
  	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
 '	\'', '`',   0,
 '	\\', 'z', 'x', 'c', 'v', 'b', 'n',
  	'm', ',', '.', '/',   0,
  	'*',
  	  0,
  	' ',
  	  0,
  	  0,
  	  0,   0,   0,   0,   0,   0,   0,   0,
  	  0,
  	  0,
  	  0,
  	  0,
  	  0,
  	  0,
  	'-',
  	  0,
  	  0,
  	  0,
  	'+',
  	  0,
  	  0,
  	  0,
  	  0,
  	  0,
  	  0,   0,   0,
  	  0,
  	  0,
  	  0,
};

void keyboard_handler(struct registers *r) {
    unsigned char scancode;

    scancode = inportb(0x60);
    if (scancode & 0x80) {
    } else {
        put_character(keyboard_map[scancode], keyboard_x, 15, 255, 255, 255);
		keyboard_x += 16;
    }
}

void init_keyboard() {
	isr_register_interrupt_handler(IRQ_BASE + 1, keyboard_handler);
}
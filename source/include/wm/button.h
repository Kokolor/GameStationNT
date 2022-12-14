#ifndef BUTTON_H
#define BUTTON_H

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <include/interrupts/input/input.h>
#include <include/vbe/vbe.h>

int draw_button(int x, int y, int width, int height, int r, int g, int b, char* text, int r1, int g1, int b1, int task_id);

#endif
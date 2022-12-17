#ifndef WINDOW_H
#define WINDOW_H

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <include/interrupts/input/input.h>
#include <include/vbe/vbe.h>

int draw_close_button(int x, int y, int radius, int r, int g, int b, int task_id);
int draw_window(int* x, int* y, int* width, int* height, int* mouse_held, int task_id);

#endif
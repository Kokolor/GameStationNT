#ifndef BUTTON_H
#define BUTTON_H

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <include/interrupts/input/input.h>
#include <include/vbe/vbe.h>

int draw_button(int x, int y, int width, int height, char* text, int task_id);

#endif
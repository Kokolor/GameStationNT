#ifndef VBE_H
#define VBE_H

#include <stdint.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <boot/boot_info.h>
#include <include/common/common.h>
#include "font.h"

void init_vbe();
void put_pixel(int x, int y, int r, int g, int b);
void put_rect(int x, int y, int width, int height, int r, int g, int b);
void clear_screen(int r, int g, int b);
void flush();
void put_circle(int x, int y, int radius, int r, int g, int b);
void put_character(char character, int x, int y, int r, int g, int b);
void put_string(char* string, int x, int y, int r, int g, int b);

#endif
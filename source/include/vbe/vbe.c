#include <stdint.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "vbe.h"

void init_vbe() {
}

void put_pixel(int x, int y, int r, int g, int b) {
    // unsigned *buffer = (unsigned *)(mb_info->framebuffer_addr + y * mb_info->framebuffer_pitch);
    unsigned *backbuffer = (unsigned *)(mb_info->framebuffer_addr + (y + mb_info->framebuffer_height) * mb_info->framebuffer_pitch);
    // buffer[x] = (r << 16) | (g << 8) | b;
    backbuffer[x] = (r << 16) | (g << 8) | b;
}

void put_rect(int x, int y, int width, int height, int r, int g, int b) {
    int end_x = x + width;
    int end_y = y + height;

    for (int i = x; i < end_x; i++)
    {
        for (int j = y; j < end_y; j++)
        {
            put_pixel(i, j, r, g, b);
        }
    }
}

void clear_screen(int r, int g, int b) {
    for(unsigned y = 0; y < mb_info->framebuffer_height; ++y)
    {
        for(unsigned x = 0; x < mb_info->framebuffer_width; ++x)
            put_pixel(x, y, r, g, b);
    }
}

void flush() {
    memcpy(mb_info->framebuffer_addr, mb_info->framebuffer_addr + mb_info->framebuffer_height * mb_info->framebuffer_pitch, mb_info->framebuffer_pitch * mb_info->framebuffer_height);
}

void put_circle(int x, int y, int radius, int r, int g, int b)
{
    int x_coordinate = x - radius;
    int y_coordinate = y - radius;

    for(int i = x_coordinate; i <= x + radius; i++)
    {
        for(int j = y_coordinate; j <= y + radius; j++)
        {
            int distance = (i - x)*(i - x) + (j - y)*(j - y);
            if(distance <= radius * radius)
            {
                put_pixel(i, j, r, g, b);
            }
        }
    }
}

void put_character(char character, int x, int y, int r, int g, int b) {
    uint8_t* offset = font + sizeof(font_header_t) + 16 * character;

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 8; j++) {
            if (offset[i] & (1 << j)) {
                put_pixel(x + 8 - j, y + i, r, g, b);
            }
        }
    }
}

void put_string(char* string, int x, int y, int r, int g, int b) {
    size_t length = strlen(string);

    for (size_t i = 0; i < length; i++) {
        put_character(string[i], x + 8 * i, y, r, g, b);
    }
}

void draw_mouse(int x, int y, int r, int g, int b) {
    const uint8_t mouse[8][8] = {
        {0, 2, 2, 2, 2, 2, 2, 0}, 
        {2, 1, 7, 6, 5, 4, 3, 2}, 
        {2, 7, 7, 6, 5, 4, 3, 2}, 
        {2, 6, 6, 5, 4, 3, 2, 0}, 
        {2, 5, 5, 4, 3, 2, 0, 0}, 
        {2, 4, 4, 3, 2, 0, 0, 0}, 
        {2, 3, 3, 2, 0, 0, 0, 0}, 
        {0, 2, 2, 0, 0, 0, 0, 0},
    };

    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
            if (mouse[j][i] == 2) {
                put_pixel(x + i, y + j, 0, 0, 0);
            } else if (mouse[j][i] == 3){
                put_pixel(x + i, y + j, 50, 50, 50);
            } else if (mouse[j][i] == 4){
                put_pixel(x + i, y + j, 75, 75, 75);
            } else if (mouse[j][i] == 5){
                put_pixel(x + i, y + j, 110, 110, 110);
            } else if (mouse[j][i] == 6){
                put_pixel(x + i, y + j, 150, 150, 150);
            } else if (mouse[j][i] == 7){
                put_pixel(x + i, y + j, 200, 200, 20);
            } else if (mouse[j][i] == 1) {
                put_pixel(x + i, y + j, r, g, b);
            }
        }
    }
}
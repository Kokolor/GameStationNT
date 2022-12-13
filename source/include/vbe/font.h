#ifndef FONT_H
#define FONT_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

extern uint8_t font[];

typedef struct {
    uint8_t magic[2];
    uint8_t mode;
    uint8_t height;
} font_header_t;

#endif
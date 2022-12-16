#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

#define FALSE 0
#define TRUE 1

#define PIC1            0x20
#define PIC2            0xA0
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1 + 1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2 + 1)

#define PIC_EOI         0x20

#define ICW1            0x11
#define ICW4_8086       0x01

size_t strlen(const char *string);
unsigned char inportb(unsigned short port);
void outportb(unsigned short port, unsigned char data);
void *memcpy(char *dst, char *src, int n);
void* memset(void * ptr, int value, uint16_t num);
void init_dynamic_mem();
void *malloc(size_t size);
void free(void *p);
static inline void io_wait(void);
void delay(uint16_t ms);
void init_pic(void);

#endif
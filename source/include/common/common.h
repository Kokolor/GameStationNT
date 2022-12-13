#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

#define FALSE 0
#define TRUE 1

size_t strlen(const char *string);
unsigned char inportb(unsigned short port);
void outportb(unsigned short port, unsigned char data);
void *memcpy(char *dst, char *src, int n);
void* memset(void * ptr, int value, uint16_t num);
void init_dynamic_mem();
void *malloc(size_t size);
void free(void *p);

#endif
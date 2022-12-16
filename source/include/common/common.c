#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "common.h"

#define NULL_POINTER ((void*)0)
#define DYNAMIC_MEM_TOTAL_SIZE 4*1024
#define DYNAMIC_MEM_NODE_SIZE sizeof(dynamic_mem_node_t) // 16

typedef struct dynamic_mem_node {
    uint32_t size;
    bool used;
    struct dynamic_mem_node *next;
    struct dynamic_mem_node *prev;
} dynamic_mem_node_t;

static uint8_t dynamic_mem_area[DYNAMIC_MEM_TOTAL_SIZE];
static dynamic_mem_node_t *dynamic_mem_start;

void init_dynamic_mem() {
    dynamic_mem_start = (dynamic_mem_node_t *) dynamic_mem_area;
    dynamic_mem_start->size = DYNAMIC_MEM_TOTAL_SIZE - DYNAMIC_MEM_NODE_SIZE;
    dynamic_mem_start->next = NULL_POINTER;
    dynamic_mem_start->prev = NULL_POINTER;
}

size_t strlen(const char *string) {
    const char *s;

    s = string;
    while (*s)
        s++;
    return (s - string);
}

unsigned char inportb(unsigned short port) {
    unsigned char value;

    __asm__ __volatile__ ("inb %1, %0" : "=a" (value) : "dN" (port));

    return value;
}

void outportb(unsigned short port, unsigned char data) {
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

void *memcpy(char *dst, char *src, int n) {
	char *p = dst;
	while (n--)
		*dst++ = *src++;
	return p;
}

void* memset(void * ptr, int value, uint16_t num) {
    uint8_t* u8Ptr = (uint8_t *)ptr;

    for (uint16_t i = 0; i < num; i++)
        u8Ptr[i] = (uint8_t)value;

    return ptr;
}

void *finde_best_mem_block(dynamic_mem_node_t *dynamic_mem, size_t size) {
    dynamic_mem_node_t *best_mem_block = (dynamic_mem_node_t *) NULL_POINTER;
    uint32_t best_mem_blockSize = DYNAMIC_MEM_TOTAL_SIZE + 1;

    dynamic_mem_node_t *CurrentMemBlock = dynamic_mem;
    while (CurrentMemBlock) {
        if ((!CurrentMemBlock->used) &&
            (CurrentMemBlock->size >= (size + DYNAMIC_MEM_NODE_SIZE)) &&
            (CurrentMemBlock->size <= best_mem_blockSize)) {
            best_mem_block = CurrentMemBlock;
            best_mem_blockSize = CurrentMemBlock->size;
        }
        CurrentMemBlock = CurrentMemBlock->next;
    }
    return best_mem_block;
}


void *malloc(size_t size) {
    dynamic_mem_node_t *best_mem_block =
            (dynamic_mem_node_t *) finde_best_mem_block(dynamic_mem_start, size);

    if (best_mem_block != NULL_POINTER) {
        best_mem_block->size = best_mem_block->size - size - DYNAMIC_MEM_NODE_SIZE;

        dynamic_mem_node_t *mem_node_allocate = (dynamic_mem_node_t *) (((uint8_t *) best_mem_block) +
                                                                        DYNAMIC_MEM_NODE_SIZE +
                                                                        best_mem_block->size);
        mem_node_allocate->size = size;
        mem_node_allocate->used = true;
        mem_node_allocate->next = best_mem_block->next;
        mem_node_allocate->prev = best_mem_block;

        if (best_mem_block->next != NULL_POINTER) {
            best_mem_block->next->prev = mem_node_allocate;
        }
        best_mem_block->next = mem_node_allocate;

        return (void *) ((uint8_t *) mem_node_allocate + DYNAMIC_MEM_NODE_SIZE);
    }
    return NULL_POINTER;
}

void *merge_current_node_into_current(dynamic_mem_node_t *current_mem_node) {
    dynamic_mem_node_t *next_mem_node = current_mem_node->next;
    if (next_mem_node != NULL_POINTER && !next_mem_node->used) {
        current_mem_node->size += current_mem_node->next->size;
        current_mem_node->size += DYNAMIC_MEM_NODE_SIZE;

        current_mem_node->next = current_mem_node->next->next;
        if (current_mem_node->next != NULL_POINTER) {
            current_mem_node->next->prev = current_mem_node;
        }
    }
    return current_mem_node;
}

void *merge_current_node_into_previous(dynamic_mem_node_t *current_mem_node) {
    dynamic_mem_node_t *previous_mem_node = current_mem_node->prev;
    if (previous_mem_node != NULL_POINTER && !previous_mem_node->used) {
        previous_mem_node->size += current_mem_node->size;
        previous_mem_node->size += DYNAMIC_MEM_NODE_SIZE;

        previous_mem_node->next = current_mem_node->next;
        if (current_mem_node->next != NULL_POINTER) {
            current_mem_node->next->prev = previous_mem_node;
        }
    }
}

void free(void *p) {
    if (p == NULL_POINTER) {
        return;
    }

    dynamic_mem_node_t *current_mem_node = (dynamic_mem_node_t *) ((uint8_t *) p - DYNAMIC_MEM_NODE_SIZE);

    if (current_mem_node == NULL_POINTER) {
        return;
    }

    current_mem_node->used = false;

    current_mem_node = merge_current_node_into_current(current_mem_node);
    merge_current_node_into_previous(current_mem_node);
}

static inline void io_wait(void) {
    outportb(0x80, 0);
}

void delay(uint16_t ms) {
    for(long long int i = 0; i < 5000 * (uint16_t)ms / 2; i++)
        io_wait();
}


void init_pic(void) {
	uint8_t A1, A2;

    A1 = inportb(PIC1_DATA);
    A2 = inportb(PIC2_DATA);

    outportb(PIC1_COMMAND, ICW1);
    outportb(PIC2_COMMAND, ICW1);

    outportb(PIC1_DATA, 0x20);
    outportb(PIC2_DATA, 0x28);

    outportb(PIC1_DATA, 4);
    outportb(PIC2_DATA, 2);

    outportb(PIC1_DATA, ICW4_8086);
    outportb(PIC2_DATA, ICW4_8086);

    outportb(PIC1_DATA, A1);
    outportb(PIC2_DATA, A2);
}

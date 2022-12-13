#define __GDT__
#include <stdint.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "gdt.h"


void init_gdt_descriptor(uint32_t base, uint32_t limit, uint8_t acces, uint8_t other, struct gdt_descriptor *descriptor) {
	descriptor->lim0_15 = (limit & 0xffff);
	descriptor->base0_15 = (base & 0xffff);
	descriptor->base16_23 = (base & 0xff0000) >> 16;
	descriptor->acces = acces;
	descriptor->lim16_19 = (limit & 0xf0000) >> 16;
	descriptor->other = (other & 0xf);
	descriptor->base24_31 = (base & 0xff000000) >> 24;
	return;
}

void init_gdt(void) {
	init_gdt_descriptor(0x0, 0x0, 0x0, 0x0, &kernel_gdt[0]);
	init_gdt_descriptor(0x0, 0xFFFFF, 0x9B, 0x0D, &kernel_gdt[1]);	/* code */
	init_gdt_descriptor(0x0, 0xFFFFF, 0x93, 0x0D, &kernel_gdt[2]);	/* data */
	init_gdt_descriptor(0x0, 0x0, 0x97, 0x0D, &kernel_gdt[3]);		/* stack */

	kernel_gdt_pointer.limit = GDTSIZE * 8;
	kernel_gdt_pointer.base = GDTBASE;

	memcpy((char *) kernel_gdt_pointer.base, (char *) kernel_gdt, kernel_gdt_pointer.limit);

	asm("lgdtl (kernel_gdt_pointer)");

	asm("   movw $0x10, %ax	\n \
            movw %ax, %ds	\n \
            movw %ax, %es	\n \
            movw %ax, %fs	\n \
            movw %ax, %gs	\n \
            ljmp $0x08, $next	\n \
            next:		\n");
}

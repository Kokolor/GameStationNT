#include <stdbool.h>
#include <stdint.h>
#include <boot/boot_info.h>
#include <include/gdt/gdt.h>
#include <include/vbe/vbe.h>
#include <include/interrupts/idt.h>
#include <include/interrupts/isr.h>
#include <include/interrupts/input/input.h>

void _start(multiboot_info_t* mboot_info){
    mb_info = mboot_info;
    init_gdt();
    init_idt();
    init_isr();
    init_irq();
    init_pic();

    init_dynamic_mem();

    init_timer();
    init_keyboard();
    init_mouse();

    __asm__ __volatile__ ("sti");

    while(1){
        clear_screen(0, 43, 54);
        put_rect(mouse_x, mouse_y, 5, 5, 255, 255, 255);
        put_string("Hello world!", 2, 2, 255, 255, 255);

        flush();
    }
}

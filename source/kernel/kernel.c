#include <stdbool.h>
#include <stdint.h>
#include <boot/boot_info.h>
#include <include/gdt/gdt.h>
#include <include/vbe/vbe.h>
#include <include/interrupts/idt.h>
#include <include/interrupts/isr.h>
#include <include/desktop/desktop.h>

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

    tasks[tasks_length].priority = 0;
	tasks[tasks_length].function = &clear_screen_task;
	tasks_length++;

    tasks[tasks_length].priority = 0;
	tasks[tasks_length].function = &taskbar_task;
	tasks[tasks_length].task_id = tasks_length;
	iparams[tasks_length * task_params_length + 0] = 0;
	iparams[tasks_length * task_params_length + 1] = 0;
	iparams[tasks_length * task_params_length + 2] = 800;
	iparams[tasks_length * task_params_length + 3] = 40;
	iparams[tasks_length * task_params_length + 4] = 1;
	tasks_length++;

	tasks[tasks_length].priority = 5;
	tasks[tasks_length].function = &draw_mouse_task;
	tasks_length++;

    while(1){
        process_tasks();

        flush();
    }
}

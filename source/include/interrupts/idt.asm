global load_idt
extern kernel_idt_pointer
load_idt:
    lidt [kernel_idt_pointer]
    ret
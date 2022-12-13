extern irq_handler

irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, irq_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret


%macro irq 2
  global irq%1
  irq%1:
    cli
    push byte 0
    push byte %2
    jmp irq_common_stub
%endmacro


irq 0, 32
irq 1, 33
irq 2, 34
irq 3, 35
irq 4, 36
irq 5, 37
irq 6, 38
irq 7, 39
irq 8, 40
irq 9, 41
irq 10, 42
irq 11, 43
irq 12, 44
irq 13, 45
irq 14, 46
irq 15, 47

extern fault_handler
global exception0
global exception1
global exception2
global exception3
global exception4
global exception5
global exception6
global exception7
global exception8
global exception9
global exception10
global exception11
global exception12
global exception13
global exception14
global exception15
global exception16
global exception17
global exception18
global exception19
global exception20
global exception21
global exception22
global exception23
global exception24
global exception25
global exception26
global exception27
global exception28
global exception29
global exception30
global exception31

exception_handler:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, fault_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret


exception0:
    cli
    push byte 0     ; store default err code(0)
    push 0          ; push exception number index in IDT
    jmp exception_handler
    pusha
    popa

exception1:
    cli
    push byte 0     ; store default err code(0)
    push 1          ; push exception number index in IDT
    jmp exception_handler


exception2:
    cli
    push byte 0     ; store default err code(0)
    push 2          ; push exception number index in IDT
    jmp exception_handler


exception3:
    cli
    push byte 0     ; store default err code(0)
    push 3          ; push exception number index in IDT
    jmp exception_handler


exception4:
    cli
    push byte 0     ; store default err code(0)
    push 4          ; push exception number index in IDT
    jmp exception_handler


exception5:
    cli
    push byte 0     ; store default err code(0)
    push 5          ; push exception number index in IDT
    jmp exception_handler


exception6:
    cli
    push byte 0     ; store default err code(0)
    push 6          ; push exception number index in IDT
    jmp exception_handler


exception7:
    cli
    push byte 0     ; store default err code(0)
    push 7          ; push exception number index in IDT
    jmp exception_handler


exception8:
    cli
    push 8          ; push exception number index in IDT
    jmp exception_handler


exception9:
    cli
    push byte 0     ; store default err code(0)
    push 9          ; push exception number index in IDT
    jmp exception_handler


exception10:
    cli
    push 10          ; push exception number index in IDT
    jmp exception_handler


exception11:
    cli
    push 11          ; push exception number index in IDT
    jmp exception_handler


exception12:
    cli
    push 12          ; push exception number index in IDT
    jmp exception_handler


exception13:
    cli
    push 13          ; push exception number index in IDT
    jmp exception_handler


exception14:
    cli
    push 14          ; push exception number index in IDT
    jmp exception_handler


exception15:
    cli
    push byte 0     ; store default err code(0)
    push 15          ; push exception number index in IDT
    jmp exception_handler


exception16:
    cli
    push byte 0     ; store default err code(0)
    push 16          ; push exception number index in IDT
    jmp exception_handler


exception17:
    cli
    push byte 0     ; store default err code(0)
    push 17          ; push exception number index in IDT
    jmp exception_handler


exception18:
    cli
    push byte 0     ; store default err code(0)
    push 18          ; push exception number index in IDT
    jmp exception_handler


exception19:
    cli
    push byte 0     ; store default err code(0)
    push 19          ; push exception number index in IDT
    jmp exception_handler


exception20:
    cli
    push byte 0     ; store default err code(0)
    push 20          ; push exception number index in IDT
    jmp exception_handler


exception21:
    cli
    push byte 0     ; store default err code(0)
    push 21          ; push exception number index in IDT
    jmp exception_handler


exception22:
    cli
    push byte 0     ; store default err code(0)
    push 22          ; push exception number index in IDT
    jmp exception_handler


exception23:
    cli
    push byte 0     ; store default err code(0)
    push 23          ; push exception number index in IDT
    jmp exception_handler


exception24:
    cli
    push byte 0     ; store default err code(0)
    push 24          ; push exception number index in IDT
    jmp exception_handler


exception25:
    cli
    push byte 0     ; store default err code(0)
    push 25          ; push exception number index in IDT
    jmp exception_handler


exception26:
    cli
    push byte 0     ; store default err code(0)
    push 26          ; push exception number index in IDT
    jmp exception_handler


exception27:
    cli
    push byte 0     ; store default err code(0)
    push 27          ; push exception number index in IDT
    jmp exception_handler


exception28:
    cli
    push byte 0     ; store default err code(0)
    push 28          ; push exception number index in IDT
    jmp exception_handler


exception29:
    cli
    push byte 0     ; store default err code(0)
    push 29          ; push exception number index in IDT
    jmp exception_handler


exception30:
    cli
    push byte 0     ; store default err code(0)
    push 30          ; push exception number index in IDT
    jmp exception_handler


exception31:
    cli
    push byte 0     ; store default err code(0)
    push 31          ; push exception number index in IDT
    jmp exception_handler


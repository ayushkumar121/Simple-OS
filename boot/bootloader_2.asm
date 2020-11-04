bits 32                 ;nasm directive - 32 bit
global start
extern kernel_main

SECTION .text

; Begin multiboot header

multiboot_structure:
    align 4
    dd 0x1BADB002                     ; Magic Number (aka. multiboot signature)
    dd 0x07                           ; Flags requests video mode memory etc.
    dd -(0x1BADB002 + 0x07)           ; Checking for corruption
    
    dd multiboot_structure          ; multiboot header addr
    dd multiboot_structure                
    dd 0                   
    dd 0                            ; multiboot info memory high
    dd start                        ; multiboot ifno memory low

    dd 0
    dd 1024                         ; width
    dd 768                          ; height
    dd 28                           ; color depth

; End of multiboot structure

multiboot_structure_info dd 0                    ; multiboot structure info

; Begin Kernel Stack

stack_end:
    times 65535 db 0
stack_start:

; End Kernel Stack

; Begin GDT Allocation ( making one giant segment)
    GDT_Contents:
        db 0, 0, 0, 0, 0, 0, 0, 0           ; Null Entry
        db 255, 255, 0, 0, 0, 0x9A, 0xCF, 0 ; 1st Entry
        db 255, 255, 0, 0, 0, 0x92, 0xCF, 0 ; 2nd Entry
        db 255, 255, 0, 0, 0, 0xFA, 0xCF, 0 ; 3rd Entry
        db 255, 255, 0, 0, 0, 0xF2, 0xCF, 0 ; 4th Entry

    GDT_Pointer db 39, 0, 0, 0, 0, 0

; End GDT Allocation

start:
    cli 			    ;block interrupts

    ; Begin check if multiboot is present (aka. check if kernel is too bad to boot)
    
    mov ecx, 0x2BADB002 
    cmp ecx, eax
    jne no_multiboot
 
    ; End check if multiboot is present

    ; Begin Enabling A20 Gate using fast gate
    
    in al, 0x92   
    or al, 2
    out 0x92, al

    ; End Enabling A20 Gate

    ; Begin Switching to Protected mode
    
    mov eax, cr0
    or eax, 1
    mov word cr0, eax
    
    ; End switching to Protected mode

    ; Begin Tell CPU about GDT
    
    mov dword [GDT_Pointer + 2], GDT_Contents
    mov dword eax, GDT_Pointer
    lgdt [eax]

    mov eax, 0x10
    mov word ds, eax
    mov word es, eax
    mov word fs, eax
    mov word fs, eax
    mov word ss, eax

    ; End Tell CPU about GDT 
    
    ; Begin kernel
    
    mov esp, stack_start
    push ebx
    call kernel_main
    
    ; End kernel

halt:
    cli
    hlt
    jmp halt
  
no_multiboot: ; Handle no multiboot situation
    jmp halt
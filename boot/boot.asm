[bits 16]
[extern prueba]
[global boot]

section .text
boot:
mov bp, 0x9000 ; set the stack
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print ; This will be written after the BIOS messages

    call switch_to_pm
    jmp $ ; this will actually never be executed


%include "print.asm"
%include "print_hex.asm"
%include "32bits-switch.asm"
%include "32bits-gdt.asm"
%include "32bits-print.asm"
%include "disk.asm"

[bits 32]
BEGIN_PM: ; after the switch we will get here
    call prueba
    jmp $

MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_PROT_MODE db "Loaded 32-bit protected mode", 0





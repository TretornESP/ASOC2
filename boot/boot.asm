[bits 16]
[global boot]
[org 0x7c00]

section .text
ini:
	jmp 0:boot

boot:
	mov [MAIN_DISK], dl
	mov bp, 0x9000 ; set the stack
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print ; This will be written after the BIOS messages
	
    call OUR_SECOND_STAGE_OFFSET

    jmp $ ; this will actually never be executed


MSG_REAL_MODE db "Started in 16-bit real mode", 0

%include "print.asm"
%include "print_hex.asm"
%include "second_stage.asm"

times 510-($-$$) db 0
dw 0xaa55

%include "32bits-switch.asm"
%include "32bits-gdt.asm"
%include "32bits-print.asm"

[bits 32]
BEGIN_PM: ; after the switch we will get here
    mov bx, MSG_PROT_MODE
    call print_string_pm
    jmp $

MSG_PROT_MODE db "Loaded 32-bit protected mode", 0
MSG_2ND_SECT db "2nd sector loaded", 0
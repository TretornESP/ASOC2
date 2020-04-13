[section .boot]
[bits 16]
[global boot]
boot:
	jmp 0:first_stage

first_stage:
    mov [MAIN_DISK], dl
    mov bp, 0x9000 ; set the stack
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print ; This will be written after the BIOS messages
    call SECOND_STAGE

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
%include "64bits-detect.asm"
%include "64bits-switch.asm"

[bits 32]
BEGIN_PM: ; after the switch we will get here
    mov bx, MSG_PROT_MODE
    call print_string_pm
    call detect_lm

BEGIN_LM:
    mov dword [0xb8000], 0x2f4b2f4f
    ;mov esp,kernel_stack_top
    ;mov ebp, esp
    extern kmain
    call kmain
    
	
MSG_PROT_MODE db "Loaded 32-bit protected mode", 0
MSG_LONG_MODE db "Loaded 64-bit long mode", 0

section .bss
align 4
kernel_stack_bottom: equ $
	resb 16384 ; 16 KB
kernel_stack_top:

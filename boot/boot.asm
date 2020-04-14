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

		mov bx, switch_to_pm  ; set address to bx
		mov dh, 0x8 ;
		call disk_load  ; read our binaries and store by offset above
		call switch_to_pm  ; give execution to our loaded binaries

    jmp $ ; this will actually never be executed


MSG_REAL_MODE db "Started in 16-bit real mode", 0

%include "asm/disk.asm"
%include "asm/print.asm"
%include "asm/print_hex.asm"

times 510-($-$$) db 0
dw 0xaa55

switch_to_pm:
    cli ; 1. disable interrupts
    lgdt [gdt_descriptor] ; 2. load the GDT descriptor
    mov eax, cr0
    or eax, 0x1 ; 3. set 32-bit mode bit in cr0
    mov cr0, eax
    jmp CODE_SEG:init_pm ; 4. far jump by using a different segment

%include "asm/32bits-gdt.asm"
%include "asm/32bits-idt.asm"

[bits 32]
	init_pm: ; we are now using 32-bit instructions
		mov ax, DATA_SEG ; 5. update the segment registers
		mov ds, ax
		mov ss, ax
		mov es, ax
		mov fs, ax
		mov gs, ax

		mov ebp, 0x90000 ; 6. update the stack right at the top of the free space
		mov esp, ebp

		in al, 0x92 ;Enable a20 gate
		test al, 2
		jnz after
		or al, 2
		and al, 0xFE
		out 0x92, al
	after:
		call BEGIN_PM ; 7. Call a well-known label with useful code

BEGIN_PM: ; after the switch we will get here
    mov bx, MSG_PROT_MODE
    call print_string_pm
    call detect_lm

%include "asm/32bits-print.asm"
%include "asm/64bits-switch.asm"

[bits 64]
BEGIN_LM:
    extern kmain
    call kmain
    jmp $

MSG_PROT_MODE db "Loaded 32-bit protected mode", 0
MSG_LONG_MODE db "Loaded 64-bit long mode", 0

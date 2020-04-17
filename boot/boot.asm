[section .boot]
[bits 16]
[global boot]
boot:
	jmp 0:first_stage

first_stage:
    mov [MAIN_DISK], dl

		xor ax, ax
		mov ds, ax
		mov ss, ax
		mov es, ax
		mov si, ax
		mov di, ax
		mov bx, ax
		mov cx, ax
		mov dx, ax

		mov bp, 0x9000 ; set the stack
		mov sp, bp

		mov bx, second_stage  ; set address to bx
		mov dh, 0x8 ;
		call disk_load  ; read our binaries and store by offset above
		call second_stage  ; give execution to our loaded binaries

    jmp $ ; this will actually never be executed

SECOND_STAGE_ADDR equ 0xA000

%include "asm/disk.asm"

times 510-($-$$) db 0
dw 0xaa55

second_stage:
	mov bx, MSG_SND_STAGE
	call print
	jmp $
	call detect_ram
	call switch_to_pm

switch_to_pm:
    cli ; 1. disable interrupts
    lgdt [gdt_descriptor] ; 2. load the GDT descriptor
    mov eax, cr0
    or eax, 0x1 ; 3. set 32-bit mode bit in cr0
    mov cr0, eax
    jmp CODE_SEG:init_pm ; 4. far jump by using a different segment

%include "asm/32bits-gdt.asm"
%include "asm/32bits-idt.asm"
%include "asm/print.asm"
%include "asm/print_hex.asm"
%include "asm/ram_detect.asm"

MSG_SND_STAGE db "Loaded second stage", 0

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

times 0xFF*512-($-$$) db 0

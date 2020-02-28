[bits 16]
[org 0x7c00]

jmp 0:init

init:
	xor ax, ax
	mov ss, ax
	mov ds, ax
	mov es, ax
	
	mov sp, 0x9000
	mov bp, sp
	
	mov bx, STR
	call print
	
	call install_keyboard
	
halt: 
	jmp $

%include "print.asm"
%include "keyboard.asm"



	
		
VGA: dd 0xb8000

times 510-($-$$) db 0
dw 0xaa55
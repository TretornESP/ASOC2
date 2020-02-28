install_keyboard:
	push word 0
	pop ds
	cli
	mov [4 * KEYBOARD_INTERRUPT], word keyboardHandler
	mov [4 * KEYBOARD_INTERRUPT + 2], cs
	sti
	ret
	
keyboardHandler:
	pusha
	
	in al, 0x60
	test al, 0x80
	jnz .end
	
	mov bl, al
	xor bh, bh
	mov al, [cs:bx + keymap]
	
	call procesar
	
.end:
	mov al, 0x61
	out 0x20, al
	popa
	iret
	
procesar:
	mov ah, 0x0e
	int 0x10
	ret
	
keymap
%include "keymap.inc"

KEYBOARD_INTERRUPT EQU 9

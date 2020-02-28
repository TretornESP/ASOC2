install_mouse:

	call .test_mouse
	
	push word 0
	pop ds
	cli
	mov [4 * MOUSE_INTERRUPT], word mouseHandler
	mov [4 * MOUSE_INTERRUPT + 2], cs
	sti
	call .wait_device
	
	mov al, 0xd4
	out 0x64, al
	
	call .wait_device
	
	mov al, 0xf4
	out 0x60, al
	
	call .wait_device
	
	in al, 0x60
	cmp al, 0xfa
	jz .success
	
	mov bx, ERR
	call print
	jmp halt

.test_mouse:
	int 11h
	test al, 0x3
	jz .no_mouse
	ret

.no_mouse:
	mov bx, NO_MOUSE
	call print
	jmp halt
	
.success:
	mov bx, SUC
	call print
	ret	
	
.wait_device
	in al, 0x64
	test al, 0b10
	jnz .wait_device
	ret
	
mouseHandler:
	pusha
	
	mov bx, MOUSE
	call print
	
.end:
	mov al, 0x20
	out 0xa0, al
	out 0x20, al
	popa
	iret
	
MOUSE: db "I came from mouse", 0
KEYBD: db "I came from keybd", 0
WAI: db "Waiting", 0
ERR: db "Error installing mouse", 0
NO_MOUSE: db "No mouse detected", 0
SUC: db "Mouse installed", 0
MOUSE_INTERRUPT EQU 0x74
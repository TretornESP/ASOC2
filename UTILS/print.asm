print:

.init:
	mov ah, 0x0e
	
.loop:
	mov al, [bx]
	cmp al, 0x0
	je print.end
	add bx, 0x1
	int 0x10
	jmp print.loop
	
.end:
	ret
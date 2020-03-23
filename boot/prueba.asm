[bits 32]
[extern _prueba]

pruebac:
    push bp ; Push stack

    call prueba

    pop	bp		; Pop stack

    mov	ax,0	; Exit code 0
    ret			





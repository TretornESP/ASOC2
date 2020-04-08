SECOND_STAGE:
	mov bx, switch_to_pm  ; set address to bx
	mov dh, 0x8 ;
	call disk_load  ; read our binaries and store by offset above
	call switch_to_pm  ; give execution to our loaded binaries
	ret

%include "disk.asm"

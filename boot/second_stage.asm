OUR_SECOND_STAGE_OFFSET:
OFFSET equ 0x1000 ; where to store boot loader binaries
mov bx, OFFSET  ; set address to bx
call disk_load  ; read our binaries and store by offset above
call OFFSET  ; give execution to our loaded binaries
ret

%include "disk.asm"

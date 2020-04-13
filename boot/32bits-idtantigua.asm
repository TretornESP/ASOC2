
idt_info:
    ; interrupt 0
    db   0xD2,0x7c          ; offset(0:15)-address of interrupt 1 function (handler)
    dw   8                  ; code segment (0x08)
    db   0                  ; hard coded all zeros
    db   10001110b          ; 1000b
                            ; 1-segment present flag
                            ; 00-privilage level
                            ; 0-hard coded value
                            ; 1110b
                            ; 1-size of gate 1-32 bit, 0-16 bit
                            ; 110-hard coded value for type interrupt gate
    db   0,0                ; offset(16:31)
    ; interrupt 1
    db   0xE6,0x7c          ; address of interrupt 0 function (handler)
    dw   8                  ; code segment (0x08)
    db   0                  ; hard coded all zeros
    db   10001110b          ; 1000b
                            ; 1-segment present flag
                            ; 00-privilage level
                            ; 0-hard coded value
                            ; 1110b
                            ; 1-size of gate 1-32 bit, 0-16 bit
                            ; 110-hard coded value for type interrupt gate
    db   0,0                ; offset(16:31)
idt_info_end:

idt_entry:
    dw idt_info_end - idt_info  ; IDT size
    dd idt_info                 ; base of IDT


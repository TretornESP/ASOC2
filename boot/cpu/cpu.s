global gdt_load
extern GDTR
gdt_load:
  push rax
  mov eax, GDTR
  lgdt[eax]
  pop rax
  ret

global tss_load
extern TSS
tss_load:
  push rax
  mov ax, TSS
  ltr ax
  pop rax
  ret

global idt_load
extern IDT
idt_load:
  push rdx
  mov edx, IDT
  lidt [edx]
  pop rdx
  sti
  ret

global cli
cli:
  cli
  ret

global sti
sti:
  sti
  ret

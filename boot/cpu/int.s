extern isr_default_int
extern do_syscalls
extern isr_schedule_int


%macro	SAVE_REGS 0
  push rax
  push rbx
  push rcx
  push rdx

  push rsi
  push rdi

  push r8
  push r9
  push r10
  push r11
  push r12
  push r13
  push r14
  push r15

  mov eax, fs
  push rax
  mov eax, gs
  push rax

  mov eax, ds
  push rax
  mov eax, es
  push rax

%endmacro

%macro	RESTORE_REGS 0
	pop rax
  mov es, eax
  pop rax
  mov ds, eax

  pop rax
  mov gs, eax
  pop rax
  mov fs, eax

  pop r15
  pop r14
  pop r13
  pop r12
  pop r11
  pop r10
  pop r9
  pop r8

  pop rdi
  pop rsi

  pop rdx
  pop rcx
  pop rbx
  pop rax

%endmacro

%macro	INTERRUPT 1
global _asm_int_%1
_asm_int_%1:
	SAVE_REGS
	push %1
	call isr_default_int
	pop rax	;;a enlever sinon
	mov al,0x20
	out 0x20,al
	RESTORE_REGS
	iret
%endmacro

extern isr_GP_exc
extern isr_PF_exc

global _asm_syscalls
_asm_syscalls:
	SAVE_REGS
	push rax                 ; transmission du numero d'appel
	call do_syscalls
	pop rax
	cli
	sti
	RESTORE_REGS
	iret

global _asm_exc_GP
_asm_exc_GP:
	SAVE_REGS
	call isr_GP_exc
	RESTORE_REGS
	add rsp,4
	iret

global _asm_exc_PF
_asm_exc_PF:
	SAVE_REGS
	call isr_PF_exc
	RESTORE_REGS
	add esp,4
	iret

global _asm_schedule
_asm_schedule:
	SAVE_REGS
	call isr_schedule_int
	mov al,0x20
	out 0x20,al
	RESTORE_REGS
	iret

INTERRUPT 1
INTERRUPT 2

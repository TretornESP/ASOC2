;; Implemenation for switching to x64 Long Mode
;; http://wiki.osdev.org/Setting_Up_Long_Mode#Entering_Long_Mode
[bits 32]

detect_lm:
  ;; Copy FLAGS in to EAX via stack
  pushfd
  pop eax

  ;; Copy to ECX as well for comparing later on
  mov ecx, eax

  ;; Flip the ID bit
  xor eax, 1 << 21

  ;; Copy EAX to FLAGS via the stack
  push eax
  popfd

  ;; Copy FLAGS back to EAX
  pushfd
  pop eax

  ;; Restore FLAGS from the old version stored in ECX
  push ecx
  popfd

  ;; Compare EAX and ECX
  ;; If they are equal then that means the bit wasn't flipped
  ;; so that, CPUID isn't supported
  xor eax, ecx
  jz detect_lm_no_cpuid

  ;; Otherwise, we have to check whether long mode can be used or not
  mov eax, 0x80000000
  cpuid
  cmp eax, 0x80000001
  jb detect_lm_no_long_mode

  ;; We can use extended function for detecting long mode now
  mov eax, 0x80000001
  cpuid
  test edx, 1 << 29
  jz detect_lm_no_long_mode

  ;; In case, if all check are successful, we can actually switch to Long Mode
  call switch_to_lm
  ret

detect_lm_no_cpuid:
  ;; In case, if CPUID isn't supported execute kernel in x32 Protected Mode
  mov bx, MSG_NO_CPUID
  call print_string_pm
  jmp $

detect_lm_no_long_mode:
  ;; In case, if Long Mode is not supported execute kernel in x32 Protected Mode
  mov bx, MSG_NO_LONG_MODE
  call print_string_pm
  jmp $

switch_to_lm:
  ;; Before we actually cover up the new paging used in x86-64
  ;; we should disable the old paging first set up in protected mode
  mov eax, cr0
  and eax, 01111111111111111111111111111111b
  mov cr0, eax

  ;; Clear the tables
  mov edi, 0x1000
  mov cr3, edi
  xor eax, eax
  mov ecx, 4096
  rep stosd
  mov edi, cr3

  ;; Set up the new tables
  mov DWORD [edi], 0x2003
  add edi, 0x1000
  mov DWORD [edi], 0x3003
  add edi, 0x1000
  mov DWORD [edi], 0x4003
  add edi, 0x1000
  mov ebx, 0x00000003
  mov ecx, 512

.set_entry:
  mov DWORD [edi], ebx
  add ebx, 0x1000
  add edi, 8
  loop .set_entry

;; Now, we need to enable PAE-paging
switch_to_lm_enable_paging:
  mov eax, cr4
  or eax, 1 << 5
  mov cr4, eax

  ;; Set the LM-bit
  mov ecx, 0xC0000080
  rdmsr
  or eax, 1 << 8
  wrmsr

  ;; Enable paging
  mov eax, cr0
  or eax, 1 << 31
  mov cr0, eax

  ;; Load our GDT with the 64-bit flags
  ;; and make far jump to init_lm
  lgdt [GDT64.Pointer]
  jmp GDT64.Code:init_lm

  MSG_NO_CPUID db "No CPUID", 0
  MSG_NO_LONG_MODE db "No Long Mode", 0

  %include "64bits-gdt.asm"

[bits 64]

init_lm:
  ;; update all segment registers
  cli
  mov ax, GDT64.Data
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  ;; Update base and stack pointers
  mov ebp, 0x90000
  mov esp, ebp

  call BEGIN_LM

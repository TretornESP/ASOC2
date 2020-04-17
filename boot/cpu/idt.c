#include "idt.h"
#include "com.h"
#include "../lib/screen.h"
#include "../mem/lib.h"

void _remap_pic() {
      //icw1
      outportb(0x20, 0x11);
      outportb(0xA0, 0x11);
      //icw2
      outportb(0x21, 0x20);
      outportb(0xA1, 0x70);
      //icw3
      outportb(0x21, 0x04);
      outportb(0xA1, 0x02);
      //icw4
      outportb(0x21, 0x01);
      outportb(0xA1, 0x01);
      //mask interrupts
      outportb(0x21, 0x0);
      outportb(0xA1, 0x0);
}

void default_handler() {

  *(vga_ptr++) = 0x0f;
  *(vga_ptr++) = 'I';
  *(vga_ptr++) = 0x0f;
  *(vga_ptr++) = 'N';
  *(vga_ptr++) = 0x0f;
  *(vga_ptr++) = 'T';

  while (1) {}
}

void load_idt_entry(uint16_t selector, uint64_t offset, uint16_t type, struct idt * descriptor) {
  descriptor -> offset_1 = (offset & 0xffff);
  descriptor -> selector = selector;
  descriptor -> ist = 0x0; //If we enable ist in TSS we can implement This
  descriptor -> type_attr = type;
  descriptor -> offset_2 = (offset & 0xffff0000) >> 16;
  descriptor -> offset_3 = (offset & 0xffffffff00000000) >> 32;
  descriptor -> zero = 0x0;
}


void idt_init() {
  cli();
  for (int i = 0; i < IDTSIZE; i++)
      load_idt_entry(0x08, (uint32_t)_asm_schedule, INTGATE, &IDT[i]);

  load_idt_entry(0x08, (uint32_t) _asm_exc_GP, INTGATE, &IDT[13]);
  load_idt_entry(0x08, (uint32_t) _asm_exc_PF, INTGATE, &IDT[14]);

  load_idt_entry(0x08, (uint32_t) _asm_schedule, INTGATE, &IDT[32]);
  load_idt_entry(0x08, (uint32_t) _asm_int_1, INTGATE, &IDT[33]);

  load_idt_entry(0x08, (uint32_t) _asm_syscalls, TRAPGATE, &IDT[48]);
  load_idt_entry(0x08, (uint32_t) _asm_syscalls, TRAPGATE, &IDT[128]);

  IDTR.base = IDTBASE;
  IDTR.limit = IDTSIZE*8;

  memcpy((char *) IDTR.base, (char *) IDT, IDTR.limit);

  idt_load();
  sti();
}

void do_syscalls() {}
void isr_GP_exc() {}
void isr_PF_exc() {}
void isr_schedule_int() {}
void isr_default_int() {}

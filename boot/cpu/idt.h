#ifndef _IDT_H
#define _IDT_H
#define IDTSIZE 256
#define IDTBASE 0x00000000

#define INTGATE  0x8E00
#define TRAPGATE 0xEF00
#include <stdint.h>


struct idt {
   uint16_t offset_1; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t ist;       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t type_attr; // type and attributes
   uint16_t offset_2; // offset bits 16..31
   uint32_t offset_3; // offset bits 32..63
   uint32_t zero;     // reserved
} __attribute__((packed));

struct idtr {
  uint16_t limit;
  uint64_t base;
} __attribute__((packed)) idt_register_t;

struct idt IDT[IDTSIZE];
struct idtr IDTR;

void default_handler();
void _remap_pic();
void load_idt_entry(uint16_t, uint64_t, uint16_t, struct idt *);
void idt_init();
extern void idt_load();

extern uint64_t _asm_exc_PF;
extern uint64_t _asm_exc_GP;
extern uint64_t _asm_schedule;
extern uint64_t _asm_syscalls;
extern uint64_t _asm_int_1;

extern void sti();
extern void cli();
#endif

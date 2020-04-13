#ifndef _GDT_H
#define _GDT_H
#define GDTBASE    0x00000800
#define GDTSIZE    256
#include <stdint.h>

struct gdt {
  uint16_t lim0_15;
  uint16_t base0_15;
  uint8_t base16_23;
  uint8_t access;
  uint8_t lim16_19 : 4;
  uint8_t flags : 4;
  uint8_t base24_31;
} __attribute__((packed));

struct gdtr{
  uint16_t limit;
  uint64_t base;
} __attribute__((packed));

struct gdt GDT[GDTSIZE];
struct gdtr GDTR;

void gdt_init();
void load_gdt_entry(uint32_t, uint32_t, uint8_t, uint8_t, struct gdt *);
extern void gdt_load();
#endif

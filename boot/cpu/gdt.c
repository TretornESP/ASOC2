#include "gdt.h"
#include "tss.h"
#include "../mem/lib.h"

void gdt_init() {
  load_gdt_entry(0x0, 0x0, 0x0, 0x0, &GDT[0]); //Null entry
  load_gdt_entry(0x0, 0x0, 0x0, 0x0, &GDT[1]); //Code
  load_gdt_entry(0x0, 0x0, 0x0, 0x0, &GDT[2]); //Data
  load_gdt_entry(0x0, 0x0, 0x0, 0x0, &GDT[3]); //Stack

  load_gdt_entry(0x0, 0x0, 0x0, 0x0, &GDT[4]); //UserSpace Code
  load_gdt_entry(0x0, 0x0, 0x0, 0x0, &GDT[5]); //UserSpace Data
  load_gdt_entry(0x0, 0x0, 0x0, 0x0, &GDT[6]); //UserSpace Stack

  load_gdt_entry((uint32_t) & TSS, sizeof(TSS), 0xE9, 0x00, &GDT[7]);

  GDTR.base = GDTBASE;
  GDTR.limit = GDTSIZE*8;

  memcpy((char *) GDTR.base, (char *) GDT, GDTR.limit);

  gdt_load();

}

void load_gdt_entry(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags, struct gdt * entry) {
  entry->lim0_15 = (limit & 0xffff);
  entry->base0_15 = (base & 0xffff);
  entry->base16_23 = (base & 0xff0000) >> 16;
  entry->access = access;
  entry->lim16_19 = (limit & 0xf0000) >> 16;
  entry->flags = (flags & 0xf);
  entry->base24_31 = (base & 0xff000000) >> 24;
}
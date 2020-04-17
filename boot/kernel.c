#include "cpu/com.h"
#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/tss.h"
#include "lib/screen.h"

void setup() {
	vga_print("GDT LOADING \0");
	gdt_init();
	vga_print("GDT LOADED \0");
	vga_print("TSS LOADING \0");
	tss_init();
	vga_print("TSS LOADED \0");
	vga_print("IDT LOADING \0");
	idt_init();
	vga_print("IDT LOADED \0");
}

void kmain() {
	vga_init();

	setup();
	vga_print("HEY DUDE IM READY \0");
	while (1);
}

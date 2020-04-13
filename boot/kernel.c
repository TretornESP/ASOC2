#include "cpu/com.h"
#include "cpu/gdt.h"
#include "cpu/idt.h"
#include "cpu/tss.h"
#include "lib/screen.h"

void setup() {
	gdt_init();
	*(vga_ptr++) = 'g';
	*(vga_ptr++) = 0x0f;
	tss_init();
	*(vga_ptr++) = 't';
	*(vga_ptr++) = 0x0f;
	idt_init();
}

void kmain() {
	vga_init();
	*(vga_ptr++) = 0x0f;
	*(vga_ptr++) = 'v';
	setup();
	*(vga_ptr++) = 0x0f;
	*(vga_ptr++) = 'H';
	*(vga_ptr++) = 0x0f;
	*(vga_ptr++) = 'e';
	*(vga_ptr++) = 0x0f;
	*(vga_ptr++) = 'y';
	while (1);
}

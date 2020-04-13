#include <stdint.h>
//#include <stddef.h>
#include "funciones.h"
#include <sys/io.h>
//#define STRING_MAX_SIZE 4096 //Cuidao con esto, es solo para debug
#define STRING_TERMINATOR '\0'
#define VGA_ADDR 0xB8000

unsigned char * vga_ptr = (unsigned char*)0xb8000;
char color = 0x0f;

void memcpy(unsigned char * dst, unsigned char * orig, size_t size) {
	for (size_t i = 0; i < size; i++) {
		*(dst+i) = *(orig+i);	
	}
}

void memset(unsigned char * dst, const unsigned char val, size_t size) {
	for (size_t i = 0; i < size; i++) {
		*(dst+i) = val;	
	}
}

size_t strlen(unsigned char * string) {
	size_t size = 0;
	while (*(string+size) != STRING_TERMINATOR) {
		if (size++ > STRING_TERMINATOR) return -1;
	}
	return size;
}

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void putc(unsigned char chr, unsigned char color) {
    unsigned char * vga_ptr = (unsigned char*)0xb8000;
    *(vga_ptr) = color;
    *(vga_ptr+1) = chr;
}

void puts(unsigned char * str) {
    unsigned char color = 0x0f;
    for (size_t size = 0; size < strlen(str); size++) {
        putc(*(str+size), color);
    }
}



void kmain() {

    idt_install();
    isrs_install();
    irq_install();

    unsigned char hello[] = "Hello\0";
    char * vga_ptr = (char*)0xb8000;
    char color = 0x0f;

    //puts(hello);


    //puts(hello);
    while (1) {}
}


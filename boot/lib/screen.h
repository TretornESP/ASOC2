#ifndef _SCREEN_H
#define _SCREEN_H
#include <stdint.h>
uint8_t * vga_ptr;
char *convert(unsigned int num, int base);
void puts(char * str);
void putchar(char c);
void printf(char * format, ...);
void vga_init();
void vga_print(const char * str);
#endif

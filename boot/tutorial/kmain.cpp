#include <cstddef>
#define STRING_MAX_SIZE 4096 //Cuidao con esto, es solo para debug
#define STRING_TERMINATOR '\0'
#define VGA_ADDR 0xB8000

char * vga_ptr = (char*)0xb8000;
char color = 0x0f;

void memcpy(char * dst, char * orig, size_t size) {
	for (size_t i = 0; i < size; i++) {
		*(dst+i) = *(orig+i);	
	}
}

void memset( char * dst, const char val, size_t size) {
	for (size_t i = 0; i < size; i++) {
		*(dst+i) = val;	
	}
}

size_t strlen(const char * string) {
	size_t size = 0;
	while (*(string+size) != STRING_TERMINATOR) {
		if (size++ > STRING_TERMINATOR) return -1;
	}
	return size;
}

void putc( char chr,  char color) {
    *(vga_ptr) = color;
    *(vga_ptr+1) = chr;
}

void puts(const char * str) {
     char color = 0x0f;
    for (size_t size = 0; size < strlen(str); size++) {
        putc(*(str+size), color);
    }
}

extern "C" void kmain()
{
	const char* hello = "Hello cpp world!\0";
	puts(hello);
}

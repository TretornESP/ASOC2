#include "screen.h"
#include <stdarg.h>
void vga_init() {
  vga_ptr = (uint8_t*) 0xb8000;
}

void putchar(char c) {
  *(vga_ptr++) = c;
  *(vga_ptr++) = 0x0f;
}

void puts(char * str) {
  vga_print(str);
}

void printf(char * format, ...) {
  char *traverse;
  unsigned int i;
  char *s;

  va_list arg;
	va_start(arg, format);

  for(traverse = format; *traverse != '\0'; traverse++)	{
  	while( *traverse != '%' ) {
  	   putchar(*traverse);
       traverse++;

       switch(*traverse)	{
  		 case 'c' : i = va_arg(arg,int);		//Fetch char argument
  		   putchar(i);
  		   break;
       case 'd' : i = va_arg(arg,int); 		//Fetch Decimal/Integer argument
         if(i<0) {
           i = -i;
           putchar('-');
         }
         puts(convert(i,10));
         break;
       case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
         puts(convert(i,8));
         break;
       case 's': s = va_arg(arg,char *); 		//Fetch string
         puts(s);
         break;
       case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
         puts(convert(i,16));
         break;
       }
  	  traverse++;
    }
  }
  va_end(arg);
}

char *convert(unsigned int num, int base)
{
	static char Representation[]= "0123456789ABCDEF";
	static char buffer[50];
	char *ptr;

	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = Representation[num%base];
		num /= base;
	}while(num != 0);
	return(ptr);
}

void vga_print(const char * str) {
  uint32_t i = 0;
  while (str[i] != '\0') {
    *(vga_ptr++) = str[i++];
    *(vga_ptr++) = 0x0f;
  }
}

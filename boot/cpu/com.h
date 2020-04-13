#ifndef _COM_H
#define _COM_H
#include <stdint.h>

uint8_t inportb (uint16_t);
void outportb (uint16_t, uint8_t);
void eoi();
#endif

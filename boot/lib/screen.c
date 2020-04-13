#include "screen.h"
void vga_init() {
  vga_ptr = (uint8_t*) 0xb8000;
}

#include "lib.h"
void memcpy(char* dst, char* src, size_t tam) {
  for (size_t i = 0; i < tam; i++) {
  *(dst+i) = *(src+i);
  }
}

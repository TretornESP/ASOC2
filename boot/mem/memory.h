#ifndef _MEMORY_H
#define _MEMORY_H
#include <stdint.h>

#define USABLE            0x1
#define RESERVED          0x2
#define ACPI_RECLAIMABLE  0x3
#define ACPI_NVS          0x4
#define BAD_MEM           0x5
#define ACPI_EXT_IGNORE   0x1
#define  ACPI_EXT_NON_VOL  0x2

struct memory_map {
  uint64_t base;
  uint64_t length;
  uint32_t type;
  uint32_t acpi;
} __attribute__((packed));

void print_memory_map();

extern struct memory_map MEMORY_MAP;
extern uint32_t   MEMORY_MAP_REAL_ENTRIES;
#endif

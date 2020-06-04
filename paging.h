#ifndef PAGING
#define PAGING

#include <stdint.h>
#include <stdlib.h>
#include "memoria.h"

typedef struct page_table_directory {

    uint8_t  xD : 1; //Execute disable.
    uint16_t z : 11; //Reserved, must be 0.
    uint64_t address : 40;
    uint8_t  availiable : 3;
    uint8_t  g : 1; //Ignored.
    uint8_t  s : 1; //Page size, 4KiB by default. Changes o 4MiB on 1. 0 in our implementation.
    uint8_t  pat : 1; //Ignored.
    uint8_t  a : 1; //Accessed. Set by CPU, but not reset.
    uint8_t  d : 1; //Cache disabled on 1.
    uint8_t  w : 1; //Write-through. Intel-specific according to MIT.
    uint8_t  u : 1; //US. When 1, can be accesed ny normal users.
    uint8_t  r : 1; //RW. When 0, the page is read only.
    uint8_t  p : 1; //Present in physical memory.

} __attribute__ ((aligned (4096), packed)) page_table_directory;

typedef struct page_table_entry {

    uint8_t  xD : 1; //Execute disable.
    uint16_t z : 11; //Reserved, must be 0.
    uint64_t address : 40;
    uint8_t  availiable : 3;
    uint8_t  g : 1; //Global: Determines whether the translation is global (see Section 4.10); ignored otherwise.
    uint8_t  pat : 1; //PAT. 0 in our implementation.
    uint8_t  d : 1; //Dirty: indicates if the page has been written into.
    uint8_t  a : 1; //Accessed: set by CPU, but not reset.
    uint8_t  c : 1; //Page-level cache disable; indirectly determines the memory type used to access the 4-KByte page referenced by this entry (see Section 4.9)
    uint8_t  w : 1; //Page-level write-through; indirectly determines the memory type used to access the 4-KByte page referenced by this entry (see Section 4.9)
    uint8_t  u : 1; //User/Supervisor: when 1 can be accesed by normal users.
    uint8_t  r : 1; //Read/Write: when 0 read only.
    uint8_t  p : 1; //Present: present in physical memory.

} __attribute__ ((packed)) page_table_entry;

typedef union _page_table_directory_union {
    struct page_table_directory data;
    uint64_t wrapper;
} page_table_directory_uni;

typedef union _page_table_entry_union {
    struct page_table_entry data;
    uint64_t wrapper;
} page_table_entry_uni;

page_table_directory * page_directory;

void init_page_table_directory(page_table_directory_uni * directory);
void mmu(void ** address, void * physical);

#endif
#include "paging.h"
#include <stdio.h>

// Mock function
void init_page_table_directory(page_table_directory_uni * directory) {
    directory = calloc(1, sizeof(page_table_directory_uni));
    directory -> wrapper = 0x7;
}

//MMU address translation Virtual->Physical. UNx16 FIx9 SEx9 THx9 FOx9 ADx12 
void mmu(void ** address, void * physical) {
    page_table_directory * T1 = physical + PAGE_TABLE_START;

    uint64_t input = (uint64_t) *address;
    uint16_t offset = (input >> 39) % 512;
    uint64_t temp = ((page_table_directory *)T1)->address;
    uint64_t add = (temp << 12) + offset * 8;
    offset = (input >> 30) % 512;
    temp = ((page_table_entry *)add)->address;
    add = (temp << 12) + offset * 8;
    offset = (input >> 21) % 512;
    temp = ((page_table_entry *)add)->address;
    add = (temp << 12) + offset * 8;
    offset = (input >> 12) % 512;
    temp = ((page_table_entry *)add)->address;
    add = (temp << 12) + offset * 8;
    offset = (input) % 4096;
    temp = ((page_table_entry *)add)->address;
    add = (temp << 12) + offset;
    *address = (void *) add;
}
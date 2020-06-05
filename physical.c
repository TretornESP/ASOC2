#include "physical.h"
#include <stdio.h>

char *dummy_string = "Epstein didnt kill himself";

void populate_phys_mem(char *physical) {
    memcpy(physical + EMULATED_TARGET_ADDR, dummy_string, strlen(dummy_string));
}

void init_dummy_table(void *physical) {
    //4096^4+512 lmao
    page_table_directory *T1 = physical + PAGE_TABLE_START;
    page_table_entry *T2 = T1 + sizeof(void *) * 512;
    page_table_entry *T3 = T2 + sizeof(void *) * 512;
    page_table_entry *T4 = T3 + sizeof(void *) * 512;
    T1+=0x062;
    T2+=0x0CD;
    T3+=0x180;
    T4+=0x00A;

    T1->address = (uint64_t) T2 >> 12;
    T2->address = (uint64_t) T3 >> 12;
    T3->address = (uint64_t) T4 >> 12;
    T4->address = 0xA;
}

/*
    DIR0->ADDR = 2^18
    DIR1->ADDR = 2^42
    DIR4095 64*4095
    PL1-0     64*4096
    PL1-1     64*4097
    PLx-y     4096^x+y
*/
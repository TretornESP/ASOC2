#ifndef PHYS
#define PHYS

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "paging.h"
#include "memoria.h"

#define EMULATED_MEMORY_SIZE 0x100000
#define EMULATED_TARGET_ADDR 0x00A455
#define EMULATED_VIRT_ADDR_1 0x31337000A455
#define EMULATED_VIRT_ADDR_2 0x000000001455
#define CR3_DUMMY 0xABCD23
uint8_t ram[EMULATED_MEMORY_SIZE];

void init_dummy_table();
void populate_phys_mem(char* physical);

//dir: A
//tp1: B
//tp2: C
//tp3: D
//off: E ->> offset

/*
    PL1 = CR3 + A*S
    PL2 = PL1 + B*S
    PL3 = PL2 + C*S
    PL4 = PL3 + D*S
    ADD = PL4 + E*S

    PL4: 40 MSB + E: 12 LSB
    PL4: 0xA    + E: 0x455
*/

//0x31337000ABCD
//0011 0001 0011 0011 0111 0000 0000 0000 1010 0100 0101 0101
//AAAA AAAA ABBB BBBB BBCC CCCC CCCD DDDD DDDD EEEE EEEE EEEE
//A: 0 0110 0010 -> 0x062
//B: 0 1100 1101 -> 0x0CD
//C: 1 1000 0000 -> 0x180
//D: 0 0000 1010 -> 0x00A
//E: 0100 0101 0101 -> 0x455

//0x000000001234
//0000 0000 0000 0000 0000 0000 0000 0000 0001 0100 0101 0101
//AAAA AAAA ABBB BBBB BBCC CCCC CCCD DDDD DDDD EEEE EEEE EEEE
//A: 0 0000 0000 -> 0x000
//B: 0 0000 0000 -> 0x000
//C: 0 0000 0000 -> 0x000
//D: 0 0000 0001 -> 0x001
//E: 0100 0101 0101 -> 0x455

/*

       PML4    PDP     PD     PT
CR3 + (4096 * 4096 * 4096 * 4096)
0x40*0x62=0x1880
*/

#endif
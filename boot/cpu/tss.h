#ifndef _TSS_H
#define _TSS_H
#include <stdint.h>
struct tss {
	uint32_t __unused_0;
	uint32_t rsp0_l;
  uint32_t rsp0_u;
  uint32_t rsp1_l;
  uint32_t rsp1_u;
  uint32_t rsp2_l;
  uint32_t rsp2_u;
  uint32_t __unused_1;
  uint32_t __unused_2;
  uint32_t ist1_l;
  uint32_t ist1_u;
  uint32_t ist2_l;
  uint32_t ist2_u;
  uint32_t ist3_l;
  uint32_t ist3_u;
  uint32_t ist4_l;
  uint32_t ist4_u;
  uint32_t ist5_l;
  uint32_t ist5_u;
  uint32_t ist6_l;
  uint32_t ist6_u;
  uint32_t ist7_l;
  uint32_t ist7_u;
  uint32_t __unused_3;
  uint32_t __unused_4;
	uint16_t __unused_5, io_map;
} __attribute__ ((packed));

struct tss TSS;

extern void tss_load();
void tss_init();
#endif

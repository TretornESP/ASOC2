#include <stdio.h>
#include "memoria.h"
#include "physical.h"
#include <sys/time.h>

int main() {

    void *mem = malloc(MAX_MEMORY * sizeof(char) + 4095);
    char *physical = ((uintptr_t) mem + 4095) & ~(uintptr_t) 0x0FFF;
    struct timeval end, start;
    gettimeofday(&start, NULL);

    populate_phys_mem(physical);
    init_dummy_table(physical);
    void *virt_addr = (void *) EMULATED_VIRT_ADDR_2;
    printf("BEFORE: %p\n", virt_addr);
    mmu(&virt_addr, physical);
    printf("AFTER: %p\n", virt_addr);
    uint64_t addr = (uint64_t) virt_addr;
    printf("Did Jeffrey kill himself? \n %s\n", physical + (uint64_t) virt_addr);

    gettimeofday(&end, NULL);
    printf("\nTask took %luus\n", ((end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec));
    free(mem);
    return 0;

}
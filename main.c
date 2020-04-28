#include <stdio.h>
#include "memoria.h"
#include <sys/time.h>
#include <stdlib.h>

int main() {

    struct timeval end, start;
    gettimeofday(&start, NULL);

    initTable();

    gettimeofday(&end, NULL);
    printTable();
    printf("\nTask took %luus\n", ((end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec));
    return 0;
}
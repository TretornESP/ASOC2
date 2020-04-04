#include <stdio.h>
#include "memoria.h"
#include <sys/time.h>
#include <stdlib.h>

int main() {
    struct timeval end, start;
    initIndex();
    srand(time(NULL));
    void* beeb[300];

    gettimeofday(&start, NULL);

    for (int i = 0; i < 300; i++) beeb[i] = palloc(rand() % 10000);
    for (int i = 0; i < 100; i++) {
        int b = rand() % 300;
        if(beeb[b] != NULL) _free(beeb[b]);
        beeb[b] = NULL;
    }
    for (int i = 0; i < 300; i++) beeb[i] = palloc(rand() % 10000);

    gettimeofday(&end, NULL);
    printIndex();
    printf("\nTask took %luus\n", ((end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec));
    return 0;
}
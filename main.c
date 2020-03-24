#include <stdio.h>
#include "memoria.h"
#include <sys/time.h>

int main() {

    struct timeval end,start;
    gettimeofday(&start, NULL);

    initIndex();
    _malloc(5000);
    char * p = _malloc(1);
    //printIndex();
    //printf("%p\n", p);
    _free(p);
    //printIndex();

    gettimeofday(&end, NULL);
    printf("\nTask took %luus", ((end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec));
    return 0;
}
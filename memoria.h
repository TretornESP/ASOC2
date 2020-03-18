#ifndef MEMORIA_H
#define MEMORIA_H

#import <stdbool.h>
#import <stdio.h>

#define PAGE_SIZE 4096
#define PAGE_NUM 3

typedef struct {
    char* pos;
    char* blockStart;
    bool isFree;
    int pID;
    long lastUsed;
} pageIndexEntry;

typedef char page[PAGE_SIZE];

page mem[PAGE_NUM];
pageIndexEntry _index[PAGE_NUM];

char* _malloc(int);
bool _free(char*);
void initIndex();
void printIndex();

#endif //MEMORIA_H
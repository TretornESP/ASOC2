#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define PAGE_SIZE 4096
#define MAX_MEMORY 1048576
#define PAGE_NUM MAX_MEMORY/PAGE_SIZE - 1

#define MAX_SHM_ENTRIES 32

typedef struct {
    void *pos;
    void *blockStart;
    unsigned long lastUsed;
} pageIndexEntry;
static pageIndexEntry _index[PAGE_NUM];

typedef struct {
    void *pos;
    char key[8];
    int flag;
    unsigned char connections;
} shmIndexEntry;
static shmIndexEntry _shmindex[MAX_SHM_ENTRIES];

void *palloc(int);

bool _free(void *);

void initIndex();

void printIndex();

void *_shmget(char[8], size_t, int, int *);

bool shmcut(void *);

void printshmIndex();

#endif //MEMORIA_H
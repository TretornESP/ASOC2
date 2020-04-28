#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdbool.h>

#ifndef NULL
#define NULL ((void*) 0x0)
#endif
#define m_size unsigned long long

#define PAGE_SIZE 4096
#define MAX_MEMORY 1048576
#define MAX_SHM_ENTRIES 32
#define PAGE_NUM MAX_MEMORY/PAGE_SIZE - 1

#define CURR_PHYS_MAP 0x01
#define PAGE_TABLE_START 0x10
static char physical[MAX_MEMORY];
#define PHYS_BASE (void*)&physical

typedef struct {
    void *pos;
    void *blockStart;
    unsigned long lastUsed;
} __attribute__((packed)) pageIndexEntry;

void* first_level_page_table;
void** phys_mapped;

pageIndexEntry m_index[PAGE_NUM]; //Deprecated

typedef struct {
    void *pos;
    char key[8];
    int flag;
    unsigned char connections;
} __attribute__((packed)) shmIndexEntry;

static shmIndexEntry shm_index[MAX_SHM_ENTRIES];

void *palloc(m_size);

bool _free(void *);

void initTable();

void printTable();

void *shmget(char[8], m_size, int, int *);

bool shmcut(void *);

void printshmIndex();

#endif //MEMORIA_H
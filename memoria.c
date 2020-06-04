#include "memoria.h"

#include <stdio.h>

int strcmp(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] == str2[i]) {
        if (str1[i] == '\0') return 0;
        i++;
    }
    if (str1[i] > str2[i]) return 1;
    else return -1;
}

char *strcpy(char *dest, const char *src) {
    dest[0] = src[0];
    for (int i = 1; src[i - 1] != '\0'; i++) dest[i] = src[i];
    return dest;
}

//Size in bytes
void *palloc(m_size size) {
    m_size pagesNeeded = size % PAGE_SIZE ? size / PAGE_SIZE + 1 : size / PAGE_SIZE;
    m_size currEmpty = 0;
    for (m_size i = 0; i < PAGE_NUM; i++) {
        if (!m_index[i].blockStart) {
            currEmpty++;
            if (currEmpty >= pagesNeeded) {
                for (m_size j = 0; j < pagesNeeded; j++) {
                    m_index[i - j].blockStart = m_index[i - pagesNeeded + 1].pos;
                }
                return m_index[i - pagesNeeded + 1].pos;
            }
        } else currEmpty = 0;
    }
    return NULL;
}

bool _free(void *p) {
    bool reachedPos = false;
    for (m_size i = 0; i < PAGE_NUM; i++) {
        if (m_index[i].blockStart == p) {
            reachedPos = true;
            m_index[i].blockStart = NULL;
        } else if (reachedPos) return true;
    }
    return reachedPos;
}

void initTable() {
    void * physical;
    first_level_page_table = physical + PAGE_TABLE_START;
    phys_mapped = physical + CURR_PHYS_MAP;

    void *second_level_page_table = first_level_page_table + sizeof(void *) * 512;
    void *third_level_page_table = second_level_page_table + sizeof(void *) * 512;
    pageIndexEntry *fourth_level_page_table = third_level_page_table + sizeof(void *) * 512;

    *(void **) first_level_page_table = second_level_page_table;
    *(void **) second_level_page_table = third_level_page_table;
    *(pageIndexEntry **) third_level_page_table = fourth_level_page_table;

    *phys_mapped = (void *) PAGE_SIZE;
}

void printTable() {
    void * physical;
    printf("\nRoot table (%p)\t|\tPhysical memory base: %p\n", first_level_page_table, physical);
    for (int i = 0; ((void **) first_level_page_table)[i] != NULL; i++) {
        printf("|\tTable %d (%p)\n", i, &((void **) first_level_page_table)[i]);
        void **second_level_page_table = ((void **) first_level_page_table)[i];
        for (int j = 0; second_level_page_table[j] != NULL; j++) {
            printf("|\t|\tTable %d-%d (%p)\n", i, j, &second_level_page_table[j]);
            void **third_level_page_table = second_level_page_table[j];
            for (int k = 0; third_level_page_table[k] != NULL; k++) {
                printf("|\t|\t|\tTable %d-%d-%d (%p)\n", i, j, k, &third_level_page_table[k]);
                pageIndexEntry *fourth_level_page_table = third_level_page_table[k];
                for (int l = 0; fourth_level_page_table[l].pos != NULL; l++) {
                    printf("|\t|\t|\t|\tPage %d-%d-%d-%d (%p) | Pos: %p BlockStart: %p LastUsed: %ld\n", i, j, k, l,
                           &fourth_level_page_table[l], fourth_level_page_table[l].pos,
                           fourth_level_page_table[l].blockStart,
                           fourth_level_page_table[l].lastUsed);
                }
            }
        }
    }
    printf("\n");
}

void *shmget(char k[8], m_size s, int flag, int *connections) {
    int i = 0;
    for (; i < MAX_SHM_ENTRIES; i++) {
        if (shm_index[i].pos == NULL) break;
        if (strcmp(k, shm_index[i].key) == 0) {
            //TODO: Comprobación permisos
            if (shm_index[i].connections == 255) {
                if (connections) *connections = 255;
                return NULL;
            }
            shm_index[i].connections++;
            if (connections) *connections = shm_index[i].connections;
            return shm_index[i].pos;
        }
    }
    if (shm_index[MAX_SHM_ENTRIES - 1].pos != NULL) {
        if (connections) *connections = -1;
        return NULL;
    }
    shm_index[i].pos = palloc(s);
    shm_index[i].connections = 1;
    if (connections) *connections = 1;
    shm_index[i].flag = flag;
    k[7] = '\0';
    strcpy(shm_index[i].key, k);
    return shm_index[i].pos;
}

bool shmcut(void *p) {
    for (int i = 0; i < MAX_SHM_ENTRIES; i++) {
        if (shm_index[i].pos == NULL) break;
        if (shm_index[i].pos == p) {
            shm_index[i].connections--;
            if (!shm_index[i].connections) {
                _free(p);
                for (; i < MAX_SHM_ENTRIES - 1; i++) { shm_index[i] = shm_index[i + 1]; }
                shm_index[MAX_SHM_ENTRIES - 1].pos = NULL;
                shm_index[MAX_SHM_ENTRIES - 1].key[0] = '\0';
            }
            return true;
        }
    }
    return false;
}

void printshmIndex() {
    for (int i = 0; i < MAX_SHM_ENTRIES; i++) {
        printf("Entrada %d\n\tPos: %p\n\tKey: %s\n\tFlag: %d\n\tConnections: %d\n\n", i, shm_index[i].pos,
               shm_index[i].key,
               shm_index[i].flag, shm_index[i].connections);
    }
}
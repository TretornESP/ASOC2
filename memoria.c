#include "memoria.h"

//Size in bytes
void *palloc(int size) {
    int pagesNeeded = size % PAGE_SIZE ? size / PAGE_SIZE + 1 : size / PAGE_SIZE;
    int currEmpty = 0;
    for (int i = 0; i < PAGE_NUM; i++) {
        if (!_index[i].blockStart) {
            currEmpty++;
            if (currEmpty >= pagesNeeded) {
                for (int j = 0; j < pagesNeeded; j++) {
                    _index[i - j].blockStart = _index[i - pagesNeeded + 1].pos;
                }
                return _index[i - pagesNeeded + 1].pos;
            }
        } else currEmpty = 0;
    }
    return NULL;
}

bool _free(void *p) {
    bool reachedPos = false;
    for (int i = 0; i < PAGE_NUM; i++) {
        if (_index[i].blockStart == p) {
            reachedPos = true;
            _index[i].blockStart = NULL;
        } else if (reachedPos) return true;
    }
    return reachedPos;
}

void initIndex() {
    for (unsigned long i = 0; i < PAGE_NUM; i++) {
        _index[i].pos = (void *) ((i + 1) * PAGE_SIZE);
        _index[i].blockStart = NULL;
        _index[i].lastUsed = 0;
    }
}

void printIndex() {
    for (int i = 0; i < PAGE_NUM; i++) {
        printf("Entrada %d\n\tPos: %p\n\tBlockStart: %p\n\tLastUsed: %ld\n\n", i, _index[i].pos, _index[i].blockStart,
               _index[i].lastUsed);
    }
}

void *_shmget(char k[8], size_t s, int flag, int *connections) {
    int i = 0;
    for (; i < MAX_SHM_ENTRIES; i++) {
        if (_shmindex[i].pos == NULL) break;
        if (strcmp(k, _shmindex[i].key) == 0) {
            //TODO: Comprobación permisos
            if (_shmindex[i].connections == 255) {
                *connections = 255;
                return NULL;
            }
            _shmindex[i].connections++;
            *connections = _shmindex[i].connections;
            return _shmindex[i].pos;
        }
    }
    if (_shmindex[MAX_SHM_ENTRIES - 1].pos != NULL) {
        *connections = -1;
        return NULL;
    }
    _shmindex[i].pos = palloc(s);
    _shmindex[i].connections = 1;
    *connections = 1;
    _shmindex[i].flag = flag;
    strcpy(_shmindex[i].key, k);
    return _shmindex[i].pos;
}

bool shmcut(void *p) {
    for (int i = 0; i < MAX_SHM_ENTRIES; i++) {
        if (_shmindex[i].pos == NULL) break;
        if (_shmindex[i].pos == p) {
            _shmindex[i].connections--;
            if (!_shmindex[i].connections) {
                _free(p);
                for (; i < MAX_SHM_ENTRIES - 1; i++) { _shmindex[i] = _shmindex[i + 1]; }
                _shmindex[MAX_SHM_ENTRIES - 1].pos = NULL;
                _shmindex[MAX_SHM_ENTRIES - 1].key[0] = '\0';
            }
            return true;
        }
    }
    return false;
}

void printshmIndex() {
    for (int i = 0; i < MAX_SHM_ENTRIES; i++) {
        printf("Entrada %d\n\tPos: %p\n\tKey: %s\n\tFlag: %d\n\tConnections: %d\n\n", i, _shmindex[i].pos, _shmindex[i].key,
               _shmindex[i].flag, _shmindex[i].connections);
    }
}
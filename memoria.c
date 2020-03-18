#include "memoria.h"

//Size in bytes
char* _malloc(int size) {
    int pagesNeeded = size%PAGE_SIZE ? size/PAGE_SIZE + 1 : size/PAGE_SIZE;
    int currEmpty = 0;
    for (int i = 0; i < PAGE_NUM; i++) {
        if(_index[i].isFree) {
            currEmpty++;
            if(currEmpty >= pagesNeeded) {
                for (int j = 0; j < pagesNeeded; j++) {
                    _index[i-j].isFree = false;
                    _index[i-j].blockStart = _index[i - pagesNeeded + 1].pos;
                }
                return _index[i - pagesNeeded + 1].pos;
            }
        } else currEmpty = 0;
    }
    return NULL;
}

bool _free(char * p) {
    bool reachedPos = false;
    for (int i = 0; i < PAGE_NUM; i++) {
        if(_index[i].blockStart == p) {
            reachedPos = true;
            _index[i].blockStart = NULL;
            _index[i].isFree = true;
        } else if(reachedPos) return true;
    }
    return reachedPos;
}

void initIndex() {
    for (int i = 0; i < PAGE_NUM; i++) {
        _index[i].pos = &mem[i];
        _index[i].blockStart = NULL;
        _index[i].isFree = true;
        _index[i].lastUsed = 0;
        _index[i].pID = 0;
    }
}

void printIndex() {
    for (int i = 0; i < PAGE_NUM; i++) {
        printf("Entrada %d\n\tPos: %p\n\tBlockStart: %p\n\tIsFree: %d\n\tpID: %d\n\tLastUsed: %ld\n\n", i, _index[i].pos, _index[i].blockStart, _index[i].isFree, _index[i].pID, _index[i].lastUsed);
    }
}

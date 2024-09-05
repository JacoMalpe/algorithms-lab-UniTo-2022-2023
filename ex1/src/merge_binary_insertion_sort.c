
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "merge_binary_insertion_sort.h"

size_t binarySearch(void *item, void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*)) {
    if (nitems == 0) 
    return 0;
    if (nitems == 1) {
        return(compar(base, item) < 0)? 1:0;
    }
    int p = nitems/2;
    if (compar(p*size + ((char*)base), item) < 0)
        return p+1 + binarySearch(item, size*(p+1) + ((char*)base), nitems-p-1, size, compar);
    else
        return binarySearch(item, base, p, size, compar);
}

void insertionSort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*)) {
    void *selected = malloc(size);
    for (int i=1; i<nitems; i++) {
        int loc = binarySearch(i*size + ((char*)base), base, i, size, compar);
        memcpy(selected, ((char*)base) + i*size, size);
        for (int j=i; j>loc; --j)
            memcpy(j*size + ((char*)base), ((char*)base) + (j-1)*size, size);
        memcpy(loc*size + ((char*)base), selected, size);
    }
    free(selected);
}

void merge(void *base, size_t m, size_t nitems, size_t size, int (*compar)(const void *, const void*)) {
    void* copy = malloc(nitems*size);
    memcpy(copy, base, nitems*size);
    char* L = (char*)copy;
    char* L2 = L + m*size;
    char* R = L2;
    char* R2 = L + nitems*size;
    
    char* p = (char*)base;
    for (int i=0; i<nitems; ++i) {
        if (L == L2) {
            memcpy(p, R, size);
            R = R + size;
        } else if (R == R2) {
            memcpy(p, L, size);
            L = L + size;
        } else if (compar(L, R) < 0) {
            memcpy(p, L, size);
            L = L + size;
        } else {
            memcpy(p, R, size);
            R = R + size;
        }
        p = p+ size;
    }
    free(copy);
}

void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, int (*compar)(const void *, const void*)) {
    if(nitems<=1)return;
    else if (nitems <= k) {
        insertionSort(base, nitems, size, compar);
        return;
    }
    size_t m = nitems/2;

    merge_binary_insertion_sort(base, m, size, k, compar);
    merge_binary_insertion_sort(((char*)base)+m*size, nitems-m, size, k, compar);
    merge(base, m, nitems, size, compar);
}

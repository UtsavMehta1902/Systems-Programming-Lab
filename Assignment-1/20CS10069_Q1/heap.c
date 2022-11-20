#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

HEAP createHeap()
{
    HEAP H = malloc(sizeof(heap));
    H->size_filled=0;
    return H;
}

int findMin(HEAP H)
{
    if(H->size_filled==0)
        return -1;
    
    return H->arr[1];
}

HEAP extractMin (HEAP H)
{
    H[1] = H[H->size_filled];

    H->size_filled-=1;

    int index = 1;
    int l, r;
    int minimum;

    while (1)
    {
        l = 2 * index;
        r = 2 * index + 1;
        minimum = r;

        if (l >= H->size_filled)
            break;

        if (r >= H->size_filled || H->arr[l] < H->arr[r])
            minimum = l;

        if (H->arr[index] < H->arr[minimum])
            break;

        H->arr[index]^=H->arr[minimum];
        H->arr[minimum]^=H->arr[index];
        H->arr[index]^=H->arr[minimum];

        index = minimum;
    }

    return H;
}

HEAP insertHeap(HEAP H, int k)
{
    H->arr[(++H->size_filled)]=k;
    int index = H->size_filled;
    int parent;

    while(1)
    {
        parent = index/2;
        if(parent < 1)
            break;
        
        if(H->arr[parent] < H->arr[index])
            break;
        
        H->arr[index]^=H->arr[parent];
        H->arr[parent]^=H->arr[index];
        H->arr[index]^=H->arr[parent];
        
        index = parent;
    }

    return H;
}

int isFullHeap(HEAP H)
{
    if(H->size_filled==HEAP_SIZE_MAX)
        return 1;
    return 0;
}

int isEmptyHeap(HEAP H)
{
    if(H->size_filled==0)
        return 1;
    return 0;
}
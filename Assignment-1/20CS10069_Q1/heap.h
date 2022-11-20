#define HEAP_SIZE_MAX 100

typedef struct _heap
{
    int arr[HEAP_SIZE_MAX+1];
    int size_filled;
}heap;

typedef heap* HEAP;

HEAP createHeap();
int findMin(HEAP H);
HEAP extractMin (HEAP H);
HEAP insertHeap(HEAP H, int k);
int isFullHeap(HEAP H);
int isEmptyHeap(HEAP H);

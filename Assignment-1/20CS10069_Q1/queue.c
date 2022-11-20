#include <stdio.h>
#include <stdlib.h>
#include "llist.h"
#include "queue.h"

QUEUE createQueue()
{
    return createList();
}

int isEmptyQueue(QUEUE Q)
{
    if(!Q)
        return 1;
    else
        return 0;
}

QUEUE enqueue(QUEUE Q, int k)
{
    return insertAtEnd(Q, k);
}

QUEUE dequeue(QUEUE Q, int *k)
{
    return deleteFromFront(Q, k);
}

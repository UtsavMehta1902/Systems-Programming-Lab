#include <stdio.h>
#include <stdlib.h>
#include "llist.h"
#include "stack.h"

STACK createStack()
{
    return createList();
}

int isEmptyStack(STACK S)
{
    if(!S)
        return 1;
    else
        return 0;
}

STACK push(STACK S, int k)
{
    return insertAtFront(S, k);
}

STACK pop(STACK S, int *k)
{
    return deleteFromFront(S, k);
}

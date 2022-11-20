#include <stdio.h>
#include <stdlib.h>
#include "union_find.h"

UNION_FIND createUF(int n)
{
    UNION_FIND F = malloc(sizeof(NODE_PTR)*n);
    for(int i=0; i<n; ++i)
        F[i] = NULL;
    
    return F;
}

UNION_FIND makeSetUF(UNION_FIND F, int x, int *i)
{
    NODE_PTR temp = malloc(sizeof(Node));
    temp->val = x;
    temp->rank=1;
    temp->parent=NULL;

    int ptr=0;
    while(F[ptr])
    {
        ptr++;
    }

    F[ptr]=temp;
    *i = ptr;
    return F;
}

NODE_PTR findUF(UNION_FIND F, int i)
{
    NODE_PTR temp = F[i];

    while(temp->parent)
    {
        temp=temp->parent;
    }

    return temp;
}

void unionUF(UNION_FIND F, int i, int j)
{
    NODE_PTR ptr1 = findUF(F, i);
    NODE_PTR ptr2 = findUF(F, j);

    if(ptr1!=ptr2)
    {
        if(ptr1->rank<ptr2->rank)
        {
            F[i]->parent = F[j];
            ptr2->rank+=ptr1->rank;
        }
        else
        {
            F[j]->parent = F[i];
            ptr1->rank+=ptr2->rank;
        }
    }

    return;
}

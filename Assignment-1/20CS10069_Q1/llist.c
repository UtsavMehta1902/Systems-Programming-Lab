#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

LLIST createList()
{
    LLIST H = NULL;
    return H;
}

int searchList(LLIST H, int k)
{
    LLIST temp = H;
    int found = 0;
    
    while(temp)
    {
        if(temp->val==k)
        {
            found = 1;
            break;
        }

        temp = temp->next;
    }

    return found;
}

LLIST insertAtFront(LLIST H, int k)
{
    LLIST temp = malloc(sizeof(node));
    temp->val = k;
    temp->next = H;
    return temp;
}

LLIST insertAtEnd(LLIST H, int k)
{
    LLIST temp = malloc(sizeof(node)), ptr=H;
    temp->val = k;
    temp->next = NULL;

    if(!H)
        return temp;

    while(ptr->next)
    {
        ptr = ptr->next;
    }
    
    ptr->next = temp;
    return H;
}

LLIST deleteFromFront(LLIST H, int *k)
{
    if(!H)
        return H;

    *k = H->val;

    LLIST temp = H->next;
    free(H);
    return temp;
}

LLIST deleteFromEnd(LLIST H, int *k)
{
    if(!H)
        return H;
    
    if(!H->next)
    {
        *k = H->val;
        free(H);
        return NULL;
    }

    LLIST temp = H->next, prev=H;
    while(temp->next)
    {
        prev = temp;
        temp = temp->next;
    }
    
    prev->next = NULL;
    *k = temp->val;
    free(temp);
    return H;
}

LLIST deleteList(LLIST H, int k)
{
    if(!H)
        return H;

    LLIST temp = H, prev;

    while(temp)
    {
        if(temp->val == k)
            break;
        
        prev=temp;
        temp=temp->next;
    }

    if(!temp)
        return H;
    
    if(temp==H)
    {
        free(temp);
        return NULL;
    }

    prev->next = temp->next;
    free(temp);
    return H;
}
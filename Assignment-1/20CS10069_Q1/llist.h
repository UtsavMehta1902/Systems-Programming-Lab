typedef struct _node
{
    int val;
    struct _node* next;
}node;

typedef node *LLIST;

LLIST createList();
int searchList(LLIST H, int k);
LLIST insertAtFront(LLIST H, int k);
LLIST insertAtEnd(LLIST H, int k);
LLIST deleteFromFront(LLIST H, int *k);
LLIST deleteFromEnd(LLIST H, int *k);
LLIST deleteList(LLIST H, int k);

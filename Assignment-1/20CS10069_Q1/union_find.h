typedef struct _Node
{
    int val;
    int rank;
    struct _Node* parent;
}Node;

typedef Node* NODE_PTR;
typedef NODE_PTR* UNION_FIND;

UNION_FIND createUF(int n);
UNION_FIND makeSetUF(UNION_FIND F, int x, int *i);
NODE_PTR findUF(UNION_FIND F, int i);
void unionUF(UNION_FIND F, int i, int j);

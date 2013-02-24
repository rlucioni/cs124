typedef struct node {
    int key;
    int value;
} node;

typedef struct heap {
    node *nodes; // node array
    int num_nodes;
    int size;
} heap;

heap *make_heap();
void free_heap(heap *h);
void insert(heap *h, int key, int value);
int deletemin(heap *h);
int size(heap *h);

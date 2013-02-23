#include <stdbool.h>

typedef struct element {
    struct element *parent;
    int rank;
    void *data;
} forest_node;

element *makeset(void *data);
element *unionize(forest *f, element *x, element *y);
element *find(element *f, element *x);



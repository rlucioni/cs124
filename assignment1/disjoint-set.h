#include <stdbool.h>

typedef struct element {
    struct element *parent;
    int rank;
    void *data;
} element;

element *makeset(void *data);
element *unionize(element *x, element *y);
element *find(element *f, element *x);



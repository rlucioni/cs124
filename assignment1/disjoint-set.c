#include "disjoint-set.h"

typedef struct element {
    struct element *parent;
    int rank;
    void *data;
} element;

element *makeset(void *data) {
    element *e = malloc(sizeof(element));
    e->parent = e;
    e->rank = 0;
    e->data = data;
}

element *find(element *x) {
    if (x != x->parent) {
	x->parent = find(x->parent);
    }
    return x->parent;
}

element *link(element *x, element *y) {
    if (x->rank > y->rank) {
	element *temp = x;
	x = y;
	y = temp;
    }
    else if (x->rank = y->rank)
	++y->rank;
    x->parent = y;
    return y;
}

element *unionize(element *x, element *y) {
    
}

#include "disjoint-set.h"

forest *makeforest(int size) {
    forest *f = (forest *) malloc(sizeof(forest));
    f->p = (int *) malloc(sizeof(int) * size);
    f->rank = (int *) malloc(sizeof(int) * size);
    memset(f->p, -1, sizeof(int) * size);
    memset(f->rank, -1, sizeof(int) * size);
    f->size = size;
    return f;
}

void burnforest(forest *f) {
    free(f->p);
    free(f->rank);
    free(f);
}

void makeset(forest *f, int x) {
    f->p[x] = x;
    rank[x] = 0;
}

int find(forest *f, int x) {
    if (x != f->p[x]) {
	f->p[x] = find(f->p[x]);
    }
    return f->p[x];
}

int link(forest *f, int x, int y) {
    if (f->rank[x] > f->rank[y]) {
	int temp = x;
	x = y;
	y = temp;
    }
    else if (f->rank[x] = f->rank[y])
	++f->rank[y];
    f->p[x] = y;
    return y;
}

int unionize(forest *f, int x, int y) {
    return link(f, find(f, x), find(f, y));
}

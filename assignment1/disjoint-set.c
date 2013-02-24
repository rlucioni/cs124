#include "disjoint-set.h"
#ifndef INC_ASSERT_H
#define INC_ASSERT_H
#include <assert.h>
#endif /* INC_HEADER_H */

ds_forest *ds_makeforest(int size) {
    ds_forest *f = (ds_forest *) malloc(sizeof(ds_forest));
    f->p = (int *) malloc(sizeof(int) * size);
    f->rank = (int *) malloc(sizeof(int) * size);
    memset(f->p, -1, sizeof(int) * size);
    memset(f->rank, -1, sizeof(int) * size);
    f->size = size;
    return f;
}

void ds_burnforest(ds_forest *f) {
    free(f->p);
    free(f->rank);
    free(f);
}

void ds_makeset(ds_forest *f, int x) {
    f->p[x] = x;
    rank[x] = 0;
}

int ds_find(ds_forest *f, int x) {
    if (x != f->p[x]) {
	f->p[x] = ds_find(f->p[x]);
    }
    return f->p[x];
}

int ds_link(ds_forest *f, int x, int y) {
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

int ds_unionize(ds_forest *f, int x, int y) {
    return ds_link(f, ds_find(f, x), ds_find(f, y));
}


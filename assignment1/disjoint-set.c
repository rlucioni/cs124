#include "disjoint-set.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// PROTOTYPEs
int ds_find(ds_forest *, int);

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
    f->rank[x] = 0;
}

int ds_find(ds_forest *f, int x) {
    if (x != f->p[x])
	    f->p[x] = ds_find(f, f->p[x]);
    return f->p[x];
}

int ds_link(ds_forest *f, int x, int y) {
    if (f->rank[x] > f->rank[y]) {
	    int temp = x;
	    x = y;
	    y = temp;
    }
    else if (f->rank[x] == f->rank[y])
	    ++f->rank[y];
    f->p[x] = y;
    return y;
}

int ds_union(ds_forest *f, int x, int y) {
    return ds_link(f, ds_find(f, x), ds_find(f, y));
}

int ds_run_tests() {
    int nodes = 12;
    ds_forest *f = ds_makeforest(nodes);

    // makeset
    for (int i = 0; i < nodes; ++i) {
	ds_makeset(f, i);
	assert(f->rank[i] == 0);
	assert(f->p[i] == i);

	// find (rank 0)
	assert(i == ds_find(f, i));
    }
    // link (roots)
    for (int i = 0; i < nodes; i += 2) {
	ds_link(f, i, i + 1);
	assert(f->p[i] == i + 1);
	assert(f->p[i + 1] == i + 1);
	assert(f->rank[i] == 0);
	assert(f->rank[i + 1] == 1);

	// find (rank 1 and 0) - no side effects
	assert(ds_find(f, i) == i + 1);
	assert(ds_find(f, i + 1) == i + 1);
    }
    // union (root & root)
    ds_union(f, 1, 3);
    assert(f->p[0] == 1);
    assert(f->p[1] == 3);
    assert(f->p[2] == 3);
    assert(f->p[3] == 3);
    assert(f->rank[3] == 2);

    // union (child & child)
    ds_union(f, 4, 6);
    assert(f->p[4] == 5);
    assert(f->p[5] == 7);
    assert(f->p[6] == 7);
    assert(f->p[7] == 7);
    assert(f->rank[7] == 2);

    // union (root & child)
    ds_union(f, 9, 10);
    assert(f->p[8] == 9);
    assert(f->p[9] == 11);
    assert(f->p[10] == 11);
    assert(f->p[11] == 11);
    assert(f->rank[11] == 2);

    return 0;
}

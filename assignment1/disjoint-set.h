// disjoint-set.h
//    disjoin-set.h/disjoint-set.c declare/implement a forest
//    data structure for working with disjoint sets

// ds_forest:
//    p and rank are parallel arrays for keeping track
//    of disjoint sets; size is the size of both arrays;
//    vertices are represented (id'ed) by ints (0, numpoints)
typedef struct {
    int *p; // parent array
    int *rank; // rank array
    int size;
} ds_forest;

// ds_make_forest(size):
//    allocates memory for disjoint sets
//    size provided up front to avoid need for resizing
ds_forest *ds_make_forest(int size);

// ds_burn_forest(f)
//    deallocates memory used by f
void ds_burn_forest(ds_forest *f);

// ds_make_set(f, x):
//    makes a set in f for x
//    (this could be done in ds_make_forest, however
//    we do it here to maintain the structure of the algorithm
//    as the excess work is negligible)
void ds_make_set(ds_forest *f, int x);

// ds_find(f, x):
//    returns the root of the set of x in f
int ds_find(ds_forest *f, int x);

// ds_union(f, x, y):
//    union the sets of x and y
int ds_union(ds_forest *f, int x, int y);

// ds_run_tets():
//    run tests to verify correctness of disjoint set implementation
int ds_run_tests();

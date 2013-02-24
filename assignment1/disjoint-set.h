typedef struct {
    int *p; // parent array
    int *rank; // rank array
    int size;
} ds_forest;

ds_forest *ds_makeforest(int size);
void ds_burnforest(ds_forest *f);
void ds_makeset(ds_forest *f, int x);
int ds_find(ds_forest *f, int x);
int ds_link(ds_forest *f, int x, int y);
int ds_unionize(ds_forest *f, int x, int y);

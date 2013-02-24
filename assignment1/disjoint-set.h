typedef struct {
    int *p; // parent array
    int *rank; // rank array
    int size;
} forest;

forest *makeforest(int size);
void burnforest(forest *f);
void makeset(forest *f, int x);
int find(forest *f, int x);
int link(forest *f, int x, int y);
int unionize(forest *f, int x, int y);

#include "matrix_multiply.h"
// accesses the element in "matrix" of dimension "dim" at "row" and "column"
#define MELT(matrix, dim, row, col) (matrix)[(row) * (dim) + (col)]

void square_matrix_multiply(int *c, const int *a, const int *b, int dim) {
    for (int i = 0; i < dim; i++)
        for (int k = 0; k < dim; k++)
            for (int j = 0; j < dim; j++)
                MELT(c, dim, i, j) += MELT(a, dim, i, k) * MELT(b, dim, k, j);
}

//#include "matrix_multiply_main.c"
int main(int argc, char **argv) {
    // process command line arguments
    if (argc != 4) {
        fprintf(stderr, "usage: %s flag dimension inputfile\n", argv[0]);
        exit(1);
    }
    int flag = atoi(argv[1]);
    int dim = atoi(argv[2]);
    char* inputfile = argv[3];
    
    assert(dim > 0);

    if (flag == 1) {
        printf("run tests");
    }

    FILE *fp;
    fp = fopen(inputfile, "r");
    assert(fp != NULL);

    int elt;
    int i;
    int j;

    int *ma = (int *) malloc(sizeof(int) * dim * dim);
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++) {
            // As per Piazza question #217, we assume the files being passed 
            // have the correct number of values (i.e., we don't check for EOF)
            (void) fscanf(fp, "%d", &elt); 
            MELT(ma, dim, i, j) = elt;
        }

    int *mb = (int *) malloc(sizeof(int) * dim * dim);
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++) {
            (void) fscanf(fp, "%d", &elt); 
            MELT(mb, dim, i, j) = elt;
        }

    fclose(fp);

    int *mc = (int *) malloc(sizeof(int) * dim * dim);
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            MELT(mc, dim, i, j) = 0;
        
    square_matrix_multiply(mc, ma, mb, dim);

    // print diagonal elements
    for (i = 0; i < dim; i++)
        printf("c[%d,%d] == %d\n", i, i, MELT(mc,dim,i,i));

    free(ma);
    free(mb);
    free(mc);
}

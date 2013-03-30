#include "matrix_multiply.h"
// accesses the element in "matrix" of dimension "dim" at "row" and "column"
#define MELT(matrix, dim, row, col) (matrix)[(row) * (dim) + (col)]
#define CROSSOVER 10
// int crossover;

void square_matrix_multiply(int *c, const int *a, const int *b, int dim) {
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            MELT(c, dim, i, j) = 0;
    for (int i = 0; i < dim; i++)
        for (int k = 0; k < dim; k++) {
	    int a_ik = MELT(a, dim, i, k);
            for (int j = 0; j < dim; j++)
                MELT(c, dim, i, j) += a_ik * MELT(b, dim, k, j);
	}
}

// madd(c, a, b, dim)
//   Addition of square matrices (a + b = c)
void madd(int *c, const int *a, const int *b, int dim) {
    for (int i = 0; i < dim; i++)
	for (int j = 0; j < dim; j++)
	    MELT(c, dim, i, j) = MELT(a, dim, i, j) + MELT(b, dim, i, j);
}

// msub(c, a, b, dim)
//   Subtraction of square matrices (a - b = c)
void msub(int *c, const int *a, const int *b, int dim) {
    for (int i = 0; i < dim; i++)
	for (int j = 0; j < dim; j++)
	    MELT(c, dim, i, j) = MELT(a, dim, i, j) - MELT(b, dim, i, j);
}

// sadd(e, a, b, c, d, dim)
//   Composition of several matrix operations for use by Strassen to avoid
//   redundant loops (used for AE + BG in the Strassen Algorithm)
// TODO: Inline to optimize away function call (since only used once)
void sadd(int *e, const int *a, const int *b, const int *c, const int *d, 
	  int dim) {
    for (int i = 0; i < dim; i++)
	for (int j = 0; j < dim; j++)
	    MELT(e, dim, i, j) = MELT(a, dim, i, j) + MELT(b, dim, i, j)
		- MELT(c, dim, i, j) + MELT(d, dim, i, j);
}

// ssub(e, a, b, c, d, dim)
//   Composition of several matrix operations for use by Strassen to avoid
//   redundant loops (used for CF + DH in the Strassen Algorithm)
// TODO: Inline to optimize away function call (since only used once)
void ssub(int *e, const int *a, const int *b, const int *c, const int *d, 
	  int dim) {
    for (int i = 0; i < dim; i++)
	for (int j = 0; j < dim; j++)
	    MELT(e, dim, i, j) = MELT(a, dim, i, j) + MELT(b, dim, i, j)
		- MELT(c, dim, i, j) - MELT(d, dim, i, j);
}

// strassen(c, a, b, dim)
//   Multiplication of square matrices using the Strassen algorithm (a x b = c)
//   Comments based off of the following matrix multiplication:
//    -    -    -   -       -                - 
//   | A  B |  | E F |  =  | AE + BG  AF + BH | 
//   | C  D |  | G H |     | CE + DG  CF + DH |
//    -    -    -   -       -                -
void strassen(int *c, const int *a, const int *b, int dim) {
    if (dim <= CROSSOVER)
	square_matrix_multiply(c, a, b, dim);
    else {
	// cutting into submatrices
	int dim_half = dim >> 2;

	// sub-matrix size
	int subsize = dim_half * dim_half;

	// work matrix (for P1 through P7 - extra for work)
	int *p = (int *) malloc(sizeof(int) * subsize * 8);

	// First calculate P7, P6, & P5 due to double operations (double space)
	// P7
	msub(&p[0], &a[0], &a[2 * subsize], dim_half); // A - C
	madd(&p[subsize], &b[0], &b[subsize], dim_half); // E + F
	strassen(&p[6 * subsize], &p[0], &p[subsize], dim_half); // (A - C)(E + F)

	// P6
	msub(&p[0], &a[subsize], &a[3 * subsize], dim_half); // B - D
	madd(&p[subsize], &b[2 * subsize], &b[3 * subsize], dim_half); // G + H
	strassen(&p[5 * subsize], &p[0], &p[subsize], dim_half); // (B - D)(G + H)

	// P5
	madd(&p[0], &a[0], &a[3 * subsize], dim_half); // A + D
	madd(&p[subsize], &b[0], &b[3 * subsize], dim_half); // E + H
	strassen(&p[4 * subsize], &p[0], &p[subsize], dim_half); // (A + D)(E + H)
	     
	// P4
	msub(&p[0], &b[3 * subsize], &b[0], dim_half); // G - E
	strassen(&p[3 * subsize], &a[3 * subsize], &p[0], dim_half); // D(G - E)

	// P3
	madd(&p[0], &a[2 * subsize], &a[3 * subsize], dim_half); // C + D
	strassen(&p[2 * subsize], &p[0], &b[0], dim_half); // (C + D)E

	// P2
	madd(&p[0], &a[0], &a[subsize], dim_half); // A + B
	strassen(&p[subsize], &p[0], &b[3 * subsize], dim_half); // (A + B)H
	
	// P1
	msub(&p[7 * subsize], &b[subsize], &b[3 * subsize], dim_half); // F - H
	strassen(&p[0], &a[0], &p[7 * subsize], dim_half); // A(F - H)

	// Calculate new matrix
	sadd(&c[0], &p[4 * subsize], &p[3 * subsize], &p[subsize], 
	     &p[5 * subsize], dim_half); // AE + BG  (P5 + P4 - P2 + P6)
	madd(&c[subsize], &p[0], &p[subsize], dim_half); // AF + BH  (P1 + P2)
	madd(&c[2 * subsize], &p[2 * subsize], &p[3 * subsize], dim_half); // CE + DG  (P3 + P4)
	ssub(&c[3 * subsize], &p[4 * subsize], &p[0], &p[2 * subsize], 
	     &p[6 * subsize], dim_half); // CF + DH  (P5 + P1 - P3 + P7)

	// deallocate work matrix
	free(p);
    }
}

int main(int argc, char **argv) {
    // process command line arguments
    if (argc != 4) {
        // fprintf(stderr, "usage: %s flag dimension inputfile crossover\n", argv[0]);
        fprintf(stderr, "usage: %s flag dimension inputfile\n", argv[0]);
        exit(1);
    }
    int flag = atoi(argv[1]);
    int dim = atoi(argv[2]);
    char* inputfile = argv[3];
    // int crossover = atoi(argv[4]);
    
    assert(dim > 0);

    if (flag == 1) {
       printf("TEST");
       exit(0);
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
        
    //square_matrix_multiply(mc, ma, mb, dim);
    // strassen's is currently segfaulting - need to do more in place memory
    // maybe do some work in the input matrices...
    strassen(mc, ma, mb, dim);

    // print diagonal elements
    /*for (i = 0; i < dim; i++)
        //printf("c[%d,%d] == %d\n", i, i, MELT(mc,dim,i,i));
        printf("%d\n", MELT(mc,dim,i,i));*/

    free(ma);
    free(mb);
    free(mc);
}

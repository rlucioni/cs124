#include "matrix_multiply.h"
// accesses the element in "matrix" of dimension "dim" at "row" and "column"
#define MELT(matrix, dim, row, col) (matrix)[(row) * (dim) + (col)]
//#define CROSSOVER 10
int32_t crossover;

void square_matrix_multiply(int32_t *c, const int32_t *a, const int32_t *b, int32_t dim) {
    for (int32_t i = 0; i < dim; i++)
        for (int32_t j = 0; j < dim; j++)
            MELT(c, dim, i, j) = 0;
    for (int32_t i = 0; i < dim; i++)
        for (int32_t k = 0; k < dim; k++) {
	    int32_t a_ik = MELT(a, dim, i, k);
            for (int32_t j = 0; j < dim; j++)
                MELT(c, dim, i, j) += a_ik * MELT(b, dim, k, j);
	}
}

// madd(c, a, b, dim)
//   Addition of square matrices (a + b = c)
void madd(int32_t *c, const int32_t *a, const int32_t *b, int32_t dim) {
    for (int32_t i = 0; i < dim; i++)
	for (int32_t j = 0; j < dim; j++)
	    MELT(c, dim, i, j) = MELT(a, dim, i, j) + MELT(b, dim, i, j);
}

// msub(c, a, b, dim)
//   Subtraction of square matrices (a - b = c)
void msub(int32_t *c, const int32_t *a, const int32_t *b, int32_t dim) {
    for (int32_t i = 0; i < dim; i++)
	for (int32_t j = 0; j < dim; j++)
	    MELT(c, dim, i, j) = MELT(a, dim, i, j) - MELT(b, dim, i, j);
}

// sadd(e, a, b, c, d, dim)
//   Composition of several matrix operations for use by Strassen to avoid
//   redundant loops (used for AE + BG in the Strassen Algorithm)
// TODO: Inline to optimize away function call (since only used once)
void sadd(int32_t *e, const int32_t *a, const int32_t *b, const int32_t *c, const int32_t *d, 
	  int32_t dim) {
    for (int32_t i = 0; i < dim; i++)
	for (int32_t j = 0; j < dim; j++)
	    MELT(e, dim, i, j) = MELT(a, dim, i, j) + MELT(b, dim, i, j)
		- MELT(c, dim, i, j) + MELT(d, dim, i, j);
}

// ssub(e, a, b, c, d, dim)
//   Composition of several matrix operations for use by Strassen to avoid
//   redundant loops (used for CF + DH in the Strassen Algorithm)
// TODO: Inline to optimize away function call (since only used once)
void ssub(int32_t *e, const int32_t *a, const int32_t *b, const int32_t *c, const int32_t *d, 
	  int32_t dim) {
    for (int32_t i = 0; i < dim; i++)
	for (int32_t j = 0; j < dim; j++)
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
void strassen(int32_t *c, const int32_t *a, const int32_t *b, int32_t dim) {
    //if (dim <= CROSSOVER)
    if (dim <= crossover)
	square_matrix_multiply(c, a, b, dim);
    else {
	// cutting into submatrices
	int32_t dim_half = dim >> 2;

	// sub-matrix size
	int32_t subsize = dim_half * dim_half;

	// work matrix (for P1 through P7 - extra for work)
	int32_t *p = (int32_t *) malloc(sizeof(int32_t) * subsize * 8);

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
    /*if (argc != 4) {
        fprintf(stderr, "usage: %s flag dimension inputfile\n", argv[0]);
        exit(1);
    }*/
    if (argc != 5) {
        fprintf(stderr, "usage: %s flag dimension inputfile crossover\n", argv[0]);
        exit(1);
    }
    int32_t flag = atoi(argv[1]);
    int32_t dim = atoi(argv[2]);
    char* inputfile = argv[3];
    crossover = atoi(argv[4]);
    
    assert(dim > 0);

    if (flag == 1) {
       printf("TEST");
       exit(0);
    }

    FILE *fp;
    fp = fopen(inputfile, "r");
    assert(fp != NULL);

    int32_t elt;
    int32_t i;
    int32_t j;

    // if not a power of 2, pad appropriately
    //    padding done to reach crossover + 2^n
    int32_t dim_pad = dim;
    if (dim & (dim - 1) != 0) {
	// Bit Twiddling Hack for finding next power of 2
	//   http://graphics.stanford.edu/~seander/bithacks.html
	//   -expects 32 bit architecture
	dim_pad--;
	dim_pad |= dim_pad >> 1;
	dim_pad |= dim_pad >> 2;
	dim_pad |= dim_pad >> 4;
	dim_pad |= dim_pad >> 8;
	dim_pad |= dim_pad >> 16;
	dim_pad++;
    }
    int32_t *ma = (int32_t *) malloc(sizeof(int32_t) * dim_pad * dim_pad);
    for (i = 0; i < dim_pad; i++)
        for (j = 0; j < dim_pad; j++) {
            // As per Piazza question #217, we assume the files being passed 
            // have the correct number of values (i.e., we don't check for EOF)
            if (i < dim && j < dim) {
		(void) fscanf(fp, "%d", &elt); 
		MELT(ma, dim_pad, i, j) = elt;
	    }
	    else
		MELT(ma, dim_pad, i, j) = 0;
        }

    int32_t *mb = (int32_t *) malloc(sizeof(int32_t) * dim_pad * dim_pad);
    for (i = 0; i < dim_pad; i++)
        for (j = 0; j < dim_pad; j++) {
            if (i < dim && j < dim) {
		(void) fscanf(fp, "%d", &elt); 
		MELT(mb, dim_pad, i, j) = elt;
	    }
	    else
		MELT(mb, dim_pad, i, j) = 0;
        }

    fclose(fp);

    int32_t *mc = (int32_t *) malloc(sizeof(int32_t) * dim_pad * dim_pad);
        
    //square_matrix_multiply(mc, ma, mb, dim_pad);
    // strassen's is currently segfaulting - need to do more in place memory
    // maybe do some work in the input matrices...
    strassen(mc, ma, mb, dim_pad);

    // print diagonal elements - does not read padding
    /*for (i = 0; i < dim; i++)
        //printf("c[%d,%d] == %d\n", i, i, MELT(mc,dim,i,i));
        printf("%d\n", MELT(mc,dim,i,i));*/

    free(ma);
    free(mb);
    free(mc);
}

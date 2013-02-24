#include "graph.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef INC_ASSERT_H
#define INC_ASSERT_H
#include <assert.h>
#endif

#define RAND_FLOAT() (rand() / RAND_MAX)
#define SQUARE(x) ((x) * (x))
#define SWAP(x,y) { a ^= b; b ^= a; a ^= b; }

static void graph_empty(int);
static void graph_generate_0(int);
static void graph_generate_euclidean(int, int);

// only utilize bottom left of adjacency matrix 

graph *graph_empty(int numpoints) {
    graph *g = (graph *) malloc(sizeof(graph));
    g->adj_matrix = (float **) malloc(sizeof(float *) * numpoints);
    for (int i = 0; i < numpoints; ++i) {
	g->adj_matrix[i] = (float *) malloc(sizeof(float) * numpoints);
	memset(g->adj_matrix[i], -1, sizeof(float) * numpoints);
    }
    g->num_nodes = numpoints;

    return g;
}

void graph_free(graph *g) {
    for (i = 0; i < g->numpoints; ++g)
	free(g->adj_matrix[i]);
    free(g->adj_matrix);
    free(g);
}

int graph_size(graph *g) {
    return g->num_nodes;
}

graph *graph_generate_0(int numpoints) {
    graph *g = graph_empty(numpoints);
    for (int i = 0; i < numpoints; ++i) {
	for (int j = 0; j <=i; ++j) {
	    g->adj_matrix[i][j] = RAND_FLOAT();
	}
    }
    
    return g;
}

graph *graph_generate_euclidean(int dimensions, int numpoints) {
    graph *g = graph_empty(numpoints);
    float ps[numpoints][dimensions]; // array of points, each of dimensions dimensions
    for (int i = 0; i < numpoints; ++i) {
	for (int d = 0; d < dimensions; ++d) {
	    ps[i][d] = RAND_FLOAT();
	}
    }
    for (int i = 0; i < numpoints; ++i) {
	for (int j = 0; j <= i; ++j) {
	    float distance = 0;
	    for (int d = 0; d < dimensions; ++d) {
		distance += SQUARE(ps[i][d] - ps[j][d]);
	    }
	    g->adj_matrix[i][j] = sqrt(distance);
	}
    }

    return g;
}

graph *graph_generate(int dimensions, int numpoints) {
    // seed random number generator
    srand(time(NULL));
    
    // call appropriate graph generation function
    switch (dimensions) {
    case 0: return graph_generate_0(numpoints);
    case 2: 
    case 3: 
    case 4: return graph_generate_euclidean(dimensions, numpoints);
    default: return NULL;
    }
}

float graph_get_edge(graph *g, int n1, int n2) {
    if (n2 > n1) SWAP(n1, n2);
    return g->adj_matrix[n1][n2];
}

int graph_run_tests() {
    int numpoints = 20;
    for (int d = 0; d <= 4; ++d) {
	if (d == 1) continue;
	g = graph_generate(d, numpoints);
	// check size
	assert(numpoints == graph_size(g));

	// check edge lengths
	float max_edge = (d == 0) ? 1 : sqrt(d);
	for (int i = 0; i < numpoints; ++i) {
	    for (int j = 0; j < numpoints; ++j) {
		float edge_length = graph_get_edge(g, i, j);
		assert(0 <= edge_length && edge_length <= max_edge);
	    }
	}
    }

    return 1;
}

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
#define MIN(x,y) (((x) <= (y)) ? (x) : (y))

static void graph_generate_0(int);
static void graph_generate_euclidean(int, int);
static void graph_edge_merge(edge *, int, int, int);

graph *graph_generate_0(int numpoints) {
    graph *g = (graph *) malloc(sizeof(graph));
    g->num_nodes = numpoints;
    g->num_edges = (numpoints - 1) * numpoints / 2;
    g->list = malloc(sizeof(edge) * g->num_edges);
    
    graph *g = graph_empty(numpoints);
    for (int i = 0; i < numpoints; ++i) {
	for (int j = 0; j <=i; ++j) {
	    if (i != j) {
		edge e = { .u = i, .v = j, .weight = RAND_FLOAT() };
		g->list[i] = e;
	    }
	}
    }
    
    return g;
}

graph *graph_generate_euclidean(int dimensions, int numpoints) {
    graph *g = (graph *) malloc(sizeof(graph));
    g->num_nodes = numpoints;
    g->num_edges = (numpoints - 1) * numpoints / 2;
    g->list = malloc(sizeof(edge) * g->num_edges);

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
	    edge e = { .u = i, .v = j, .weight = sqrt(distance) };
	    g->list[i] = e;
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

void graph_free(graph *g) {
    free(g->list);
    free(g);
}


void graph_edge_merge(edge *list, int min, int mid, int max) {
    int l_size = min - min + 1;
    int r_size = max - mid;

    edge left[l_size];
    edge right[r_size];
    memcpy(&left, list + min, sizeof(edge) * l_size);
    memcpy(&right, list + mid + 1, sizeof(edge) * r_size);

    int i, l, r;
    for (i = min, l = 0, r = 0; l < l_size && r < r_size; ++i)
	list[i] = (left[l].weight <= right[r].weight) ? left[l++] : right[r++];
    if (l < l_size) {
	for (; i < max; ++i)
	    list[i] = left[l++];
    }
    else {
	for (; i < max; ++i)
	    list[i] = right[r++];
    }
}

void graph_edge_sort(graph *g) {
    for (int m = 1; m < g->num_edges; m *= 2) {
	for (int i = 0; i < g->num_edges - m; i += 2 * m) {
	    merge(g->list, i, i + m - 1, MIN(i + 2 *m, n));
	}
    }
}

int graph_run_tests() {
}

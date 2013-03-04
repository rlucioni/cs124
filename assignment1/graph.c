#include "graph.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define SQUARE(x) ((x) * (x))
#define SWAP(x,y) { a ^= b; b ^= a; a ^= b; }
#define MIN(x,y) (((x) <= (y)) ? (x) : (y))

static graph *graph_generate_0(int);
static graph *graph_generate_euclidean(int, int);
static void graph_edge_merge(edge *, int, int, int, edge *);

graph *graph_generate_0(int numpoints) {
    graph *g = (graph *) malloc(sizeof(graph));
    g->num_nodes = numpoints;
    g->num_edges = numpoints;
    g->list = (edge *) malloc(sizeof(edge) * g->num_edges);

    int max_width_cutoff = 10000;
    float max_width = .002;
    
    int e = 0;
    for (int i = 1; i < numpoints; ++i) {
	for (int j = 0; j < i; ++j) {
	    float w = (float) rand() / RAND_MAX;
	    if (numpoints < max_width_cutoff || w < max_width) {
		if (e >= g->num_edges) {
		    g->num_edges *= 2;
		    g->list = realloc(g->list, sizeof(edge) * g->num_edges);
		}
		edge e_local = { .u = i, .v = j, .weight = w };
		g->list[e++] = e_local;
	    }
	}
    }
    g->num_edges = e;
    
    return g;
}

graph *graph_generate_euclidean(int dimensions, int numpoints) {
    graph *g = (graph *) malloc(sizeof(graph));
    g->num_nodes = numpoints;
    g->num_edges = numpoints;
    g->list = malloc(sizeof(edge) * g->num_edges);

    float ps[numpoints][dimensions]; // array of points, each of dimensions dimensions
    for (int i = 0; i < numpoints; ++i) {
	for (int d = 0; d < dimensions; ++d) {
	    ps[i][d] = (float) rand() / RAND_MAX;
	}
    }

    int max_width_cutoff = 5000;
    float max_width = (dimensions == 2) ? 0.05 : (dimensions == 3) ? 0.15 : 0.3;

    int e = 0;
    for (int i = 0; i < numpoints; ++i) {
	for (int j = 0; j < i; ++j) {
	    float distance = 0;
	    for (int d = 0; d < dimensions; ++d) {
		distance += SQUARE(ps[i][d] - ps[j][d]);
	    }
	    float w = sqrt(distance);
	    if (numpoints < max_width_cutoff || w < max_width) {
		if (e >= g->num_edges) {
		    g->num_edges *= 2;
		    g->list = realloc(g->list, sizeof(edge) * g->num_edges);
		}
		edge e_local = { .u = i, .v = j, .weight = w };
		g->list[e++] = e_local;
	    }
	}
    }
    g->num_edges = e;

    return g;
}

graph *graph_generate(int dimensions, int numpoints) {
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


void graph_edge_merge(edge *src, int s1, int s2, int end, edge *dest) {
    int i, l, r;
    for (i = s1, l = s1, r = s2; l < s2 && r < end; ++i) 
	dest[i] = (src[l].weight <= src[r].weight) ? src[l++] : src[r++];
    if (l < s2) {
	for (; i < end; ++i, ++l)
	    dest[i] = src[l];	
    }
    else {
	for (; i < end; ++i, ++r) 
	    dest[i] = src[r];	
    }
}

void graph_edge_sort(graph *g) {
    // printf("EDGE SORT BEGIN\n");
    int n = g->num_edges;
    edge *a = g->list;
    edge *b = malloc(sizeof(edge) * n);
    for (int m = 1; m < n; m *= 2) {
	for (int i = 0; i < n; i += 2 * m) {
	    graph_edge_merge(a, i, MIN(i + m, n), MIN(i + 2 * m, n), b);
	}
	edge *temp = a;
	a = b;
	b = temp;
    }
    if (a != g->list) {
	memcpy(g->list, a, sizeof(edge) * n);
	free(a);
    }
    else
	free(b);
}

void graph_print(graph *g) {
    printf("# of Nodes: %d\n", g->num_nodes);
    printf("# of Edges: %d\n", g->num_edges);
    printf("Edge Weights: [");
    for (int i = 0; i < g->num_edges; ++i) {
	printf("%s%.02f", (i == 0) ? "" : ", ", g->list[i].weight);
    }
    printf("]\n");
    /*    for (int i = 0; i < g->num_edges; ++i)
	printf("\t(%d, %d) : %f\n", g->list[i].u, g->list[i].v, g->list[i].weight);
	printf("\n");*/
}

int test_graph_generate_0() {
    int num_nodes = 20;
    graph *g = graph_generate_0(num_nodes);
    assert(g->num_nodes == num_nodes);
    for (int i = 0; i < g->num_edges; ++i) {
	assert(g->list[i].weight <= 1);
	assert(g->list[i].weight >= 0);
    }

    return 0;
}

int test_graph_generate_euclidean() {
    int num_nodes = 20;
    for (int d = 2; d <= 4; ++d) {
	graph *g = graph_generate_euclidean(d, num_nodes);
	assert(g->num_nodes == num_nodes);

	float max_weight = sqrt(d);
	for (int i = 0; i < g->num_edges; ++i) {
	    assert(g->list[i].weight <= max_weight);
	    assert(g->list[i].weight >= 0);
	}
    }

    return 0;
}


int graph_run_tests() {
    test_graph_generate_0();
    test_graph_generate_euclidean();
    return 0;
}

test_graphs *graph_test_graphs() {
    test_graphs *graphs = (test_graphs *) malloc(sizeof(test_graphs));
    graphs->num_graphs = 4;
    graphs->graphs = malloc(sizeof(edge) * graphs->num_graphs);
    graphs->mst_weights = malloc(sizeof(float) * graphs->num_graphs);

    edge *l0 = malloc(sizeof(edge) * 0);
    edge *l1 = malloc(sizeof(edge) * 1);
    edge *l2 = malloc(sizeof(edge) * 3);
    edge *l3 = malloc(sizeof(edge) * 6);
    edge l1_local[1] = { { .u = 0, .v = 1, .weight = 0.5 } }; 
    edge l2_local[3] = { { .u = 0, .v = 1, .weight = 0.1 }, { .u = 1, .v = 2, .weight = 0.7 }, { .u = 2, .v = 0, .weight = 0.5 } };
    edge l3_local[6] = { { .u = 0, .v = 1, .weight = 1.0 }, { .u = 0, .v = 2, .weight = 0.6 }, { .u = 0, .v = 3, .weight = 0.4 }, 
		 { .u = 1, .v = 2, .weight = 0.3 }, { .u = 1, .v = 3, .weight = 0.1 }, { .u = 2, .v = 3, .weight = 0.2 } };
    memcpy(l1, &l1_local, sizeof(edge) * 1);
    memcpy(l2, &l2_local, sizeof(edge) * 3);
    memcpy(l3, &l3_local, sizeof(edge) * 6);

    graphs->graphs[0].list = l0;
    graphs->graphs[0].num_nodes = 1;
    graphs->graphs[0].num_edges = 0;
    graphs->mst_weights[0] = 0.0;

    graphs->graphs[1].list = l1;
    graphs->graphs[1].num_nodes = 2;
    graphs->graphs[1].num_edges = 1;
    graphs->mst_weights[1] = 0.5;

    graphs->graphs[2].list = l2;
    graphs->graphs[2].num_nodes = 3;
    graphs->graphs[2].num_edges = 3;
    graphs->mst_weights[2] = 0.6;

    graphs->graphs[3].list = l3;
    graphs->graphs[3].num_nodes = 4;
    graphs->graphs[3].num_edges = 6;
    graphs->mst_weights[3] = 0.7;

    return graphs;
}

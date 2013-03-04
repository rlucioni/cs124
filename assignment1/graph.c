#include "graph.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

// MACROs
#define SQUARE(x) ((x) * (x))
#define MIN(x,y) (((x) <= (y)) ? (x) : (y))

// PROTOTYPEs
static graph *graph_generate_0(int);
static graph *graph_generate_euclidean(int, int);
static void graph_edge_merge(edge *, int, int, int, edge *);

// graph_generate_0:
//    Generates graph w/ num_nodes vertices where edge lengths
//    are assigned random values between 0 and 1
//    num_nodes must be > 1
graph *graph_generate_0(int num_nodes) {
    // allocate memory
    graph *g = (graph *) malloc(sizeof(graph));
    g->num_nodes = num_nodes;
    g->num_edges = num_nodes;
    g->list = (edge *) malloc(sizeof(edge) * g->num_edges);

    // for values of num_nodes > max_width_cutoff do not include
    //    edges of width > max_width as these edges will not be
    //    in MST (see writeup for more info)
    int max_width_cutoff = 10000;
    float max_width = .002;
    
    // generate edges w/ random edge weights for graph, dynamically
    //    updating the size of the edge list to allow for more edges;
    //    we do not know value to begin w/ since we do not add
    //    all edges (see above comment)
    int e = 0;
    for (int i = 1; i < num_nodes; ++i) {
	for (int j = 0; j < i; ++j) {
	    float w = (float) rand() / RAND_MAX;
	    if (num_nodes < max_width_cutoff || w < max_width) {
		if (e >= g->num_edges) {
		    g->num_edges *= 2;
		    g->list = realloc(g->list, sizeof(edge) * g->num_edges);
		}
		edge e_local = { .u = i, .v = j, .weight = w };
		g->list[e++] = e_local;
	    }
	}
    }
    // reset num_edges based on number of edges actually added
    g->num_edges = e;
    
    return g;
}

// graph_generate_euclidean:
//    Generates graph w/ num_nodes vertices where vertices are
//    points in n-dimensional space w/ random coordinate values b/t 0 and 1
//    where n = dimensions (argument);
//    dimensions and num_nodes must be > 1
graph *graph_generate_euclidean(int dimensions, int num_nodes) {
    // allocate memory
    graph *g = (graph *) malloc(sizeof(graph));
    g->num_nodes = num_nodes;
    g->num_edges = num_nodes;
    g->list = malloc(sizeof(edge) * g->num_edges);

    // randomly generate points in n-dimensional space
    float ps[num_nodes][dimensions];
    for (int i = 0; i < num_nodes; ++i) {
	for (int d = 0; d < dimensions; ++d) {
	    ps[i][d] = (float) rand() / RAND_MAX;
	}
    }

    // for values of num_nodes > max_width_cutoff do not include
    //    edges of width > max_width as these edges will not be
    //    in MST (see writeup for more info)
    int max_width_cutoff = 5000;
    float max_width = (dimensions == 2) ? 0.05 : (dimensions == 3) ? 0.15 : 0.3;

    // generate edges w/ weights from pregenerated pointsn
    //    updating the size of the edge list to allow for more edges;
    //    we do not know value to begin w/ since we do not add
    //    all edges (see above comment)
    int e = 0;
    for (int i = 0; i < num_nodes; ++i) {
	for (int j = 0; j < i; ++j) {
	    float distance = 0;
	    for (int d = 0; d < dimensions; ++d) {
		distance += SQUARE(ps[i][d] - ps[j][d]);
	    }
	    float w = sqrt(distance);
	    if (num_nodes < max_width_cutoff || w < max_width) {
		if (e >= g->num_edges) {
		    g->num_edges *= 2;
		    g->list = realloc(g->list, sizeof(edge) * g->num_edges);
		}
		edge e_local = { .u = i, .v = j, .weight = w };
		g->list[e++] = e_local;
	    }
	}
    }
    // reset num_edges based on number of edges actually added
    g->num_edges = e;

    return g;
}

graph *graph_generate(int dimensions, int num_nodes) {
    // call appropriate graph generation function
    switch (dimensions) {
    case 0: return graph_generate_0(num_nodes);
    case 2: 
    case 3: 
    case 4: return graph_generate_euclidean(dimensions, num_nodes);
    default: return NULL;
    }
}

// graph_edge_merge(src, s1, s2, end, dest):
//    helper function for bottom-up mergesort implementation
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

// graph_edge_sort(g):
//    bottom-up implementation of mergesort
void graph_edge_sort(graph *g) {
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

// test_graph_generate_0():
//    tests the number of nodes and edge weights
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

// test_graph_generate_euclidean():
//    tests the number of nodes and edge weights
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
    l1 = l1_local;
    l2 = l2_local;
    l3 = l3_local;

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

void graph_free(graph *g) {
    free(g->list);
    free(g);
}

void graph_free_test_graphs(test_graphs *ts) {
    for (int i = 0; i < ts->num_graphs; ++i)
	free(ts->graphs[i].list);
    free(ts->graphs);
    free(ts->mst_weights);
    free(ts);
}

#include "graph.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#ifndef INC_ASSERT_H
#define INC_ASSERT_H
#include <assert.h>
#endif

#define SQUARE(x) ((x) * (x))
#define SWAP(x,y) { a ^= b; b ^= a; a ^= b; }
#define MIN(x,y) (((x) <= (y)) ? (x) : (y))

static graph *graph_generate_0(int);
static graph *graph_generate_euclidean(int, int);
static void graph_edge_merge(edge *, int, int, int);

graph *graph_generate_0(int numpoints) {
    graph *g = (graph *) malloc(sizeof(graph));
    g->num_nodes = numpoints;
    g->num_edges = (numpoints - 1) * numpoints / 2;
    g->list = (edge *) malloc(sizeof(edge) * g->num_edges);

    int e = 0;
    for (int i = 1; i < numpoints; ++i) {
	for (int j = 0; j < i; ++j) {
	    g->list[e].u = i;
	    g->list[e].v = j;
	    g->list[e].weight = (float) rand() / RAND_MAX;
	    ++e;
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
	    ps[i][d] = (float) rand() / RAND_MAX;
	}
    }
    for (int i = 0, e = 0; i < numpoints; ++i) {
	for (int j = 0; j < i; ++j) {
	    float distance = 0;
	    for (int d = 0; d < dimensions; ++d) {
		distance += SQUARE(ps[i][d] - ps[j][d]);
	    }
	    edge edg = { .u = i, .v = j, .weight = sqrt(distance) };
	    g->list[e] = edg;
	    ++e;
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

void graph_edge_merge(edge *list, int s1, int s2, int end) {
    int l_size = s2 - s1;
    int r_size = end - s2;

    edge left[l_size];
    edge right[r_size];
    memcpy(&left, list + s1, sizeof(edge) * l_size);
    memcpy(&right, list + s2, sizeof(edge) * r_size);

    int i, l, r;
    for (i = s1, l = 0, r = 0; l < l_size && r < r_size; ++i) 
	list[i] = (left[l].weight <= right[r].weight) ? left[l++] : right[r++];
    if (l < l_size) {
	for (; i < end; ++i, ++l)
	    list[i] = left[l];
    }
    else {
	for (; i < end; ++i, ++r) 
	    list[i] = right[r];
    }
}

void graph_edge_sort(graph *g) {
    for (int m = 1; m < g->num_edges; m *= 2) {
	for (int i = 0; i < g->num_edges - m; i += 2 * m) {
	    graph_edge_merge(g->list, i, i + m, MIN(i + 2 *m, g->num_edges));
	}
    }
}

void graph_print(graph *g) {
    printf("# of Nodes: %d\n", g->num_nodes);
    printf("# of Edges: %d\n", g->num_edges);
    for (int i = 0; i < g->num_edges; ++i)
	printf("\t(%d, %d) : %f\n", g->list[i].u, g->list[i].v, g->list[i].weight);
    printf("\n");
}

int test_graph_generate_0() {
    int num_nodes = 20;
    graph *g = graph_generate_0(num_nodes);
    assert(g->num_nodes == num_nodes);
    assert(g->num_edges == (num_nodes - 1) * num_nodes / 2);

    // each node should be attached to num_nodes - 1 edges
    // keep array of nodes, and increment when touched by edge
    // all edge lengths should be less than 1
    int nodes[num_nodes];
    memset(&nodes, 0, sizeof(int) * num_nodes);

    for (int i = 0; i < g->num_edges; ++i) {
	assert(g->list[i].weight <= 1);
	assert(g->list[i].weight >= 0);
	++nodes[g->list[i].u];
	++nodes[g->list[i].v];
    }
    int edges_per_node = g->num_edges - 1;
    for (int i = 0; i < num_nodes; ++i)
	assert(nodes[i] == edges_per_node);

    return 0;
}

int test_graph_generate_euclidean() {
    int num_nodes = 20;
    for (int d = 2; d <= 4; ++d) {
	graph *g = graph_generate_euclidean(d, num_nodes);
	assert(g->num_nodes == num_nodes);
	assert(g->num_edges == (num_nodes - 1) * num_nodes / 2);

	int nodes[num_nodes];
	memset(&nodes, 0, sizeof(int) * num_nodes);
	float max_weight = sqrt(d);
	for (int i = 0; i < g->num_edges; ++i) {
	    assert(g->list[i].weight <= max_weight);
	    assert(g->list[i].weight >= 0);
	    ++nodes[g->list[i].u];
	    ++nodes[g->list[i].v];
	}
	int edges_per_node = g->num_edges - 1;
	for (int i = 0; i < num_nodes; ++i)
	    assert(nodes[i] == edges_per_node);
    }

    return 0;
}

int test_graph_edge_merge() {
    /*    // duplicate
    edge d2[2] = { { 0, 0, .5}, { 1, 1, .5} };
    edge d3[3] = { { 0, 0, .5}, { 1, 1, .5}, { 2, 2, .5} };
    edge d4[4] = { { 0, 0, .5}, { 1, 1, .5}, { 2, 2, .5}, { 3, 3, .5} };
    edge d5[5] = { { 0, 0, .5}, { 1, 1, .5}, { 2, 2, .5}, { 3, 3, .5}, { 4, 4, .5} };

    // sorted
    edge s2[2] = { { 0, 0, .1}, { 1, 1, .2} };
    edge s3[3] = { { 0, 0, .1}, { 1, 1, .2}, { 2, 2, .3} };
    edge s4[4] = { { 0, 0, .1}, { 1, 1, .2}, { 2, 2, .3}, { 3, 3, .4} };
    edge s5[5] = { { 0, 0, .1}, { 1, 1, .2}, { 2, 2, .3}, { 3, 3, .4}, { 4, 4, .5} };

    // unsorted/interleaved
    edge u2[2] = { { 1, 1, .2}, { 0, 0, .1} };
    edge u3[3] = { { 0, 0, .1}, { 2, 2, .3}, { 1, 1, .2} };
    edge u4[4] = { { 0, 0, .1}, { 3, 3, .4}, { 1, 1, .2}, { 2, 2, .3} };
    edge u5[5] = { { 0, 0, .1}, { 2, 2, .3}, { 4, 4, .5}, { 1, 1, .2}, { 3, 3, .4} };

    graph_edge_merge(&d2, 0, 1, 2);
    graph_edge_merge(&d3, 0, 2, 3);
    graph_edge_merge(&d4, 0, 2, 4);
    graph_edge_merge(&d5, 0, 3, 5);
    assert(d2[2] == { { 0, 0, .5}, { 1, 1, .5} });
    assert(d3[3] == { { 0, 0, .5}, { 1, 1, .5}, { 2, 2, .5} });
    assert(d4[4] == { { 0, 0, .5}, { 1, 1, .5}, { 2, 2, .5}, { 3, 3, .5} });
    assert(d5[5] == { { 0, 0, .5}, { 1, 1, .5}, { 2, 2, .5}, { 3, 3, .5}, { 4, 4, .5} });

    graph_edge_merge(&s2, 0, 1, 2);
    graph_edge_merge(&s3, 0, 2, 3);
    graph_edge_merge(&s4, 0, 2, 4);
    graph_edge_merge(&s5, 0, 3, 5);
    assert(s2[2] == { { 0, 0, .1}, { 1, 1, .2} });
    assert(s3[3] == { { 0, 0, .1}, { 1, 1, .2}, { 2, 2, .3} });
    assert(s4[4] == { { 0, 0, .1}, { 1, 1, .2}, { 2, 2, .3}, { 3, 3, .4} });
    assert(s5[5] == { { 0, 0, .1}, { 1, 1, .2}, { 2, 2, .3}, { 3, 3, .4}, { 4, 4, .5} });

    graph_edge_merge(&u2, 0, 1, 2);
    graph_edge_merge(&u3, 0, 2, 3);
    graph_edge_merge(&u4, 0, 2, 4);
    graph_edge_merge(&u5, 0, 3, 5);
    assert(u2[2] == { { 0, 0, .1}, { 1, 1, .2} });
    assert(u3[3] == { { 0, 0, .1}, { 1, 1, .2}, { 2, 2, .3} });
    assert(u4[4] == { { 0, 0, .1}, { 1, 1, .2}, { 2, 2, .3}, { 3, 3, .4} });
    assert(u5[5] == { { 0, 0, .1}, { 1, 1, .2}, { 2, 2, .3}, { 3, 3, .4}, { 4, 4, .5} });
    */
    return 0;
}

int test_graph_edge_sort() {
    /*
    // single
    edge l1[1] = { { 0, 0, .1} };
    
    // duplicate
    edge d2[2] = { { 0, 0, .5}, { 1, 1, .5} };
    edge d3[3]; = { { 0, 0, .5}, { 1, 1, .5}, { 2, 2, .5} };
    edge d4[4]; = { { 0, 0, .5}, { 1, 1, .5}, { 2, 2, .5}, { 3, 3, .5} };
    edge d5[5]; = { { 0, 0, .5}, { 1, 1, .5}, { 2, 2, .5}, { 3, 3, .5}, { 4, 4, .5} };

    // sorted
    edge s2[2] = { { 0, 0, .1}, { 1, 1, .2} };
    edge s3[3] = { { 0, 0, .1}, { 1, 1, .2}, { 2, 2, .3} };
    edge s4[4] = { { 0, 0, .1}, { 1, 1, .2}, { 2, 2, .3}, { 3, 3, .4} };
    edge s5[5] = { { 0, 0, .1}, { 1, 1, .2}, { 2, 2, .3}, { 3, 3, .4}, { 4, 4, .5} };

    // unsorted/interleaved
    edge u2[2] = { { 1, 1, .2}, { 0, 0, .1} };
    edge u3[3] = { { 0, 0, .1}, { 2, 2, .3}, { 1, 1, .2} };
    edge u4[4] = { { 0, 0, .1}, { 3, 3, .4}, { 1, 1, .2}, { 2, 2, .3} };
    edge u5[5] = { { 0, 0, .1}, { 2, 2, .3}, { 4, 4, .5}, { 1, 1, .2}, { 3, 3, .4} };

    graph g = { .list = &l1, .num_nodes = 1, .num_edges = 2};
        graph_edge_sort(&g);
    */
    return 0;
}

int graph_run_tests() {
    test_graph_generate_0();
    test_graph_generate_euclidean();
    test_graph_edge_merge();
    test_graph_edge_sort();

    return 0;
}

test_graph *graph_test_graphs() {
    test_graph *tgs = (test_graph *) malloc(sizeof(test_graph) * 4);
    edge *l1 = malloc(sizeof(edge) * 0);
    edge *l2 = malloc(sizeof(edge) * 1);
    edge *l3 = malloc(sizeof(edge) * 3);
    edge *l4 = malloc(sizeof(edge) * 6);
    edge l2_local[1] = { { .u = 0, .v = 1, .weight = 0.5 } }; 
    edge l3_local[3] = { { .u = 0, .v = 1, .weight = 0.1 }, { .u = 1, .v = 2, .weight = 0.7 }, { .u = 2, .v = 0, .weight = 0.5 } };
    edge l4_local[6] = { { .u = 0, .v = 1, .weight = 1.0 }, { .u = 0, .v = 2, .weight = 0.6 }, { .u = 0, .v = 3, .weight = 0.4 }, 
		 { .u = 1, .v = 2, .weight = 0.3 }, { .u = 1, .v = 3, .weight = 0.1 }, { .u = 2, .v = 3, .weight = 0.2 } };
    memcpy(l2, &l2_local, sizeof(edge) * 1);
    memcpy(l3, &l3_local, sizeof(edge) * 3);
    memcpy(l4, &l4_local, sizeof(edge) * 6);

    tgs[0].graph.list = l1;
    tgs[0].graph.num_nodes = 1;
    tgs[0].graph.num_edges = 0;
    tgs[0].mst_weight = 0.0;

    tgs[1].graph.list = l2;
    tgs[1].graph.num_nodes = 2;
    tgs[1].graph.num_edges = 1;
    tgs[1].mst_weight = 0.5;

    tgs[2].graph.list = l3;
    tgs[2].graph.num_nodes = 3;
    tgs[2].graph.num_edges = 3;
    tgs[2].mst_weight = 0.6;

    tgs[3].graph.list = l4;
    tgs[3].graph.num_nodes = 4;
    tgs[3].graph.num_edges = 6;
    tgs[3].mst_weight = 0.7;

    return tgs;
}

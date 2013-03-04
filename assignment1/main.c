#include "graph.h"
#include "disjoint-set.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float max_weight = 0.0;

// Kruskal's returns an adjacency matrix of the MST, indexed by node
float kruskals(graph *input_graph) {
    // our X is a summation of the weights - we asked about this on Piazza
    float mst_weight = 0.0;

    // sort edges of input_graph by weight <- side effect
    graph_edge_sort(input_graph);
    //printf("EDGES SORTED\n");

    // make space for the vertex sets
    ds_forest *f = ds_makeforest(input_graph->num_nodes);
    //printf("FOREST GROWN\n");
    
    // for each vertex in input_graph, makeset containing vertex
    for (int n = 0; n < input_graph->num_nodes; n++)
        ds_makeset(f, n);
    //printf("VERTEX SETS CREATED\n");

    // cycle through edges in input_graph
    for (int e = 0; e < input_graph->num_edges; e++) {
        int node_u = input_graph->list[e].u;
        int node_v = input_graph->list[e].v;
        if (ds_find(f, node_u) != ds_find(f, node_v)) {
            mst_weight += input_graph->list[e].weight;
	    max_weight = input_graph->list[e].weight;
            ds_union(f, node_u, node_v);
        }
    }

    ds_burnforest(f);

    return mst_weight;
}

int main(int argc, char **argv) {
    // process command line args
    if (argc != 5) {
	    fprintf(stderr, "usage: %s flag numpoints numtrials dimension\n", argv[0]);
	    exit(1);
    }
    int flag = atoi(argv[1]);
    int numpoints = atoi(argv[2]);
    int numtrials = atoi(argv[3]);
    int dimension = atoi(argv[4]);

    // check against invalid args
    if (flag > 3 || flag < 0)
	fprintf(stderr, "flag %d has no meaning\nrunning in standard mode...\n", flag);
    else if (numpoints < 0) {
	fprintf(stderr, "numpoints must be greater than 0\n");
	exit(1);
    }
    else if (numtrials < 0) {
	fprintf(stderr, "numtrials must be greater than 0\n");
	exit(1);
    }
    else if (dimension > 4 || dimension == 1 || dimension < 0) {
	fprintf(stderr, "dimension 0 or in range [2,...,4]\n");
	exit(1);
    }

    if (flag == 1) {
        test_graphs *tests = graph_test_graphs();
        for (int n = 0; n < tests->num_graphs; n++) { 
            if (fabsf(tests->mst_weights[n] - kruskals(&tests->graphs[n])) < 0.00001)
                printf("TEST %d: PASS\n", n);
            else {
                printf("TEST %d: FAIL\n", n);
                exit(EXIT_FAILURE);
            }
        }

        return 0;
    }

    if (flag == 2) {
	ds_run_tests();
	graph_run_tests();
	return 0;
    }

    if (numpoints <= 0) {
        fprintf(stderr, "No tree exists for a graph with %d vertices", numpoints);
        exit(EXIT_FAILURE);
    }
    
    // run trials
    float running_total = 0.0;
    srand(time(NULL));
    for (int i = 0; i < numtrials; ++i) {
	graph *g = graph_generate(dimension, numpoints);
	running_total += kruskals(g);
	graph_free(g);
    }

    if (flag == 3) {
	printf("Maximum Edge Weight: %f\n", max_weight);
	return 0;
    }

    printf("%f %d %d %d\n", running_total / numtrials, numpoints, numtrials, dimension);
    return 0;
}

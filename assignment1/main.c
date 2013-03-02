#include "graph.h"
#include "disjoint-set.h"
#include <stdio.h>
#include <stdlib.h>

void print_edge_weights(graph *g) {
    printf("edge weights: [");
    for (int i = 0; i < g->num_nodes; i++)
	printf("%s%.2f", (i == 0) ? "" : ", ", g->list[i].weight);
    printf("]\n");
}

// Kruskal's returns an adjacency matrix of the MST, indexed by node
float kruskals(graph *input_graph) {
    // our X is a summation of the weights - we asked about this on Piazza
    float mst_weight = 0.0;

    // sort edges of input_graph by weight <- side effect
    //print_edge_weights(input_graph);
    graph_edge_sort(input_graph);
    //print_edge_weights(input_graph);
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
            ds_union(f, node_u, node_v);
        }
    }

    ds_burnforest(f);

    return mst_weight;
}

int main(int argc, char **argv) {
    // process command line arguments
    if (argc != 5) {
	    fprintf(stderr, "usage: %s flag numpoints numtrials dimension\n", argv[0]);
	    exit(1);
    }
    int flag = atoi(argv[1]);
    int numpoints = atoi(argv[2]);
    int numtrials = atoi(argv[3]);
    int dimension = atoi(argv[4]);

    if (flag == 1) {
        test_graph *test_array = graph_test_graphs();
	// some test comparisons may fail because of the inherent inaccuracy in
	// floating point arithmetic
	int length = 4;
        for (int n = 0; n < length; n++) { 
            if (test_array[n].mst_weight == kruskals(&test_array[n].graph))
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
    for (int i = 0; i < numtrials; ++i) {
	graph *g = graph_generate(dimension, numpoints);
    //printf("GRAPH GENERATED\n");
	running_total += kruskals(g);
    //printf("KRUSKALS COMPLETE\n\n");
	graph_free(g);
    }

    printf("%f %d %d %d\n", running_total / numtrials, numpoints, numtrials, dimension);
    return 0;
}

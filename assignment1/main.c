#include "graph.h"
#include "disjoint-set.h"
#include <stdio.h>

// Kruskal's returns an adjacency matrix of the MST, indexed by node
float kruskals(graph *input_graph) {
    // our X is a summation of the weights - we asked about this on Piazza
    float mst_weight = 0;

    // sort edges of input_graph by weight <- side effect
    graph_edge_sort(input_graph->list);

    // make space for the vertex sets
    forest *f = makeforest(input_graph->num_nodes);
    
    // for each vertex in input_graph, makeset containing vertex
    for (int n = 0; n < input_graph->num_nodes; n++)
        ds_makeset(f, n);

    // cycle through edges in input_graph
    for (int e = 0; e < input_graph->num_edges; e++) {
        int node_u = input_graph->list[e].u;
        int node_v = input_graph->list[e].v;
        if ds_find(f, node_u) == ds_find(f, node_v) {
            mst_weight += mst_weight + input_graph->list[e].weight
            ds_union(f, node_u, node_v);
        }
    }

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
        int length = sizeof(test_array)/sizeof(test_array[0]);
        for (int n = 0; n < length; n++) { 
            if test_array[n]->mst_weight == kruskals(test_array[n]->graph)
                printf("TEST %d: PASS", n);
            else {
                printf("TEST %d: FAIL", n);
                exit(EXIT_FAILURE);
            }
        }

        return 0;
    }

    if (flag == 2) {
       return graph_run_tests();
    }

    if numpoints <= 0 {
        fprintf(stderr, "No tree exists for a graph with %d vertices", numpoints);
        exit(EXIT_FAILURE);
    }
    
    // run trials
    float running_total = 0;
    for (int i = 0; i < numtrials; ++i) {
	    graph *g = generate_graph(dimension, numpoints);
	    running_total += kruskals(g);
	    free_graph(g);
    }

    printf("%f %d %d %d\n", running_total / numpoints, numpoints, numtrials, dimension);
    return 0;
}

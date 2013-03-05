#include "graph.h"
#include "disjoint-set.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// GLOBALS
float max_weight = 0.0; // max weight of any MST seen so far

// Kruskal's algorithm:
//    Returns the weight of an MST of the input graph instead of the MST itself
//    in order to avoid an unnecessary pass through the MST to sum edge weights
//    which would result in an extra n summations (permission received for this on
//    Piazza)
float kruskals(graph *input_graph) {
    // Running MST weight
    float mst_weight = 0.0;

    // Sort edges of input_graph by weight
    graph_edge_sort(input_graph);

    // Allocate memory for disjoint set forest
    ds_forest *f = ds_make_forest(input_graph->num_nodes);
    
    // For each vertex: 
    //    Makeset containing vertex
    for (int n = 0; n < input_graph->num_nodes; n++)
        ds_make_set(f, n);

    // For each edge:
    //    Check whether the vertices are connected and if not add the edge
    //    to the MST (add the weight to running total) and connect (union)
    //    the vertices in the disjoint set forest; Update maximum
    //    weight added to the MST
    for (int e = 0; e < input_graph->num_edges; e++) {
        int node_u = input_graph->list[e].u;
        int node_v = input_graph->list[e].v;
        if (ds_find(f, node_u) != ds_find(f, node_v)) {
            mst_weight += input_graph->list[e].weight;
	    // Conditional necessary for multiple runs
	    if (input_graph->list[e].weight > max_weight)
		max_weight = input_graph->list[e].weight;
            ds_union(f, node_u, node_v);
        }
    }

    // Free memory of disjoint set forest
    ds_burn_forest(f);

    // Return MST weight
    return mst_weight;
}

int main(int argc, char **argv) {
    // Process command line args
    if (argc != 5) {
	    fprintf(stderr, "usage: %s flag numpoints numtrials dimension\n", argv[0]);
	    exit(1);
    }
    int flag = atoi(argv[1]);
    int numpoints = atoi(argv[2]);
    int numtrials = atoi(argv[3]);
    int dimension = atoi(argv[4]);

    // Check against invalid args
    if (flag > 4 || flag < 0)
	fprintf(stderr, "flag %d has no meaning\nrunning in standard mode...\n", flag);
    else if (numpoints <= 1) {
	fprintf(stderr, "numpoints must be greater than 1\n");
	exit(1);
    }
    else if (numtrials <= 0) {
	fprintf(stderr, "numtrials must be greater than 0\n");
	exit(1);
    }
    else if (dimension > 4 || dimension == 1 || dimension < 0) {
	fprintf(stderr, "dimension 0 or in range [2,...,4]\n");
	exit(1);
    }

    // Flag 1:
    //    Run on predefined graphs w/ precalculated mst weights and compare
    //    to verfy correctness of implementation
    if (flag == 1) {
        test_graphs *tests = graph_test_graphs();
        for (int n = 0; n < tests->num_graphs; n++) { 
            if (fabsf(tests->mst_weights[n] - kruskals(&tests->graphs[n])) < 0.00001)
                printf("TEST %d: PASS\n", n);
            else
                printf("TEST %d: FAIL\n", n);
        }
        return 0;
    }

    // Flag 2:
    //    Run tests to verify the correctness of graph generation and the
    //    disjoint set implementation (tests are defined in respective
    //    files)
    if (flag == 2) {
	ds_run_tests();
	graph_run_tests();
	return 0;
    }
    
    // Run tests maintaining avg.
    // Seed rand here as opposed to w/in generate function to avoid reseeding
    int time_total = 0;;
    srand(time(NULL));
    float running_total = 0.0;
    for (int i = 0; i < numtrials; ++i) {
	graph *g = graph_generate(dimension, numpoints);
	clock_t start = clock();
	running_total += kruskals(g);
	time_total += clock() - start;
	graph_free(g);
    }

    // Flag 3:
    //    Print out max edge weight from all MSTs over the course of all runs
    //    (not averaged). Used to determine appropriate cutoff values for 
    //    edge size
    if (flag == 3) {
	printf("Maximum Edge Weight: %f\n", max_weight);
	return 0;
    }

    // Flag 4:
    //    Print out average runtime of algorithm.
    //    Used for determining alogrithmic runtime.
    else if (flag == 4) {
	// Output styled for Mathematica/Woflram Alpha
	int msec = time_total * 1000 / CLOCKS_PER_SEC;
	printf("{%d, %f}\n", numpoints, (float) msec / numtrials);
	return 0;
    }

    // Print out results
    printf("%f %d %d %d\n", running_total / numtrials, numpoints, numtrials, dimension);
    return 0;
}

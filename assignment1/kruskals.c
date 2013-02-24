#include "graph.h"
#include "disjoint-set.h"
#include "heap.h"
#include <stdio.h>
#include <assert.h>

float prims(graph *g) {
    int s;
    float mst_weight = 0;
    int num_vertices = graph_size(g);
    float dist[num_vertices];
    float prev[num_vertices];
    int S[num_vertices];
    

    heap *h = make_heap();
    insert(h, s, 0);
    for (int i = 0; i < num_vertices; ++i) {
	dist[i] = -1;
	prev[i] = NULL;
    }
    dist[s] = 0;
    while (size(h) > 0) {
	int v = deletemin(h);
	S[v] = 1;

    }
    

    return mst_weight;
}


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

    if (flag == 1)
	run_tests();
    
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

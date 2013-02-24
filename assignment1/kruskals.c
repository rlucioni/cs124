#include "graph.h"
#include "disjoint-set.h"
#include "heap.h"
#include <stdio.h>

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
	for (int w = 0; w 
    }
    

    return mst_weight;
}


// Kruskal's returns an adjacency matrix of the MST, indexed by node

float kruskals(graph *input_graph) {
    // initialize new graph - empty
    float mst_weight = 0;

    // sort edges of input_graph by weight

    // for each vertex in input_graph, makeset containing vertex
    forest *f = makeforest(graph_size(g));
    
    // cycle through edges in input_graph

        // if endpoints not in the same vertex set, union the edge with edges in output_graph
        
        // union the endpoint sets
        
    return mst_weight;
}

graph* sum_edges(input_graph*) {
    int sum = 0;

    // loop through edges in input_graph, add to sum

    return sum;
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

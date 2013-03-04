// graph.h
//    graph.h/graph.c implement graph data structures and helper
//    functions for working with those data structures

// edge:
//    u,v = vertices
//    weight = edge weight
typedef struct {
    int u;
    int v;
    float weight;
} edge;

// graph:
//    Edge list implementation
typedef struct {
    edge *list;
    int num_nodes;
    int num_edges;
} graph;

// test_raphs:
//    Predefined graphs with predefined MST weights to be used
//    for testing correctness of algorithm.
//    graphs and mst_weights are parallel arrays
typedef struct {
    graph *graphs;
    float *mst_weights;
    int num_graphs;
} test_graphs;

// generate_graph(dimensions, numpoints):
//    Returns a pointer to a graph w/ num_nodes vertices;
//    For explanation of the dimensions variable see assignment
//    specification
graph *graph_generate(int dimensions, int num_nodes);

// graph_test_graphs()
//    Return an array of test_graphs for correctness checking
test_graphs *graph_test_graphs();

// graph_edge_sort(g):
//    Sort edge list of g
void graph_edge_sort(graph *g);

// graph_print(g):
//    Print graph (for debugging purposes)
void graph_print(graph *g);

// graph_run_tests():
//    Run tests on graph generation functions
int graph_run_tests();

// Memory deallocation functions
void graph_free(graph *g);
void graph_free_test_graphs(test_graphs *ts);

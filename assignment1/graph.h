typedef struct {
    int u;
    int v;
    float weight;
} edge;

typedef struct {
    edge *list;
    int num_nodes;
    int num_edges;
} graph;

typedef struct {
    graph *graphs;
    float *mst_weights;
    int num_graphs;
} test_graphs;

// generate_graph(dimensions, numpoints)
//    Returns a pointer to a graph of w/ numpoints vertices (nodes). 
//    For explanation of the dimensions variable see assignment 
//    specification
graph *graph_generate(int dimensions, int numpoints);
void graph_free(graph *g);
void graph_edge_sort(graph *g);

int graph_run_tests();
test_graphs *graph_test_graphs();
void graph_print(graph *g);

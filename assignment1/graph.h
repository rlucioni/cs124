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
    graph *graph;
    float mst_weight;
} test_graph;

// generate_graph(dimensions, numpoints)
//    Returns a pointer to a graph of w/ numpoints vertices (nodes). 
//    For explanation of the dimensions variable see assignment 
//    specification
graph *graph_generate(int dimensions, int numpoints);
void graph_free(graph *g);

int graph_run_tests();
test_graph *graph_test_graphs();

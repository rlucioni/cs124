typedef struct {
    float **adj_matrix;
    int num_nodes;
} graph;

// generate_graph(dimensions, numpoints)
//    Returns a pointer to a graph of w/ numpoints vertices (nodes). 
//    For explanation of the dimensions variable see assignment 
//    specification
graph *graph_generate(int dimensions, int numpoints);
void graph_free(graph *g);
int graph_size(graph *g);

// get_edge(n1, n2)
//    Returns the weight of the edge between n1 and n2
//    If no edge exists between n1 and n2, get_edge returns
//    -1.
float graph_get_edge(graph *g, int n1, int n2);

int graph_run_tests();

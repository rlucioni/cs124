typedef struct {
    float **adj_matrix;
    int num_nodes;
} graph;

// empty_graph()
//    Returns a pointer to an empty graph
graph *empty_graph(int numpoints);
void free_graph(graph *g);

// generate_graph(dimensions, numpoints)
//    Returns a pointer to a graph of w/ numpoints vertices (nodes). 
//    For explanation of the dimensions variable see assignment 
//    specification
graph *generate_graph(int dimensions, int numpoints);

// get_edge(n1, n2)
//    Returns the weight of the edge between n1 and n2
//    If no edge exists between n1 and n2, get_edge returns
//    -1.
float get_edge(graph *g, int n1, int n2);
void add_edge(graph *g, int n1, int n2, float weight);
void delete_edge(graph *g, int n1, int n2);


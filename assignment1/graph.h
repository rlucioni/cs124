typedef graph **float;
typedef node int;

// empty_graph()
//    Returns a pointer to an empty graph
graph *empty_graph();

// generate_graph(dimensions, numpoints)
//    Returns a pointer to a graph of w/ numpoints vertices (nodes). 
//    For explanation of the dimensions variable see assignment 
//    specification
graph *generate_graph(int dimensions, int numpoints);

// get_edge(n1, n2)
//    Returns the weight of the edge between n1 and n2
//    If no edge exists between n1 and n2, get_edge returns
//    -1.
float get_edge(node *n1, node *n2);

void add_edge(graph *g, node *n1, node *n2);
void delete_edge(graph *g, node *n1, node *n2);


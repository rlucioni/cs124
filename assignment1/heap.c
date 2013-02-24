#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

#define BASE_SIZE 16

#define PARENT(i) (((i) % 2 == 0) ? ((i) - 2) / 2 : ((i) - 1) / 2)  
#define LCHILD(i) (2*(i)+1)
#define RCHILD(i) (2*(i)+2)

heap *make_heap() {
    heap *h = (heap *) malloc(sizeof(heap));
    h->nodes = (node *) malloc(sizeof(node) * BASE_SIZE);
    h->num_nodes = 0;
    h->size = BASE_SIZE;
    return h;
}

void free_heap(heap *h) {
    free(h->nodes);
    free(h);
}

void insert(heap *h, int key, int value) {
    // allocate memory if necessary
    if (++h->num_nodes > h->size) {
	h->size <<= 1;
	realloc(h->nodes, h->size);
	if (!h->nodes) {
	    fprintf(stderr, "Memory Error: line %d in %s", __LINE__, __FILE__);
	    exit(EXIT_FAILURE);
	}
    }

    node n = { .key = key, .value = value }
    int i = h->num_nodes - 1;
    int p = PARENT(i);
    h->nodes[i] = n;
    while (i >=0 && h->nodes[i].value < h->nodes[p].value) {
	node temp = h->nodes[p];
	h->nodes[p] = h->nodes[i];
	h->nodes[i] = temp;
	i = p;
	p = PARENT(i);
    }
}

int deletemin(heap *h) {
    int min = h->nodes[0].key;
    --h->num_nodes;

    h->nodes[0] = h->nodes[h->num_nodes];
    int i = 0;
    int l = LCHILD(i);
    int r = RCHILD(i);
    int child;
    while(1) {
	if (l >= h->num_nodes && r < h->num_nodes)
	    child = r;
	else if (l < h->num_nodes && r >= h->num_nodes)
	    child = l;
	else if (l < h->bum_nodes && r < h->num_nodes)
	    child = (h->nodes[l].value < h->nodes[r].value) ? l : r;
	else
	    break;

	if (h->nodes[i].value > h->nodes[child].value) {
	    node temp = h->nodes[child];
	    h->nodes[child] = h->nodes[i];
	    h->nodes[i] = temp;
    	}
	else 
	    break;
    }

    return min;
}

int size(heap *h) {
    return h->num_nodes;
}

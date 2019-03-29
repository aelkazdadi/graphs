#ifndef GRAPH_H
#define GRAPH_H

#define NLINKS 100000000lu
#include <inttypes.h>

typedef uint32_t fixedInt;

typedef struct {
  fixedInt s;
  fixedInt t;
} edge;

// Graphs are undirected unless otherwise specified

typedef struct {
  fixedInt n;  // number of nodes
  fixedInt e;  // number of edges
  edge *edges; // list of edges
} edgeList;

typedef struct {
  fixedInt n;  // number of nodes
  char **rows; // Matrix elements as bits of chars
} adjacencyMatrix;

/*
 * We assume the number of edges, along with their duplicates, in the case of
 * undirected graphs, can fit inside an fixedInt.
 */

typedef struct {
  fixedInt n;
  fixedInt e;
  fixedInt *cd;
  fixedInt *adj;
} adjacencyArray;

// compute the maximum of three fixedInt
static inline fixedInt max3(fixedInt a, fixedInt b, fixedInt c) {
  a = (a > b) ? a : b;
  return (a > c) ? a : c;
}

static inline fixedInt min3(fixedInt a, fixedInt b, fixedInt c) {
  a = (a < b) ? a : b;
  return (a < c) ? a : c;
}

int compareEdges(const void *a, const void *b);

void checkOrder(char *input);

/*
 * Cleaned files for undirected edges are assumed to have the following
 * format:
 * - One line containing the number of nodes and edges in the format {V E}
 * - E lines of edges in the format {u v} sorted lexicographically
 */

// read undirected cleaned files of edges
edgeList *readEdgeList(char *input);
adjacencyArray *readAdjacencyArray(char *input);
adjacencyMatrix *readAdjacencyMatrix(char *input);

/*
 * Files containing edges of directed graphs are assumed to have the following
 * format:
 *  - Any number of lines of comments prefixed by '#'
 *  - One empty line
 *  - Edges in the format {u v} sorted lexicographically
 */

// read directed file of edges as adjacency array
adjacencyArray *readDirected(char *input);

void freeEdgelist(edgeList *g);
void freeAdjacencyArray(adjacencyArray *g);
void freeAdjacencyMatrix(adjacencyMatrix *g);

#endif

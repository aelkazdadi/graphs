#ifndef GRAPH_H
#define GRAPH_H

#define NLINKS 100000000lu

typedef struct {
  unsigned long s;
  unsigned long t;
} edge;

// Graphs are undirected unless otherwise specified

typedef struct {
  unsigned long n; // number of nodes
  unsigned long e; // number of edges
  edge *edges;     // list of edges
} edgeList;

typedef struct {
  unsigned long n; // number of nodes
  char **rows;     // Matrix elements as bits of chars
} adjacencyMatrix;

typedef struct {
  unsigned long int n;
  unsigned long int e;
  unsigned long long int *cd;
  unsigned long int *adj;
} adjacencyArray;

// compute the maximum of three unsigned long
inline unsigned long max3(unsigned long a, unsigned long b, unsigned long c) {
  a = (a > b) ? a : b;
  return (a > c) ? a : c;
}

inline unsigned long min3(unsigned long a, unsigned long b, unsigned long c) {
  a = (a < b) ? a : b;
  return (a < c) ? a : c;
}

edgeList *readEdgeList(char *input);
adjacencyArray *readAdjacencyArray(char *input);
adjacencyMatrix *readAdjacencyMatrix(char *input);

void freeEdgelist(edgeList *g);
void freeAdjacencyArray(adjacencyArray *g);
void freeAdjacencyMatrix(adjacencyMatrix *g);

#endif

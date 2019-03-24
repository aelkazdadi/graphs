#include "array.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  long unsigned int node;
  long unsigned int degree;
} ndPair;

typedef struct {
  long unsigned int n;
  ndPair *array;
} ndArray;

typedef struct {
  long unsigned int u;
  long unsigned int v;
  long unsigned int w;
} triangle;

typedef struct {
  long unsigned int n;
  triangle *array;
} triangleArray;

int compare(const void *a, const void *b) {
  ndPair *m = (ndPair *)a;
  ndPair *n = (ndPair *)b;
  return (m->degree < n->degree) - (m->degree > n->degree);
}

triangleArray getTriangles(adjacencyArray *g) {
  triangleArray out;
  ndArray sortedNodes;
  sortedNodes.n = g->n;
  sortedNodes.array = malloc(g->n * sizeof(ndPair));

  for (long unsigned int i = 0; i < g->n; ++i) {
    sortedNodes.array[i].node = i;
    sortedNodes.array[i].degree = g->cd[i+1] - g->cd[i];
  }
  qsort(sortedNodes.array, g->n, sizeof(ndPair), compare);
  return out;
}

int main(int argc, char **argv) {}

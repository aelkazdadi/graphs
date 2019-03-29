#include "array.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  fixedInt node;
  fixedInt degree;
} ndPair;

typedef struct {
  fixedInt n;
  ndPair *array;
} ndArray;

typedef struct {
  fixedInt u;
  fixedInt v;
  fixedInt w;
} triangle;

typedef struct {
  fixedInt n;
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
  // FIXME: Array.array has type fixedInt *
  sortedNodes.n = g->n;
  sortedNodes.array = malloc(g->n * sizeof(ndPair));

  for (fixedInt i = 0; i < g->n; ++i) {
    sortedNodes.array[i].node = i;
    sortedNodes.array[i].degree = g->cd[i + 1] - g->cd[i];
  }
  qsort(sortedNodes.array, g->n, sizeof(ndPair), compare);
  return out;
}

int main(int argc, char **argv) {}

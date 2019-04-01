#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  fixedInt n;
  fixedInt d;
} pair;

int compare(const void *a, const void *b) {
  pair *m = (pair *)a;
  pair *n = (pair *)b;
  return (m->d < n->d) - (m->d > n->d);
}

fixedInt* getTriangles(adjacencyArray *g) {
  fixedInt *out;
  pair *sortedNodes = malloc(g->n * sizeof(pair));;

  for (fixedInt i = 0; i < g->n; ++i) {
    sortedNodes[i].n = i;
    sortedNodes[i].d = g->cd[i + 1] - g->cd[i];
  }
  qsort(sortedNodes, g->n, sizeof(pair), compare);
  return out;
}

int main(int argc, char **argv) {}

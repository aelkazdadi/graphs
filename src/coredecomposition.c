#include "array.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  long unsigned int n;
  long unsigned int d;
} pair;

int compare(const void *a, const void *b) {
  // u < v if degree(u) < degree(v)
  pair *u = (pair *)a;
  pair *v = (pair *)b;
  return (u->d > v->d) - (u->d < v->d);
}

long unsigned int max(long unsigned int a, long unsigned int b) {
  return (a > b) ? a : b;
}

long unsigned int *coreDecomposition(adjacencyArray *g) {
  long unsigned int *coreValue = malloc(g->n * sizeof(long unsigned int));

  pair *orderedNodes = malloc(g->n * sizeof(pair));

  for (long unsigned int i = 0; i < g->n; ++i) {
    orderedNodes[i].n = i;
    orderedNodes[i].d = g->cd[i + 1] - g->cd[i];
  }
  // Sort vertices by degree
  qsort(orderedNodes, g->n, sizeof(pair), compare);

  // Inverse of previous order
  long unsigned int *invOrd = malloc(g->n * sizeof(long unsigned int));
  for (long unsigned int i = 0; i < g->n; ++i) {
    invOrd[orderedNodes[i].n] = i;
  }

  // Index of first appearance of each degree in ordered array of nodes
  long unsigned int *firstIndex = malloc(g->n * sizeof(long unsigned int));
  long unsigned int d = 0;
  long unsigned int i = 0;

  firstIndex[0] = 0;
  while (d < g->n && i < g->n) {
    while (d < orderedNodes[i].d) {
      firstIndex[d] = i;
      ++d;
    }
    firstIndex[d] = i;
    while (d == orderedNodes[i].d) {
      ++i;
    }
    ++d;
  }
  firstIndex[d] = g->n + 1;

  long unsigned int *removed = calloc(g->n, sizeof(long unsigned int));

  long unsigned int c = 0;
  i = 0;
  while (i < g->n) {
    long unsigned int node = orderedNodes[i].n;
    c = max(c, orderedNodes[i].d);
    // Remove node i from graph
    removed[node] = 1;
    ++firstIndex[orderedNodes[i].d];

    long unsigned int neighborStart = g->cd[node];
    long unsigned int neighborEnd = g->cd[node + 1];
    for (unsigned long j = neighborStart; j < neighborEnd; ++j) {
      long unsigned int neighbor = g->adj[j];
      if (!removed[neighbor]) {
        long unsigned int neighborDegree = g->cd[neighbor + 1] - g->cd[neighbor];

        long unsigned int first = firstIndex[neighborDegree];
        long unsigned int index = invOrd[neighbor];

        // Reduce degree of neighbors of i and reorder
        orderedNodes[index].n = orderedNodes[first].n;
        orderedNodes[index].d = orderedNodes[first].d;

        orderedNodes[first].n = neighbor;
        orderedNodes[first].d = neighborDegree - 1;

        // Update inverse order
        // of element swapped with neighbor
        invOrd[orderedNodes[first].n] = first;
        // of neighbor
        invOrd[orderedNodes[index].n] = index;

        // Update first index of old degree of neighbor
        ++firstIndex[neighborDegree];
      }
    }

    coreValue[orderedNodes[i].n] = c;
    ++i;
  }

  free(firstIndex);
  free(orderedNodes);
  return coreValue;
}

int main(int argc, char **argv) {
  adjacencyArray *g = readAdjacencyArray(argv[1]);
  long unsigned int *coreValue = coreDecomposition(g);
}

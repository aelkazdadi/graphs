#include "array.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  fixedInt n;
  fixedInt d;
} pair;

int compare(const void *a, const void *b) {
  // u < v if degree(u) < degree(v)
  pair *u = (pair *)a;
  pair *v = (pair *)b;
  return (u->d > v->d) - (u->d < v->d);
}

fixedInt max(fixedInt a, fixedInt b) { return (a > b) ? a : b; }

fixedInt *coreDecomposition(adjacencyArray *g) {
  fixedInt *coreValue = malloc(g->n * sizeof(fixedInt));

  pair *orderedNodes = malloc(g->n * sizeof(pair));

  for (fixedInt i = 0; i < g->n; ++i) {
    orderedNodes[i].n = i;
    orderedNodes[i].d = g->cd[i + 1] - g->cd[i];
  }
  // Sort vertices by degree
  qsort(orderedNodes, g->n, sizeof(pair), compare);

  // Inverse of previous order
  fixedInt *invOrd = malloc(g->n * sizeof(fixedInt));
  for (fixedInt i = 0; i < g->n; ++i) {
    invOrd[orderedNodes[i].n] = i;
  }

  // Index of first appearance of each degree in ordered array of nodes
  fixedInt *firstIndex = malloc(g->n * sizeof(fixedInt));
  fixedInt d = 0;
  fixedInt i = 0;

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

  fixedInt *removed = calloc(g->n, sizeof(fixedInt));

  fixedInt c = 0;
  i = 0;
  while (i < g->n) {
    fixedInt node = orderedNodes[i].n;
    c = max(c, orderedNodes[i].d);
    // Remove node i from graph
    removed[node] = 1;
    ++firstIndex[orderedNodes[i].d];

    fixedInt neighborStart = g->cd[node];
    fixedInt neighborEnd = g->cd[node + 1];
    for (fixedInt j = neighborStart; j < neighborEnd; ++j) {
      fixedInt neighbor = g->adj[j];
      if (!removed[neighbor]) {
        fixedInt neighborDegree = orderedNodes[invOrd[neighbor]].d;

        fixedInt first = firstIndex[neighborDegree];
        fixedInt index = invOrd[neighbor];

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
  fixedInt *coreValue = coreDecomposition(g);
}

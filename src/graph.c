#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

void free_edgelist(edgelist *g) {
  free(g->edges);
  free(g);
}

// reading the edgelist from file
edgelist *readedgelist(char *input) {
  unsigned long e1 = NLINKS;
  FILE *file = fopen(input, "r");

  edgelist *g = malloc(sizeof(edgelist));
  g->n = 0;
  g->e = 0;
  g->edges = malloc(e1 * sizeof(edge)); // allocate some RAM to store edges

  while (fscanf(file, "%lu%lu", &(g->edges[g->e].s), &(g->edges[g->e].t)) ==
         2) {
    g->n = max3(g->n, g->edges[g->e].s, g->edges[g->e].t);
    if (g->e++ == e1) { // increase allocated RAM if needed
      e1 += NLINKS;
      g->edges = realloc(g->edges, e1 * sizeof(edge));
    }
  }
  fclose(file);

  g->n++;

  g->edges = realloc(g->edges, g->e * sizeof(edge));

  return g;
}

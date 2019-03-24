#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

// reading the edge list from file
edgeList* readEdgeList(char* input) {
  FILE* file = fopen(input, "r");

  edgeList* g = malloc(sizeof(edgeList));

  if (fscanf(file, "%lu%lu", &(g->n), &(g->e)) != 2) return g;

  g->edges = malloc(g->e * sizeof(edge)); // allocate some RAM to store edges

  long unsigned int i = 0;
  long unsigned int s = 0;
  long unsigned int t = 0;
  while (fscanf(file, "%lu%lu", &s, &t) == 2) {
    g->edges[i].s = s;
    g->edges[i].t = t;
    ++i;
  }

  fclose(file);

  return g;
}

adjacencyMatrix* readAdjacencyMatrix(char* input) {
  FILE* file = fopen(input, "r");
  adjacencyMatrix* g = malloc(sizeof(adjacencyMatrix));

  unsigned char bits[8];
  bits[0] = 1 << 0;
  bits[1] = 1 << 1;
  bits[2] = 1 << 2;
  bits[3] = 1 << 3;
  bits[4] = 1 << 4;
  bits[5] = 1 << 5;
  bits[6] = 1 << 6;
  bits[7] = 1 << 7;

  long unsigned s;
  long unsigned t;

  if (fscanf(file, "%lu%lu", &(g->n), &s) != 2) return g;
  g->rows = malloc((g->n) * sizeof(char *));

  long unsigned int nBlocks = ((g->n) >> 3) + 1;
  for (long unsigned int i = 0; i < (g->n); ++i) {
    g->rows[i] = malloc(sizeof(char) * nBlocks);
  }

  while (fscanf(file, "%lu%lu", &s, &t) == 2) {
    long unsigned int sBlock = s >> 3;
    long unsigned int tBlock = t >> 3;

    unsigned char sPos = s & 7;
    unsigned char tPos = t & 7;

    g->rows[s][tBlock] |= bits[tPos];
    g->rows[t][sBlock] |= bits[sPos];
  }

  return g;
}

void freeAdjacencyMatrix(adjacencyMatrix* g) {
  for (long unsigned int i = 0; i < g->n; ++i) {
    free(g->rows[i]);
  }
  free(g->rows);
  free(g);
}

void freeEdgelist(edgeList* g) {
  free(g->edges);
  free(g);
}

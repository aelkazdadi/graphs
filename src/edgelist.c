#include <locale.h>
#include <stdio.h>
#include <time.h> //to estimate the runing time
#include "timer.h"
#include "graph.h"

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");

  struct timespec t1, t2;
  // Window size
  unsigned long int h = 5;

  edgeList *g;

  printf("Input file: %s\n", argv[1]);
  g = readEdgeList(argv[1]);

  printf("%lu nodes\n", g->n);
  printf("%lu edges\n", g->e);

  printf("Head of edge list:\n");
  for (int i = 0; i < h; ++i) {
    printf("%lu %lu\n", g->edges[i].s, g->edges[i].t);
  }

  freeEdgelist(g);

  adjacencyMatrix* m = readAdjacencyMatrix(argv[1]);
  unsigned long int p = 2;
  unsigned long int q = 17;
  h = 2;
  printf("Matrix rows %lu to %lu, cols %lu to %lu\n", p - h, p + h, q - h, q + h);
  for (unsigned long int i = p - h; i < p + h + 1; ++i) {
    for (unsigned long int j = q - h; j < q + h + 1; ++j) {
      printf("%u ", ((m->rows[i][j >> 3]) & (1 << (j & 7))) >> (j & 7));
    }
    printf("\n");
  }
  printf("\n");
  freeAdjacencyMatrix(m);

  return 0;
}

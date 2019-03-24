#include "graph.h"
#include "timer.h"
#include <locale.h>
#include <stdio.h>

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");

  struct timespec clock[10];
  // Window size
  unsigned long int h = 5;

  edgeList *g;

  printf("Input file: %s\n", argv[1]);
  getTime(clock);
  g = readEdgeList(argv[1]);
  getTime(clock + 1);

  printf("%lu nodes\n", g->n);
  printf("%lu edges\n", g->e);
  printf("-----------------------------\n");

  printf("Edge list read in %Lf seconds\n",
         timeDiff(clock, clock + 1) / NSEC_IN_SEC);
  printf("Head of edge list:\n");
  for (int i = 0; i < h; ++i) {
    printf("%lu %lu\n", g->edges[i].s, g->edges[i].t);
  }

  freeEdgelist(g);

  getTime(clock);
  adjacencyMatrix *m = readAdjacencyMatrix(argv[1]);
  getTime(clock + 1);
  printf("\nAdjacency matrix read in %Lf seconds\n",
         timeDiff(clock, clock + 1) / NSEC_IN_SEC);
  unsigned long int p = 2;
  unsigned long int q = 17;
  h = 2;

  printf("Matrix rows %lu to %lu, cols %lu to %lu\n", p - h, p + h, q - h,
         q + h);
  for (unsigned long int i = p - h; i < p + h + 1; ++i) {
    for (unsigned long int j = q - h; j < q + h + 1; ++j) {
      printf("%u ", ((m->rows[i][j >> 3]) & (1 << (j & 7))) >> (j & 7));
    }
    printf("\n");
  }
  freeAdjacencyMatrix(m);

  getTime(clock);
  adjacencyArray *a = readAdjacencyArray(argv[1]);
  getTime(clock + 1);
  printf("\nAdjacency array read in %Lf seconds\n",
         timeDiff(clock, clock + 1) / NSEC_IN_SEC);
  printf("Head of adjacency array:\n");

  h = 5;
  int l = 10;
  for (int i = 0; i < h; ++i) {
    printf("%d : ", i);
    int j;
    for (j = a->cd[i]; (j < a->cd[i] + l) && (j < a->cd[i + 1]); ++j) {
      printf("%lu ", a->adj[j]);
    }
    if (j < a->cd[i + 1]) {
      printf("...");
    }
    printf("\n");
  }
  printf("\n");

  return 0;
}

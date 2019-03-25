#include "graph.h"
#include "timer.h"
#include <stdlib.h>
#include <stdio.h>

void mulMatVec(adjacencyArray *g, double *vec, double* out) {
}

int main(int argc, char **argv) {
  struct timespec clock[10];

  getTime(clock);
  adjacencyArray *a = readDirected(argv[1]);
  getTime(clock + 1);
  printf("\nAdjacency array read in %Lf seconds\n",
         timeDiff(clock, clock + 1) / NSEC_IN_SEC);
  printf("Head of adjacency array:\n");

  long unsigned int h = 40;
  int l = 1000;
  for (int i = 0; i < h; ++i) {
    printf("%d : %llu : ", i, a->cd[i+1]-a->cd[i]);
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
}

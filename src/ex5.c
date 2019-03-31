#include "degree.h"
#include "graph.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  struct timespec *clock = malloc(3 * sizeof(struct timespec));
  fixedInt e1 = NLINKS;
  fixedInt n1 = NLINKS;

  getTime(clock);
  FILE *file = fopen(argv[1], "r");

  fixedInt s, t = 0;
  long long unsigned int Q = 0;

  edgeList *g = malloc(sizeof(edgeList));

  if (fscanf(file, "%u%u", &(g->n), &(g->e)) != 2)
    return EXIT_FAILURE;

  fixedInt *degrees = malloc(g->n * sizeof(fixedInt));
  g->edges = malloc(g->e * sizeof(edge));

  fixedInt e = 0;

  while (fscanf(file, "%u%u", &s, &t) == 2) {
    g->edges[e].s = s;
    g->edges[e].t = t;
    ++(degrees[s]);
    ++(degrees[t]);
    ++e;
  }

  fclose(file);
  getTime(clock + 1);

  for (fixedInt i = 0; i < g->e; ++i) {
    Q += degrees[g->edges[i].s] * degrees[g->edges[i].t];
  }

  getTime(clock + 2);
  printf("Q_G: %llu\n", Q);
  printf("%Lf seconds to build edge and degree lists.\n",
         timeDiff(clock, clock + 1) / 1000000000.0L);
  printf("%Lf seconds to calculate Q_G.\n",
         timeDiff(clock + 1, clock + 2) / 1000000000.0L);
}

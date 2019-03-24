#include "degree.h"
#include "graph.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  struct timespec *clock = malloc(3 * sizeof(struct timespec));
  unsigned long e1 = NLINKS;
  unsigned long n1 = NLINKS;

  getTime(clock);
  FILE *file = fopen(argv[1], "r");

  long unsigned int s, t = 0;
  long long unsigned int Q = 0;

  long unsigned int *degrees = malloc(e1 * sizeof(long unsigned int));
  edgeList *g = malloc(sizeof(edgeList));
  g->n = 0;
  g->e = 0;
  g->edges = malloc(e1*sizeof(edge));
  while (fscanf(file, "%lu%lu", &s, &t) == 2) {
    g->n = max3(g->n, s, t);
    --s;
    --t;
    g->edges[g->e].s = s;
    g->edges[g->e].t = t;
    ++(degrees[s]);
    ++(degrees[t]);

    if (g->e++ == e1) { // increase allocated RAM if needed
      e1 += NLINKS;
      g->edges = realloc(g->edges, e1 * sizeof(edge));
    }
    if (g->n == n1) { // increase allocated RAM if needed
      n1 += NLINKS;
      degrees = realloc(degrees, n1 * sizeof(long unsigned int));
    }
  }

  fclose(file);
  getTime(clock + 1);

  for (long unsigned int i = 0; i < g->e; ++i)
  {
    Q += degrees[g->edges[i].s] * degrees[g->edges[i].t];
  }

  getTime(clock + 2);
  printf("Q_G: %llu\n", Q);
  printf("%Lf seconds to build edge and degree lists.\n",
         timeDiff(clock, clock + 1) / 1000000000.0L);
  printf("%Lf seconds to calculate Q_G.\n",
         timeDiff(clock + 1, clock + 2) / 1000000000.0L);
}

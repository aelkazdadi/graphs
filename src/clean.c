#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void clean(char *input, char *output) {
  printf("%s\n", input);
  printf("%s\n", output);

  FILE *in = fopen(input, "r");
  FILE *out = fopen(output, "w");

  if (in == NULL || out == NULL)
    return ;

  char *line = NULL;
  size_t size = 0;
  ssize_t getLineResult;
  int scanResult;

  unsigned int nComments = 0;
  long long unsigned int e1 = NLINKS;

  do {
    getLineResult = getline(&line, &size, in);
    ++nComments;
  } while (getLineResult > 0 && line[0] == '#');
  --nComments;

  unsigned long s, t = 0;

  edgelist *g = malloc(sizeof(edgelist));
  g->n = 0;
  g->e = 0;
  g->edges = malloc(e1 * sizeof(edge));

  scanResult = sscanf(line, "%lu%lu", &s, &t);
  while (scanResult == 2) {
    if (s < t) {
      g->n = max3(g->n, s, t);
      g->edges[g->e].s = s;
      g->edges[g->e].t = t;
      fprintf(out, "%lu %lu\n", s, t);

      if (g->e++ == 1) {
        e1 += NLINKS;
        g->edges = realloc(g->edges, e1 * sizeof(edge));
      }
    }
    scanResult = fscanf(in, "%lu%lu", &s, &t);
  }
  fclose(in);
  fclose(out);

  printf("%lu %lu\n", g->n, g->e);
}

int main(int argc, char **argv) { clean(argv[1], argv[2]); }

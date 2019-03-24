#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int compare(const void* a, const void* b) {
  edge *e1 = (edge *) a;
  edge *e2 = (edge *) b;
  return 2 * ((e1->s > e2->s) - (e1->s < e2->s)) +
         ((e1->t > e2->t) - (e1->t < e2->t));
}

int main(int argc, char **argv) {
  printf("Input file: %s\n", argv[1]);
  printf("Output file: %s\n", argv[2]);

  // Count lines in input file
  char command[10000];
  strcpy(command, "wc -l ");
  strcat(command, argv[1]);
  printf("Running \"%s\"...\n", command);
  char buffer[128];
  FILE *fp;
  fp = popen(command, "r");
  long unsigned int nLines;
  if (fgets(buffer, 128, fp) != NULL) {
    nLines = strtoul(buffer, NULL, 10);
  }
  pclose(fp);
  printf("%lu lines found.\n", nLines);

  // Count comments
  char *line = NULL;
  size_t size = 0;
  ssize_t getLineResult;
  int scanResult;

  unsigned int nComments = -1;
  FILE *in = fopen(argv[1], "r");
  if (in == NULL)
    return -1;

  do {
    getLineResult = getline(&line, &size, in);
    ++nComments;
  } while (getLineResult > 0 && line[0] == '#');
  printf("%u comments found.\n", nComments);

  // Store edges in memory
  long unsigned int n = 0;
  long unsigned int e = 0;

  edge *edges = malloc(sizeof(edge) * (nLines - nComments));

  long unsigned s, t = 0;

  scanResult = sscanf(line, "%lu%lu", &s, &t);
  free(line);
  while (scanResult == 2) {
    n = max3(n, s, t);
    if (s > t) {
      long unsigned int tmp = s;
      s = t;
      t = tmp;
    }
    if (s != t) {
      // Discard self loops
      edges[e].s = s - 1;
      edges[e].t = t - 1;
      ++e;
    }
    scanResult = fscanf(in, "%lu%lu", &s, &t);
  }
  fclose(in);
  if (e == 0) return -1;

  // Free unneeded memory
  edges = realloc(edges, e * sizeof(edge));

  // Sort edges
  qsort(edges, e, sizeof(edge), compare);

  // Write edges to output file
  FILE *out = fopen(argv[2], "w");
  fprintf(out, "%lu %lu\n", n, e);

  fprintf(out, "%lu %lu\n", edges[0].s, edges[0].t);
  for (long unsigned int i = 1; i < e; ++i) {
    if (compare(edges+i, edges+(i-1)) > 0)
      fprintf(out, "%lu %lu\n", edges[i].s, edges[i].t);
  }
  fclose(out);
}

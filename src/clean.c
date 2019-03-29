#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
  fixedInt nLines;
  if (fgets(buffer, 128, fp) != NULL) {
    nLines = strtoul(buffer, NULL, 10);
  }
  pclose(fp);
  printf("%u lines found.\n", nLines);

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
  fixedInt max = 0;
  fixedInt min = -1u;
  fixedInt e = 0;

  edge *edges = malloc(sizeof(edge) * (nLines - nComments));

  fixedInt s, t = 0;

  scanResult = sscanf(line, "%u%u", &s, &t);
  free(line);
  while (scanResult == 2) {
    // Track largest and smallest node indices
    max = max3(max, s, t);
    min = min3(min, s, t);
    if (s > t) {
      fixedInt tmp = s;
      s = t;
      t = tmp;
    }
    if (s != t) {
      // Discard self loops
      edges[e].s = s;
      edges[e].t = t;
      ++e;
    }
    scanResult = fscanf(in, "%u%u", &s, &t);
  }
  fclose(in);

  printf("Smallest node index: %u\n", min);
  printf("Largest node index: %u\n", max);
  if (e == 0)
    return -1;

  printf("%u nodes, %u edges found.\n", max - min + 1, e);
  // Free unneeded memory
  edges = realloc(edges, e * sizeof(edge));

  // Sort edges
  qsort(edges, e, sizeof(edge), compareEdges);

  // Write edges to output file
  FILE *out = fopen(argv[2], "w");
  fprintf(out, "%u %u\n", max - min + 1, e);

  fprintf(out, "%u %u\n", edges[0].s - min, edges[0].t - min);
  for (fixedInt i = 1; i < e; ++i) {
    if (compareEdges(edges + i, edges + (i - 1)) > 0) {
      fprintf(out, "%u %u\n", edges[i].s - min, edges[i].t - min);
    }
  }
  fclose(out);
}

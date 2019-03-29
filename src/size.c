#include "graph.h"
#include <inttypes.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

fixedInt getSize(char *input) {
  FILE *file = fopen(input, "r");
  char *line = NULL;
  size_t size = 0;
  ssize_t getLineResult;
  int scanResult;

  unsigned int nComments = 0;
  fixedInt nEdges = 0;

  if (file == NULL)
    return 0;

  do {
    getLineResult = getline(&line, &size, file);
    ++nComments;
  } while (getLineResult > 0 && line[0] == '#');
  --nComments;

  fixedInt s, t = 0;

  scanResult = sscanf(line, "%u%u", &s, &t);
  while (scanResult == 2) {
    ++nEdges;
    scanResult = fscanf(file, "%u%u", &s, &t);
  }
  fclose(file);

  return nEdges;
}

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  printf("%u edges.\n", getSize(argv[1]));
}

#include "degree.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

degreeList* getDegrees(char* input) {
  FILE* file = fopen(input, "r");

  degreeList* out = malloc(sizeof(degreeList));

  unsigned long int tmp;
  if (fscanf(file, "%lu%lu", &(out->n), &tmp) != 2) return NULL;

  out->degrees = malloc((out->n) * sizeof(unsigned long int));

  for (long unsigned int i = 0; i < out->n; ++i) {
    out->degrees[i] = 0;
  }

  unsigned long int s, t = 0;
  while (fscanf(file, "%lu%lu", &s, &t) == 2) {
    ++(out->degrees[s]);
    ++(out->degrees[t]);
  }
  fclose(file);

  return out;
}

void freeDegreeList(degreeList* degrees) { free(degrees->degrees); }

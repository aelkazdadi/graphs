#include "degree.h"
#include "array.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Array *getDegrees(char *input) {
  FILE *file = fopen(input, "r");

  Array *out = malloc(sizeof(Array));

  fixedInt tmp;
  if (fscanf(file, "%u%u", &(out->n), &tmp) != 2)
    return NULL;

  out->array = calloc((out->n), sizeof(fixedInt));

  fixedInt s, t = 0;
  while (fscanf(file, "%u%u", &s, &t) == 2) {
    ++(out->array[s]);
    ++(out->array[t]);
  }
  fclose(file);

  return out;
}

void freeDegreeList(Array *degrees) { free(degrees->array); }

#include "degree.h"
#include "array.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Array *getDegrees(char *input) {
  FILE *file = fopen(input, "r");

  Array *out = malloc(sizeof(Array));

  unsigned long int tmp;
  if (fscanf(file, "%lu%lu", &(out->n), &tmp) != 2)
    return NULL;

  out->array = calloc((out->n), sizeof(unsigned long int));

  unsigned long int s, t = 0;
  while (fscanf(file, "%lu%lu", &s, &t) == 2) {
    ++(out->array[s]);
    ++(out->array[t]);
  }
  fclose(file);

  return out;
}

void freeDegreeList(Array *degrees) { free(degrees->array); }

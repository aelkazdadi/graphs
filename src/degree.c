#include "degree.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

degreeList *getDegrees(char *input) {
  unsigned long e1 = NLINKS;
  FILE *file = fopen(input, "r");

  // allocate some RAM to store degrees
  degreeList *out = malloc(sizeof(degreeList));
  out->n = 0;
  out->degrees = malloc(e1 * sizeof(unsigned long int));

  unsigned long int s, t = 0;
  while (fscanf(file, "%lu%lu", &s, &t) == 2) {
    out->n = max3(out->n, s, t);
    ++out->degrees[s - 1];
    ++out->degrees[t - 1];

    if (out->n + 1 == e1) { // increase allocated RAM if needed
      e1 += NLINKS;
      out->degrees = realloc(out->degrees, e1 * sizeof(unsigned long int));
    }
  }
  fclose(file);

  out->degrees = realloc(out->degrees, out->n * sizeof(unsigned long int));

  return out;
}

void freeDegreeList(degreeList *degrees) { free(degrees->degrees); }

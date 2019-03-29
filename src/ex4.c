#include "degree.h"
#include <stdio.h>

void printDegrees(char *output, Array *degrees) {
  FILE *file = fopen(output, "w");
  for (fixedInt i = 0; i < degrees->n; ++i) {
    fprintf(file, "%u\n", degrees->array[i]);
  }
}

int main(int argc, char **argv) {
  Array *degrees = getDegrees(argv[1]);
  printDegrees(argv[2], degrees);
}

#include <stdio.h>
#include "degree.h"

void printDegrees(char *output, degreeList *degrees)
{
  FILE *file = fopen(output, "w");
  for (unsigned long int i = 0; i < degrees->n; ++i)
  {
    fprintf(file, "%lu\n", degrees->degrees[i]);
  }
}

int main(int argc, char **argv)
{
  degreeList *degrees = getDegrees(argv[1]);
  printDegrees(argv[2], degrees);
}

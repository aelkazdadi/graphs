#ifndef DEGREE_H
#define DEGREE_H

typedef struct {
  long unsigned int n;
  long unsigned int *array;
} Array;

Array *getDegrees(char *input);
void freeDegreeList(Array *degrees);
#endif

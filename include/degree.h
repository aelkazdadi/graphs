#ifndef DEGREE_H
#define DEGREE_H

typedef struct {
  long unsigned int n;
  long unsigned int *degrees;
} degreeList;

degreeList *getDegrees(char *input);
void freeDegreeList(degreeList *degrees);
#endif

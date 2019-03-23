#include <stdio.h>
#include "degree.h"
#include <time.h>
#include "timer.h"

int main(int argc, char **argv) {
  struct timespec t1;
  struct timespec t2;

  getTime(&t1);

  long unsigned int *degrees = getDegrees(argv[1])->degrees;
  FILE *file = fopen(argv[1], "r");

  long unsigned int s, t = 0;
  long long unsigned int Q = 0;
  while (fscanf(file, "%lu%lu", &s, &t) == 2) {
      Q += degrees[s - 1] * degrees[t - 1];
  }
  fclose(file);

  getTime(&t2);
  printf("Q_G: %llu\n", Q);
  printf("Time taken: %Lf\n", timeDiff(&t1, &t2));
}

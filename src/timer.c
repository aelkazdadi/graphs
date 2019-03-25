#include "timer.h"
#include <stdio.h>

void getTime(struct timespec *t) { clock_gettime(CLOCK_MONOTONIC, t); }

long long unsigned int timeDiff(struct timespec *t1, struct timespec *t2) {
  return ((long long unsigned)(t2->tv_sec - t1->tv_sec)) * 1000000000 +
         (t2->tv_nsec - t1->tv_nsec);
}

void dispTime(struct timespec *t, unsigned int n) {
  for (unsigned int i = 0; i < n; ++i) {
    printf("%Lf\n", timeDiff(t + 2*i, t + 2*i + 1) / NSEC_IN_SEC);
  }
}

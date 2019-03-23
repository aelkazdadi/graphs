#include "timer.h"

void getTime(struct timespec *t)
{
  clock_gettime(CLOCK_MONOTONIC, t);
}

long long unsigned timeDiff(struct timespec *t1, struct timespec *t2) {
  return ((long long unsigned)(t2->tv_sec - t1->tv_sec)) * 1000000000 +
         (t2->tv_nsec - t1->tv_nsec);
}

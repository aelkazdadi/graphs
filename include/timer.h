#ifndef TIMER_H
#define TIMER_H
#define NSEC_IN_SEC 1000000000.0L

#include <time.h> //to estimate the runing time

long long unsigned int timeDiff(struct timespec *t1, struct timespec *t2);

void getTime(struct timespec *t);

#endif

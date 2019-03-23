#ifndef TIMER_H
#define TIMER_H
#include <time.h> //to estimate the runing time

long long unsigned int timeDiff(struct timespec *t1, struct timespec *t2);

void getTime(struct timespec *t);

#endif

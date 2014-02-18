#include "Timer.h"

void Timer::start()
{
	clock_gettime(CLOCK_MONOTONIC, &t);
}

long int Timer::nsec_elapsed()
{
	struct timespec p;
	clock_gettime(CLOCK_MONOTONIC, &p);
	return (p.tv_sec - t.tv_sec) * 1000000000 + (p.tv_nsec - t.tv_nsec);
}

long int Timer::sec_elapsed()
{
	struct timespec p;
	clock_gettime(CLOCK_MONOTONIC, &p);
	return p.tv_sec - t.tv_sec;
}

void Timer::sleep(long int sec, long int nsec)
{
	struct timespec p;
	p.tv_sec = sec;
	p.tv_nsec = nsec;
	nanosleep(&p, NULL);
}

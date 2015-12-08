#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

double tstart, tend, ttotal;

double getClock()
{
   	struct timeval tv; 
   	int ok;

   	ok = gettimeofday(&tv, (void *) 0);

   	if (ok < 0)
   		printf("gettimeofday error");

   	return (tv.tv_sec * 1.0 + tv.tv_usec * 1.0E-6);
}

void startTimer()
{
	tstart = 0, tend = 0, ttotal = 0;

	tstart = getClock();
}

void endTimer()
{
	tend = getClock();

	ttotal = tend - tstart;
}

void printTime()
{
	printf("Time = %.9lf\n", ttotal);
}

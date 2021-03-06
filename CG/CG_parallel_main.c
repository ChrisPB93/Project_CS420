#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <mpi.h>
#include <sys/time.h>
#include "test.h"
#include "CG_parallel.h"

int main(int argc, char *argv[])
{
	// Specify size
	int n = atoi(argv[1]);
	int maxIterations = atoi(argv[2]);
	double tolerance = atof(argv[3]);
	int numThreads = atoi(argv[4]);
	int N = n + 1;
	double h = 1.0 / N;

	// Allocate memory
	double (*X)[n] = malloc(sizeof(double) * n * n);
	double (*Y)[n] = malloc(sizeof(double) * n * n);
	double (*A)[n * n] = malloc(sizeof(double) * n * n * n * n);
	double *f = malloc(sizeof(double) * n * n);
	double *x = malloc(sizeof(double) * n * n);

	// Create the test case
	createXAndY(n, h, X, Y);
	createMatrix(n, h, A);
	createRHS(n, h, f, X, Y);

	//Solve equations by LU-decomposition
	conjGrad(n * n, A, f, x, maxIterations,tolerance, numThreads, argc, argv);

	// Free memory
	free(A);
	free(f);
	free(X);
	free(Y);

	return 0;
}

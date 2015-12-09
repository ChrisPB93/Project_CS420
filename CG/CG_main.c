#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "test.h"
#include "CG.h"

int main(int argc, char const *argv[])
{
	// Specify size
	int n = atoi(argv[1]);
	int maxIterations = atoi(argv[2]);
	double tolerance = atof(argv[3]);
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
	conjGrad(n * n, A, f, x, maxIterations,tolerance);


	// Free memory
	free(A);
	free(f);
	free(X);
	free(Y);

	return 0;
}

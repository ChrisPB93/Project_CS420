#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "test.h"
#include "timer.h"

void LU(int N,  double A[N][N], double f[N], double u[N])
{
	double sum;

	// Factorization step
	for (int c = 0; c < N - 1; c++) {
		for (int r = c + 1; r < N; r++) {
			A[r][c] = A[r][c] / A[c][c];

			for (int cc = c + 1; cc < N; cc++) {
				A[r][cc] = A[r][cc] - A[r][c] * A[c][cc];
			}
		}
	}
	
	// Forward substitution step
	for (int r = 0; r < N; r++)	{
		sum = 0;

		for (int c = 0; c < r; c++)
			sum += A[r][c] * u[c];

		u[r] = f[r] - sum;
	}

	// Backward substitution step
	for (int r = N - 1; r >= 0; r--) {
		sum = 0;

		for (int c = r + 1; c < N; c++)
			sum += A[r][c] * u[c];

		u[r] = (u[r] - sum) / A[r][r];
	}		
}

int main(int argc, char *argv[])
{
	int n, N;

	if (argc != 2) {
		fprintf(stderr, "Wrong number of arguments.\nUsage: %s n\n", argv[0]);
		return -1;
	}

	n = atoi(argv[1]); // The number of physical nodes per dimension
	N = n * n; // The number of matrix elements per dimension

	double h = 1.0 / (n + 1);

	// Allocate memory
	double (*X)[n] = malloc(sizeof(double) * n * n);
	double (*Y)[n] = malloc(sizeof(double) * n * n);

	double (*A)[N] = malloc(sizeof(double) * N * N);
	double *f = malloc(sizeof(double) * N);
	double *u = malloc(sizeof(double) * N);

	// Create the test case
	createXAndY(n, h, X, Y);
	createMatrix(n, h, A);
	createRHS(n, h, f, X, Y);

	// Find the solution
	startTimer();
	LU(N, A, f, u);
	endTimer();
	printTime();

	// Check the solution for correctness
	int correct = checkSolution(n, u, X, Y);

	if (!correct) {
		printf("Warning! The algorithm did not produce a correct solution!\n");
		printf("Mean error = %.9f\n", computeError(n, u, X, Y));
	}

	// Free memory
	free(A);
	free(f);
	free(X);
	free(Y);
	free(u);

	return 0;
}


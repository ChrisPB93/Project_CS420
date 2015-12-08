#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <omp.h>

#include "test.h"
#include "timer.h"

void LU(int n, double A[n][n], double f[n], double u[n], int rank, int size)
{
	MPI_Status status;

	int columns = n / size;
	int min = rank * columns;
	int max = min + columns - 1;

	double sum;

	double *cSend = malloc(sizeof(double) * n);
	double *cRecv = malloc(sizeof(double) * n);

	// Factorization step
	for (int c = 0; c < n - 1; c++) {
		if (c >= min && c <= max) {

            #pragma omp parallel for
			for (int r = c + 1; r < n; r++) {
				A[r][c] = A[r][c] / A[c][c];
			}

			if (size > 1) {
			    #pragma omp parallel for
				for (int r = 0; r < n; r++) {
					cSend[r] = A[r][c];
				}

				for (int process = rank + 1; process < size; process++) {
					MPI_Send(cSend, n, MPI_DOUBLE, process, 1, MPI_COMM_WORLD);
				}
			}
		}

		if (c < min) {
			MPI_Recv(cRecv, n, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            #pragma omp parallel for
			for (int r = 0; r < n; r++) {
				A[r][c] = cRecv[r];
			}
		}

        #pragma omp parallel for
		for (int r = c + 1; r < n; r++) {
			for (int cc = min; cc <= max; cc++) {
				A[r][cc] = A[r][cc] - A[r][c] * A[c][cc];
			}
		}
	}

	// Forward substitution step
	for (int r = 0; r < n; r++)	{
		sum = 0;

        #pragma omp parallel for reduction(+:sum)
		for (int c = 0; c < r; c++)
			sum += A[r][c] * u[c];

		u[r] = f[r] - sum;
	}

	// Backward substitution step
	for (int r = n - 1; r >= 0; r--) {
		sum = 0;

        #pragma omp parallel for reduction(+:sum)
		for (int c = r + 1; c < n; c++)
			sum += A[r][c] * u[c];

		u[r] = (u[r] - sum) / A[r][r];
	}
}

int main(int argc, char *argv[])
{
	int rank, size, n, numThreads, N;

	if (argc != 3) {
		fprintf(stderr, "Wrong number of arguments.\nUsage: %s n numThreads\n", argv[0]);
		return -1;
	}

	n = atoi(argv[1]); // The number of physical nodes per dimension
	numThreads = atoi(argv[2]);
	N = n * n; // The number of matrix elements per dimension
	
	omp_set_num_threads(numThreads);
	
	MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

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
	if (rank == size - 1) startTimer();
	LU(N, A, f, u, rank, size);
	if (rank == size - 1) endTimer();
	if (rank == size - 1) printTime();

	MPI_Finalize();

	// Check the solution for correctness
	if (rank == size - 1) {
		int correct = checkSolution(n, u, X, Y);

		if (!correct) {
			printf("Warning! The algorithm did not produce a correct solution!\n");
			printf("Mean error = %.9f\n", computeError(n, u, X, Y));
		}
	}

	// Free memory
	free(A);
	free(f);
	free(X);
	free(Y);
	free(u);

	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include </usr/local/Cellar/gcc/5.2.0/lib/gcc/5/gcc/x86_64-apple-darwin15.0.0/5.2.0/include/omp.h>

#include "LU.h"
#include "test.h"
#include "timer.h"

int main(int argc, char *argv[])
{
	int rank, size;

	MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int n, t;

	if (argc <= 1) {
		n = 4;
		t = 1;
	} else if (argc <= 2) {
		n = atoi(argv[1]);
		t = 1;
	} else {
		n = atoi(argv[1]);
		t = atoi(argv[2]);
	}

	//omp_set_num_threads(t);

	int N = n + 1;
	double h = 1.0 / N;

	if (rank == 0) printf("Matrix size = %d * %d for a total of %d elements\n", n * n, n * n, n * n *n * n);

	// Allocate memory for the test case
	double (*X)[n] = malloc(sizeof(double) * n * n);
	double (*Y)[n] = malloc(sizeof(double) * n * n);
	double (*A)[n * n] = malloc(sizeof(double) * n * n * n * n);
	double *f = malloc(sizeof(double) * n * n);
	double *x = malloc(sizeof(double) * n * n);

	// Create the test case
	createXAndY(n, h, X, Y);
	createMatrix(n, h, A);
	createRHS(n, h, f, X, Y);

	// Sequential version
	if (rank == 0) {
		printf("Sequential\n");
		startTimer();
		LUSequential(n * n, A, f, x);
		endTimer();
		printTime();

		// Display the result
		//printf("x = \n");
		//printVector(n * n, x);
		printf("Last element of x = %f\n", x[n * n - 1]);
	}

	MPI_Barrier(MPI_COMM_WORLD);

	// Parallel version
	createMatrix(n, h, A);

	if (rank == 0) printf("Parallel\n");
	if (rank == 0) startTimer();
	LUParallel(n * n, A, f, x, rank, size);
	if (rank == 0) endTimer();
	if (rank == 0) printTime();

	MPI_Barrier(MPI_COMM_WORLD);

	// Display the result
	if (rank == size - 1) {
		//printf("x = \n");
		//printVector(n * n, x);
		printf("Last element of x = %f\n", x[n * n - 1]);
	}

	// Free memory
	free(A);
	free(f);
	free(X);
	free(Y);
	free(x);

	MPI_Finalize();

	return 0;
}

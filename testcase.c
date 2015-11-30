#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "testcase.h"

/*double forcingTerm(double x, double y);
double exactSltn(double x, double y);
void createXAndY(int n, double h, double (*X)[n], double (*Y)[n]);
void createMatrix(int n, double h, double (*A)[n]);
void createRHS(int n, double h, double *f, double (*X)[n], double (*Y)[n]);
void printMatrix(int n, double (*A)[n]);
void printVector(int n, double *V);*/

/*int main()
{
	// Specify size
	int n = 3;
	int N = n + 1;
	double h = 1.0 / N;

	// Allocate memory
	double (*X)[n] = malloc(sizeof(double) * n * n);
	double (*Y)[n] = malloc(sizeof(double) * n * n);
	double (*A)[n * n] = malloc(sizeof(double) * n * n * n * n);
	double *f = malloc(sizeof(double) * n * n);

	// Create the test case
	createXAndY(n, h, X, Y);
	createMatrix(n, h, A);
	createRHS(n, h, f, X, Y);

	// Display the test case
	printf("X = \n");
	printMatrix(n, X);
	printf("Y = \n");
	printMatrix(n, Y);
	printf("A = \n");
	printMatrix(n * n, A);
	printf("f = \n");
	printVector(n * n, f);

	// Free memory
	free(A);
	free(f);
	free(X);
	free(Y);

	return 0;
}*/

double forcingTerm(double x, double y)
{
	return (pow(x, 2) + pow(y, 2) + 10) * y * sin(x * y) - 2 * x * cos(x * y);
}

double exactSltn(double x, double y)
{
	return y * sin(x * y);
}

void createXAndY(int n, double h, double (*X)[n], double (*Y)[n])
{
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			X[i][j] = h + j * h;
			Y[i][j] = h + i * h;
		}
	}
}

void createMatrix(int n, double h, double (*A)[n * n])
{
	int i, j;

	// Zero entries and the diagonal
	for (i = 0; i < n * n; i++) {
		for (j = 0; j < n * n; j++) {
			A[i][j] = 0;
			A[i][i] = 4 + 10 * pow(h, 2);
		}
	}

	// Upper and lower bands
	j = n;
	for (i = 0; i < n * n - n; i++, j++) {
		A[i][j] = -1;
		A[j][i] = -1;
	}

	// Upper and lower bands adjacent to the diagonal
	j = 1;
	for (i = 0; i < n * n - 1; i++, j++) {
		if (j % n != 0) {
			A[i][j] = -1;
			A[j][i] = -1;
		}
	}

	// Multiply matrix by 1 / h^2
	for (i = 0; i < n * n; i++) {
		for (j = 0; j < n * n; j++) {
			A[i][j] *= 1 / pow(h, 2);
		}
	}
}

void createRHS(int n, double h, double *f, double (*X)[n], double (*Y)[n])
{
	int i, j;
	double x, y;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			x = X[i][j];
			y = Y[i][j];

			f[i * n + j] = forcingTerm(x, y);

			if (x == n * h) {
			  	f[i * n + j] += 1 / pow(h, 2) * y * sin(y);
			}

			// Boundary condition on 
			if (y == n * h) {
			 	f[i * n + j] += 1 / pow(h, 2) * sin(x);
			}
		}
	}
}

void printMatrix(int n, double (*A)[n])
{
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%2.2f ", A[i][j]);
		}
		printf("\n");
	}
}

void printVector(int n, double *V)
{
	int i;

	for (i = 0; i < n; i++) {
		printf("%2.2f\n", V[i]);
	}
}

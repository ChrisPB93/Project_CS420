#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "test.h"

double forcingTerm(double x, double y)
{
	return (pow(x, 2) + pow(y, 2) + 10) * y * sin(x * y) - 2 * x * cos(x * y);
}

double exactSltn(double x, double y)
{
	return y * sin(x * y);
}

int checkSolution(int n, double *u, double (*X)[n], double (*Y)[n])
{
	double sltn, val;
	int index;

	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			index = (n - 1 - i) * n + j;

			sltn = exactSltn(X[i][j], Y[i][j]);

			val = (u[index] - sltn) / sltn;

			if (val < -0.01 || val > 0.01) {
				return 0;
			}
		}
	}

	return 1;
}

double computeError(int n, double *u, double (*X)[n], double (*Y)[n])
{
	double sltn, error = 0;
	int index;

	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			index = (n - 1 - i) * n + j;

			sltn = exactSltn(X[i][j], Y[i][j]);

			error += (u[index] - sltn) / sltn;
		}
	}

	return error / (n * n);
}

void printExactSolution(int n, double (*X)[n], double (*Y)[n])
{
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			printf("%.9f\n", exactSltn(X[i][j], Y[i][j]));
		}
	}
}

void createXAndY(int n, double h, double (*X)[n], double (*Y)[n])
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			X[i][j] = h + j * h;
			Y[i][j] = n * h - i * h;
		}
	}
}

void createMatrix(int n, double h, double (*A)[n * n])
{
	// Zero entries and the diagonal
	for (int i = 0; i < n * n; i++) {
		for (int j = 0; j < n * n; j++) {
			A[i][j] = 0;
			A[i][i] = 4 + 10 * pow(h, 2);
		}
	}

	// Upper and lower bands
	int j = n;
	for (int i = 0; i < n * n - n; i++, j++) {
		A[i][j] = -1;
		A[j][i] = -1;
	}

	// Upper and lower bands adjacent to the diagonal
	j = 1;
	for (int i = 0; i < n * n - 1; i++, j++) {
		if (j % n != 0) {
			A[i][j] = -1;
			A[j][i] = -1;
		}
	}

	// Multiply matrix by 1 / h^2
	for (int i = 0; i < n * n; i++) {
		for (int j = 0; j < n * n; j++) {
			A[i][j] *= 1 / pow(h, 2);
		}
	}
}

void createRHS(int n, double h, double *f, double (*X)[n], double (*Y)[n])
{
	int index;
	double x, y;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			x = X[i][j];
			y = Y[i][j];
			index = (n - 1 - i) * n + j;

			f[index] = forcingTerm(x, y);

			// Boundary condition on the right boundary
			if (x == n * h) {
			  	f[index] += 1 / pow(h, 2) * y * sin(y);
			}

			// Boundary condition on the bottom boundary
			if (y == n * h) {
			 	f[index] += 1 / pow(h, 2) * sin(x);
			}
		}
	}
}

void printMatrix(int n, double (*M)[n])
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%5.3f ", M[i][j]);
		}
		printf("\n");
	}
}

void printVector(int n, double *V)
{
	for (int i = 0; i < n; i++) {
		printf("%.9f\n", V[i]);
	}
}

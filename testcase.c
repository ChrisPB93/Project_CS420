#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double forcingTerm(double x, double y);
double exactSltn(double x, double y);
void createMatrix(int n, double (*A)[n]);
void createRHS(int n, double h, double *f, double (*X)[n], double (*Y)[n]);
void printMatrix(int n, double (*A)[n]);

int main()
{
	int n = 3;
	int N = n + 1;
	double h = 1.0 / N;

	printf("h = %f\n", h);

	double (*X)[n] = malloc(sizeof(double) * n * n);
	double (*Y)[n] = malloc(sizeof(double) * n * n);

	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			X[i][j] = h + j * h;
		}
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			Y[i][j] = h + i * h;
		}
	}

	printMatrix(n, X);
	printf("------------\n");
	printMatrix(n, Y);
	printf("------------\n");

	double (*A)[n * n] = malloc(sizeof(double) * n * n * n * n);
	double *f = malloc(sizeof(double) * n * n);

	createMatrix(n, A);
	createRHS(n, h, f, X, Y);

	printMatrix(n * n, A);

	for (i = 0; i < n * n; i++) {
		printf("%2.2f\n", f[i]);
	}

	free(A);
	free(f);
	free(X);
	free(Y);

	return 0;
}

double forcingTerm(double x, double y)
{
	return (pow(x, 2) + pow(y, 2) + 10) * y * sin(x * y) - 2 * x * cos(x * y);
}

double exactSltn(double x, double y)
{
	return y * sin(x * y);
}

void createMatrix(int n, double (*A)[n * n])
{
	int i, j;

	for (i = 0; i < n * n; i++)
		for (j = 0; j < n * n; j++)
			A[i][j] = 0;

	for (i = 0; i < n * n; i++)
		A[i][i] = 4;

	j = n;
	for (i = 0; i < n * n - n; i++, j++) {
		A[i][j] = -1;
		A[j][i] = -1;
	}

	j = 1;
	for (i = 0; i < n * n - 1; i++, j++) {
		if (j % n != 0) {
			A[i][j] = -1;
			A[j][i] = -1;
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

			if (y == h) {
			 	f[i * n + j] += 1 / pow(h, 2) * y * sin(y);
			}

			if (x == n * h) {
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
			printf("%2.2f   ", A[i][j]);
		}
		printf("\n\n");
	}
}

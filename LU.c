#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "LU.h"
#include "testcase.h"

void LUSequential(int n,  double A[n][n], double f[n], double u[n])
{
	double sum;

	// Factorization step
	for (int c = 0; c < n - 1; c++) {
		for (int r = c + 1; r < n; r++) {
			A[r][c] = A[r][c] / A[c][c];

			for (int cc = c + 1; cc < n; cc++) {
				A[r][cc] = A[r][cc] - A[r][c] * A[c][cc];
			}
		}
	}
	
	// Forward substitution step
	for (int r = 0; r < n; r++)	{
		sum = 0;

		for (int c = 0; c < r; c++)
			sum += A[r][c] * u[c];

		u[r] = f[r] - sum;
	}

	// Backward substitution step
	for (int r = n - 1; r >= 0; r--) {
		sum = 0;

		for (int c = r + 1; c < n; c++)
			sum += A[r][c] * u[c];

		u[r] = (u[r] - sum) / A[r][r];
	}		
}

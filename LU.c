#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LU.h"

void luDecom(int n,  double A[][n], double f[n], double u[n]) {
	double L[n][n];
	double y[n];
	double sum;

	//Factorization step
	for (int k = 0; k < n - 1; k++) {
		if(A[k][k] == 0) {
			return;
		} else {
			for (int i = k + 1; k < n; k++) {
				L[i][k] = A[i][k]/A[k][k];
				A[i][k] = L[i][k];
				for (int j = k + 1; j < n; j++) {
					A[i][j] = A[i][j] - L[i][k] * A[k][j];
				}
			}
		}
	}
	
	//Forward substitution step
	y[1] = f[1] / L[1][1];
	for (int i = 1; i < n; i++)	{
		sum = 0;
		for(int j = 0; j <= i - 1; j++)
			sum += L[i][j] * f[j];
		y[i] = (f[i] - sum) / L[i][i];
	}

	//Bacward substitution step
	u[n - 1] = y[n - 1] / A[n - 1][n -  1];
	for (int i = n - 2; i >= 0; i--) {
		sum = 0;
		for (int j = i + 1; j < n; j++) {
			sum += L[i][j]*y[j];
		}
		u[i] = (y[i] - sum) / A[i][i];
	}
	
}
/*
int main(int argc, char const *argv[])
{
	int A[][2] = {{1,0}, {0,1}};
	int f[] = {1,1};
	int size = 2;
	int res[size];
	luDecom(size,A,f,res);
	return 0;
}
*/




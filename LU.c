#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LU.h"
#include "testcase.h"
/*
void luDecom(int n,  double A[][n], double f[n], double u[n]) {
	double L[n][n];
	double y[n];
	double sum;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			L[i][j] = 0;
		}
	}
	//Factorization step
	for (int k = 0; k < n - 1; k++) {
		for (int i = k + 1; i < n; i++) {
			if(A[k][k] != 0) {
				L[i][k] = A[i][k]/A[k][k];
			} else {
				L[i][k] = 0;
			}
			printf("L[%d][%d]=%f\n",i,k,L[i][k]);
			A[i][k] = L[i][k];
			for (int j = k + 1; j < n; j++) {
				A[i][j] = A[i][j] - L[i][k] * A[k][j];
			}
		}
	}
	printf("L=\n");
	printMatrix(n, L);
	printf("U=\n");
	printMatrix(n,A);
	
	//Forward substitution step
	y[1] = f[1] / L[1][1];
	for (int i = 1; i < n; i++)	{
		sum = 0;
		for(int j = 0; j <= i - 1; j++)
			sum += L[i][j] * f[j]; //Should be result
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
*/


void luDecom(int n,  double A[][n], double f[n], double u[n]) {
	double sum;

	//Factorization step
	for (int k = 0; k < n - 1; k++) {
		for (int i = k + 1; i < n; i++) {
			A[i][k] = A[i][k]/A[k][k];
			for (int j = k + 1; j < n; j++) {
				A[i][j] = A[i][j] - A[i][k] * A[k][j];
			}
		}
	}
	
	//Forward substitution step
	u[1] = f[1];
	for (int i = 1; i < n; i++)	{
		sum = 0;
		for(int j = 0; j <= i - 1; j++)
			sum += A[i][j] * u[j];
		u[i] = f[i] - sum;
	}

	//Bacward substitution step
	u[n - 1] = u[n - 1] / A[n - 1][n -  1];
	for (int i = n - 2; i >= 0; i--) {
		sum = 0;
		for (int j = i + 1; j < n; j++) {
			sum += A[i][j]*u[j];
		}
		u[i] = (u[i] - sum) / A[i][i];
	}		
}

/*
int main(int argc, char const *argv[])
{
	double A[3][3] = {{2,2,7}, {8,7,8}, {2,4,6}};
	double f[] = {1,1};
	int size = 3;
	double res[size];

	printf("A=\n");
	printMatrix(size,A);

	luDecom(size,A,f,res);

	return 0;
}
*/



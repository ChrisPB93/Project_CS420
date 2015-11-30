#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CG.h"
#include "testcase.h"


void conjGrad(int n,  double A[][n], double f[n], double x[n]) {
	int k = 0;
	double tolerance = 1e-4;
	int maxIterations = 1000;
	double r[n] = f;
	double rPrev[n];
	double p[n];
	double s[n]; 
	double alpha, beta;


	while(dotProduct(n,r,r) > tolerance && k < maxIterations) {
		k++;
		if(k == 1) {
			p = r;
		} else {
			beta = dotProduct(n, r, r) / dotProduct(n, rPrev, rPrev);
			vectorAdd(n, beta, r, p, p);
		}
		matrixVectorMult(n, A, p, s);
		alpha = dotProduct(n, r, r) / dotProduct(n, p, s);
		vectorAdd(n, alpha, x, p, x);	
		rPrev = r;
		vectorAdd(n, -alpha, r, s, r);
	}
}

double dotProduct(int n,int a[n], int b[n]) {
	double res = 0;
	for(int i = 0; i < n; i++) {
		res += a[i] * b[i];
	}
	return res;
}

// Functions

void matrixVectorMult(int n, double M[n][n], double V[n], double R[n])
{
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			R[i] += M[i][j] * V[i];
		}
	}
}

void vectorAdd(int n, double S, double V1[n], double V2[n], double R[n])
{
	int i;

	for (i = 0; i < n; i++)
	{
		R[i] = V1[i] + S * V2[i];
	}
}

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}


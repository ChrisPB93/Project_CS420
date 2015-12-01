#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "CG.h"
#include "testcase.h"


void conjGrad(int n,  double A[][n], double f[n], double x[n], int maxIterations, double tolerance) {
	int k;
	double *r;
	double *s;
	double *p;
	double *rPrev;
	double alpha, beta;

	int nbytes = n*sizeof(double);

	s = (double *)malloc(nbytes);
	r = (double *)malloc(nbytes);
	rPrev = (double *)malloc(nbytes);
	p = (double *)malloc(nbytes);

	k = 0;
	memset(x,0,nbytes);
	memcpy(r,f,nbytes);
	memcpy(s,f,nbytes);
	


	while(dotProduct(n,r,r) > tolerance && k < maxIterations) {
		k++;
		printf("k=%d\n", k);
		if(k == 1) {
			memcpy(p,r,nbytes);
		} else {
			beta = dotProduct(n, r, r) / dotProduct(n, rPrev, rPrev);
			vectorAdd(n, beta, r, p, p);
		}
		memcpy(rPrev, r, nbytes);
		memset(s,0, nbytes);
		matrixVectorMult(n, A, p, s);
		alpha = dotProduct(n, r, r) / dotProduct(n, p, s);
		vectorAdd(n, alpha, x, p, x);	
		vectorAdd(n, -alpha, r, s, r);
	}

	free(r);
	free(s);
	free(p);
	free(rPrev);
}

double dotProduct(int n,double* a, double* b) {
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
			R[i] += M[i][j] * V[j];
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


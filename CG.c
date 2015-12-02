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
	double alpha, beta;
	double rDot, rPrevDot;

	int nbytes = n*sizeof(double);

	s = (double *)malloc(nbytes);
	r = (double *)malloc(nbytes);
	p = (double *)malloc(nbytes);

	k = 0;
	memset(x,0,nbytes);
	memcpy(r,f,nbytes);
	memcpy(s,f,nbytes);
	
	//DOTPRODUCT ONLY CALCULATED ONCE!!!!
	rDot = dotProduct(n,r,r);
	while(rDot > tolerance && k < maxIterations) {
		k++;
		if(k == 1) {
			memcpy(p,r,nbytes);
		} else {
			beta = rDot / rPrevDot; //reuse from last iteration
			vectorAdd(n, beta, r, p, p);
		}
		rPrevDot = rDot;
		memset(s,0, nbytes);
		matrixVectorMult(n, A, p, s);
		alpha = rDot / dotProduct(n, p, s); //dotp
		vectorAdd(n, alpha, x, p, x);	
		vectorAdd(n, -alpha, r, s, r);
		rDot = dotProduct(n,r,r);
	}

	free(r);
	free(s);
	free(p);
}

// Functions
double dotProduct(int n,double* a, double* b) {
	double res = 0;
	for(int i = 0; i < n; i++) {
		res += a[i] * b[i];
	}
	return res;
}

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


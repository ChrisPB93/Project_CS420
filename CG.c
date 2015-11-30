#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CG.h"
#include "testcase.h"


void luDecom(int n,  double A[][n], double f[n], double x[n]) {
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
			p = r + beta * p;
		}
		s = A . p;
		alpha = dotProduct(n, r, r) / dotProduct(n, p, s);
		x = x + alpha * p;

		rPrev = r;
		r = r - alpha * s;
	}
}

double dotProduct(int n,int a[n], int b[n]) {
	double res = 0;
	for(int i = 0; i < n; i++) {
		res += a[i] * b[i];
	}
	return res;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "CG.h"
#include "testcase.h"


void conjGrad(int n,  double A[][n], double f[n], double x[n], int maxIterations, double tolerance) {
	int k, n_local;
	double *r;
	double *s;
	double *p;
	double *x_local;
	double A_local[][n];
	double alpha, beta;
	double rDot, rDot_local, psDot, psDot_local, rPrevDot;
	int nbytes;
	int recvcount;

	MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  n_local = n/procs;

	nbytes = n_local*sizeof(double);

	s = (double *)malloc(nbytes);
	r = (double *)malloc(nbytes);
	p = (double *)malloc(nbytes);

	k = 0;
	memset(x_local,0,nbytes);
	MPI_Scatter(&f, n_local, MPI_DOUBLE, &r, n_local, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	//memcpy(r,f,nbytes);
	//memcpy(s,r,nbytes); CHECK THIS!?!?
	
	rDot_local = dotProduct(n,r,r);
	MPI_Allreduce(&rDot_local, &rDot, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
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
		matrixVectorMult(n, A, p, s); //REWRITE!!!!
		psDot_local = dotProduct(n, p, s);
		MPI_Allreduce(&psDot_local, &psDot, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
		alpha = rDot / psDdot; //dotp
		vectorAdd(n, alpha, x_local, p, x_local);	
		vectorAdd(n, -alpha, r, s, r);
		rDot_local = dotProduct(n,r,r);
		MPI_Allreduce(&rDot_local, &rDot, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	}
	MPI_Allgatherv(&x_local, n_local, MPI_DOUBLE, &x, &recvcount, MPI_DOUBLE, MPI_COMM_WORLD);
	//gatherv to get vector

	free(r);
	free(s);
	free(p);
	MPI_Finalize();
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


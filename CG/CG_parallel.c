#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <mpi.h>
#include <sys/time.h>
#include <omp.h>
#include "CG_parallel.h"
#include "test.h"

struct timeval tv;
double get_clock() {
   struct timeval tv; int ok;
   ok = gettimeofday(&tv, (void *) 0);
   if (ok<0) { printf("gettimeofday error");  }
   return (tv.tv_sec * 1.0 + tv.tv_usec * 1.0E-6);
}

void conjGrad(int n,  double A[][n], double f[n], double x[n], int maxIterations, double tolerance, int numThreads, int argc, char **argv) {
	int k, m, procs, rank;
	double *r;
	double *s;
	double *p;
	double *p_gather;
	double *x_local;
	double alpha, beta;
	double rDot, rDot_local, psDot, psDot_local, rPrevDot, tstart, tend, ttotal;
	int mbytes, provided;

	omp_set_num_threads(numThreads);
	MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
  MPI_Comm_size(MPI_COMM_WORLD, &procs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  m = n/procs;

	mbytes = m*sizeof(double);
	double A_local[m][n];

	s = (double *)malloc(mbytes);
	r = (double *)malloc(mbytes);
	p = (double *)malloc(mbytes);
	x_local = (double *)malloc(mbytes);
	p_gather = (double *)malloc(n*sizeof(double));
	k = 0;
	memset(x_local,0,mbytes);
	MPI_Scatter(f, m, MPI_DOUBLE, r, m, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Scatter(A, n*m, MPI_DOUBLE, A_local, n*m, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	tstart = get_clock();
	rDot_local = dotProduct(m,r,r);
	MPI_Allreduce(&rDot_local, &rDot, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	while(rDot > tolerance && k < maxIterations) {
		k++;
		if(k == 1) {
			memcpy(p,r,mbytes);
		} else {
			beta = rDot / rPrevDot; //reuse from last iteration
			vectorAdd(m, beta, r, p, p);
		}
		rPrevDot = rDot;
		memset(s,0, mbytes);
		MPI_Allgather(p, m, MPI_DOUBLE, p_gather, m, MPI_DOUBLE, MPI_COMM_WORLD);
		matrixVectorMult(m, n, A_local, p_gather, s);
		psDot_local = dotProduct(m, p, s);
		MPI_Allreduce(&psDot_local, &psDot, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
		alpha = rDot / psDot;
		vectorAdd(m, alpha, x_local, p, x_local);	
		vectorAdd(m, -alpha, r, s, r);
		rDot_local = dotProduct(m,r,r);
		MPI_Allreduce(&rDot_local, &rDot, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	}
	MPI_Allgather(x_local, m, MPI_DOUBLE, x, m, MPI_DOUBLE, MPI_COMM_WORLD);
	tend = get_clock();
	ttotal = tend-tstart;

	if(rank == 0) {
		printf("Time spent: %12.8lf\n",ttotal);
	}
	free(r);
	free(s);
	free(p);
	free(x_local);
	free(p_gather);
	MPI_Finalize();
}

// Functions
double dotProduct(int n,double* a, double* b) {
	int i;
	double res = 0;
	#pragma omp parallel for reduction(+:res)
	for(i = 0; i < n; i++) {
		res += a[i] * b[i];
	}
	return res;	
}

void matrixVectorMult(int m, int n, double M[m][n], double V[n], double R[n])
{
	int i, j;
	#pragma omp parallel for private(j)
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			R[i] += M[i][j] * V[j];
		}
	}
}

void vectorAdd(int n, double S, double V1[n], double V2[n], double R[n])
{
	int i;

	#pragma omp parallel for
	for (i = 0; i < n; i++)
	{
		R[i] = V1[i] + S * V2[i];
	}
}


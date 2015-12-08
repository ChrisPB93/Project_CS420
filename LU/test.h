#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

double forcingTerm(double x, double y);
double exactSltn(double x, double y);
int checkSolution(int n, double *x, double (*X)[n], double (*Y)[n]);
double computeError(int n, double *u, double (*X)[n], double (*Y)[n]);
void printExactSolution(int n, double (*X)[n], double (*Y)[n]);
void createXAndY(int n, double h, double (*X)[n], double (*Y)[n]);
void createMatrix(int n, double h, double (*A)[n]);
void createRHS(int n, double h, double *f, double (*X)[n], double (*Y)[n]);
void printMatrix(int n, double (*M)[n]);
void printVector(int n, double *V);

#endif

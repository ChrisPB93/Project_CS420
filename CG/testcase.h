#ifndef TESTCASE_H_INCLUDED
#define TESTCASE_H_INCLUDED

double forcingTerm(double x, double y);
double exactSltn(double x, double y);
void createXAndY(int n, double h, double (*X)[n], double (*Y)[n]);
void createMatrix(int n, double h, double (*A)[n]);
void createRHS(int n, double h, double *f, double (*X)[n], double (*Y)[n]);
void printMatrix(int n, double (*A)[n]);
void printVector(int n, double *V);

#endif
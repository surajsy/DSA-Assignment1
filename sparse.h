#define RANDMAX 1000
#define NROW_MAX 150
#define NCOL_MAX 100
#define NMAX NROW_MAX*NCOL_MAX
#define ALPHA1 73
#define BETA1 599
#define ALPHA2 71
#define BETA2 617

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

/*typedef struct
{
    int value[NROW_MAX*NCOL_MAX];
    int row[NROW_MAX*NCOL_MAX];
    int col[NROW_MAX*NCOL_MAX];
}sparseMat,COO,CSR,CSC;*/

//randSparseMat.c
void randSparseMat(int nRow, int nCol, int* nNonZero, int nNegative, int cooMat[][3]);

//printSparseMat.c
void printSparseMat(int nRow, int nCol,int nNZ, int mat[][3],char* matType);

void printCooMat(int nRow,int nCol, int mat[][3]);

void printCsr(int nRow,int nCol,int mat[][3]);

void printCsc(int nRow,int nCol,int mat[][3]);

void printCoo(int nRow,int nCol,int nNZ,int mat[][3]);

//transform.c
void sortSparse(int cooMat[][3], int nNonZero, char* dim);

void cooToCsr(int cooMat[][3],int csrMat[][3],int nNonZero,int nRow);

void cooToCsc(int cooMat[][3],int cscMat[][3], int nNonZero,int nCol);

void cscToCoo(int cscMat[][3], int cooMat[][3], int nCol);

void csrToCoo(int csrMat[][3],int cooMat[][3], int nRow);

//mulSparseMat.c
int mulSparseMat(int A[][3],int nRowA,int nColA,int B[][3],int nRowB,int nColB,int C[][3]);

void transpose(int nNonZero,int A[][3],int At[][3]);

int sparseRowOp(int A[][3],int nRow,int nCol,int r1,int k1,int r2,int k2,int rA[][3]);




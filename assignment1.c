#include<stdio.h>
//#include<conio.h>
#include "sparse.h"

void main(){

    int i,k,key;
    int nRow,nCol,nRow2,nCol2;
    int cooMatrix[NMAX][3],cooMatrix2[NMAX][3];
    int csrMatrix[NMAX][3],csrMatrix2[NMAX][3];
    int cscMatrix[NMAX][3],cscMatrix2[NMAX][3];
	int product[NMAX][3];
	int mat[NMAX][3];
    float pNonZero, pNegative;
    int nNonZero,nNegative,nNonZero2,nNZ;
	int r1,r2,k1,k2;

    while(1){
		printf("Input matrix parameters for random generation: R C pNZ pNeg\n");
		scanf("%d %d %f %f",&nRow,&nCol,&pNonZero,&pNegative);
        if(nRow<=0||nCol<=0||pNonZero<0||pNegative<0){
            printf("Invalid input. Try again...\n");
            continue;
        }
        else break;
    }

    nNonZero = (int)nRow*nCol*pNonZero/100;
    nNegative = (int)nRow*nCol*pNegative/100;
	
	

    randSparseMat(nRow,nCol,&nNonZero,nNegative,cooMatrix);
	printSparseMat(nRow,nCol,nNonZero,cooMatrix,"coo");
//	printCoo(nRow,nCol,nNonZero,cooMatrix);
	printf("\n");
//	k = getc(stdin);
	while(1){
		printf("Input matrix dimensions and no. of non zeros:R C nNZ\n");
		scanf("%d %d %d",&nRow,&nCol,&nNonZero);
		
		printf("Input matrix in COO form\n");
		for(i=0;i<nNonZero;i++){
			scanf("%d",&cooMatrix[i][0]);
		}
		for(i=0;i<nNonZero;i++){
			scanf("%d",&cooMatrix[i][1]);
			if(cooMatrix[i][1]>nRow) {
				printf("invalid row input at %d\n",i);
				return;
			}
		}
		for(i=0;i<nNonZero;i++){
			scanf("%d",&cooMatrix[i][2]);
			if(cooMatrix[i][2]>nCol) {
				printf("invalid col input at %d\n",i);
				return;
			}
		}
		
		printf("Matrix form:\n");
		printSparseMat(nRow,nCol,nNonZero,cooMatrix,"coo");
		printf("\n");
		
		printf("CSC form:\n");
		cooToCsc(cooMatrix,cscMatrix,nNonZero,nCol);
	//	printSparseMat(nRow,nCol,cscMatrix,"csc");
		printCsc(nRow,nCol,cscMatrix);
		printf("\n");
		
		printf("CSR form:\n");
		cooToCsr(cooMatrix,csrMatrix,nNonZero,nRow);
	//	printSparseMat(nRow,nCol,csrMatrix,"csr");
		printCsr(nRow,nCol,csrMatrix);
		printf("\n");
	//	k = getc(stdin);
		
		printf("Tnput weights and row indices for row operation:r1 k1 r2 k2\n");
		scanf("%d %d %d %d",&r1,&k1,&r2,&k2);
		
		printf("Output of row operation\n");
		nNZ = sparseRowOp(cscMatrix,nRow,nCol,r1,k1,r2,k2,mat);
		printCsc(nRow,nCol,mat);
		printf("\n");
		printSparseMat(nRow,nCol,nNZ,mat,"csc");
		
	//	k = getc(stdin);
		printf("Input matrix dimensions and no. of non zeros:R C nNZ\n");
		scanf("%d %d %d",&nRow2,&nCol2,&nNonZero2);
		
		printf("Input matrix in COO form\n");
		for(i=0;i<nNonZero2;i++){
			scanf("%d",&cooMatrix2[i][0]);
		}
		for(i=0;i<nNonZero2;i++){
			scanf("%d",&cooMatrix2[i][1]);
			if(cooMatrix2[i][1]>nRow2) {
				printf("invalid row input at %d\n",i);
				return;
			}
		}
		for(i=0;i<nNonZero2;i++){
			scanf("%d",&cooMatrix2[i][2]);
			if(cooMatrix2[i][2]>nCol2) {
				printf("invalid col input at %d\n",i);
				return;
			}
		}
		
		printf("Matrix form:\n");
		printSparseMat(nRow2,nCol2,nNonZero2,cooMatrix2,"coo");
		printf("\n");
		
		printf("CSC form:\n");
		cooToCsc(cooMatrix2,cscMatrix2,nNonZero2,nCol2);
	//	printSparseMat(nRow,nCol,cscMatrix,"csc");
		printCsc(nRow2,nCol2,cscMatrix2);
		printf("\n");
		
		printf("CSR form:\n");
		cooToCsr(cooMatrix2,csrMatrix2,nNonZero2,nRow2);
	//	printSparseMat(nRow,nCol,csrMatrix,"csr");
		printCsr(nRow2,nCol2,csrMatrix2);
		printf("\n");
		
	//	k = getc(stdin);
		printf("A=\n");
		printSparseMat(nRow,nCol,nNonZero,cooMatrix,"coo");
		printf("\n");
		printf("B=\n");
		printSparseMat(nRow2,nCol2,nNonZero2,cooMatrix2,"coo");
		printf("\n");
		
		nNZ = mulSparseMat(csrMatrix,nRow,nCol,cscMatrix2,nRow2,nCol2,product);
		printf("product AB=\n");
	//	printCoo(nRow,nCol2,nNZ,product);
		printSparseMat(nRow,nCol2,nNZ,product,"coo");
		printf("\n");
		
		printf("Do you wish to continue? Press 1 if yes, 0 to exit\n");
		scanf("%d",&key);
		if(key!=1) break;
	}
}


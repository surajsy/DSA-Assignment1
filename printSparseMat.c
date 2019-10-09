#include<stdio.h>
#include "sparse.h"

//int* tempPtr;

void printSparseMat(int nRow, int nCol, int nNZ, int mat[][3],char* matType){
    int i,j;
    int index,ptr;
    int nNonZero;
	int temp[NMAX][3];
	

    if(nRow>20||nCol>20){
        printf("Dimensions too large... Returning\n");
        return;
    }
	
	
    if(strcmp(matType,"coo")==0){
		sortSparse(mat,nNZ,"row");
        printCooMat(nRow,nCol,mat);
    }

    else if(strcmp(matType,"csr")==0){
		csrToCoo(mat,temp,nRow);
		printCooMat(nRow,nCol,temp);		
    }

    else if(strcmp(matType,"csc")==0){
		cscToCoo(mat,temp,nCol);
//		printCoo(nRow,nCol,mat[nCol][2]-1,temp);
		printCooMat(nRow,nCol,temp);
	}
}

void printCooMat(int nRow,int nCol, int mat[][3]){
	int index = 0;
	int i,j;
    for(i=0;i<nRow;i++){
		for(j=0;j<nCol;j++){
			if(mat[index][2]==j+1 && mat[index][1]==i+1){
				printf("%d ",mat[index][0]);
				index++;
			}
            else printf("0 ");
		}
		printf("\n");
	}
}

void printCoo(int nRow,int nCol,int nNZ,int mat[][3]){
	int i;
	for(i=0;i<nNZ;i++){
		printf("%d ",mat[i][0]);
	}
	printf("\n");
	for(i=0;i<nNZ;i++){
		printf("%d ",mat[i][1]);
	}
	printf("\n");
	for(i=0;i<nNZ;i++){
		printf("%d ",mat[i][2]);
	}
	printf("\n");	
}

void printCsr(int nRow,int nCol,int mat[][3]){
	int i,nNZ;
	nNZ = mat[nRow][1]-1;
	for(i=0;i<nNZ;i++){
		printf("%d ",mat[i][0]);
	}
	printf("\n");
	for(i=0;i<nRow+1;i++){
		printf("%d ",mat[i][1]);
	}
	printf("\n");
	for(i=0;i<nNZ;i++){
		printf("%d ",mat[i][2]);
	}
	printf("\n");	
}

void printCsc(int nRow,int nCol,int mat[][3]){
	int i,nNZ;
	nNZ = mat[nCol][2]-1;
	for(i=0;i<nNZ;i++){
		printf("%d ",mat[i][0]);
	}
	printf("\n");
	for(i=0;i<nNZ;i++){
		printf("%d ",mat[i][1]);
	}
	printf("\n");
	for(i=0;i<nCol+1;i++){
		printf("%d ",mat[i][2]);
	}
	printf("\n");	
}
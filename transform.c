#include "sparse.h"
#include<string.h>

void sortSparse(int cooMat[][3], int nNonZero, char* dim){
    int i,j;
    int temp;

if(strcmp(dim,"row")==0){
    for(i=0;i<nNonZero;i++)
		for(j=1;j<nNonZero;j++){
			if(cooMat[j][1]<cooMat[j-1][1]){
				temp = cooMat[j][0];
				cooMat[j][0] = cooMat[j-1][0];
				cooMat[j-1][0] = temp;
				temp = cooMat[j][1];
				cooMat[j][1] = cooMat[j-1][1];
				cooMat[j-1][1] = temp;
				temp = cooMat[j][2];
				cooMat[j][2] = cooMat[j-1][2];
				cooMat[j-1][2] = temp;
			}	
		}
	}

else if(strcmp(dim,"col")==0){
    for(i=0;i<nNonZero;i++)
		for(j=1;j<nNonZero;j++){
			if(cooMat[j][2]<cooMat[j-1][2]){
				temp = cooMat[j][0];
				cooMat[j][0] = cooMat[j-1][0];
				cooMat[j-1][0] = temp;
				temp = cooMat[j][1];
				cooMat[j][1] = cooMat[j-1][1];
				cooMat[j-1][1] = temp;
				temp = cooMat[j][2];
				cooMat[j][2] = cooMat[j-1][2];
				cooMat[j-1][2] = temp;
			}	
		}
	}
}

void cooToCsr(int cooMat[][3],int csrMat[][3], int nNonZero,int nRow){
    int ptr,nzCount,index;
    int i,j;
    
    sortSparse(cooMat,nNonZero,"row");

	nzCount = 0;

	for(i=0;i<nNonZero;i++){
		csrMat[i][0] = cooMat[i][0];
		csrMat[i][2] = cooMat[i][2];
	}
//		for(i=0;i<nRow+1;i++)
//		printf("%d %d %d\n",csrMat[i][0],csrMat[i][1],csrMat[i][2]);
//		printf("\n");
	
	csrMat[0][1] = 1;
    for(i=1;i<nRow+1;i++){
		for(j=0;j<nNonZero;j++){
			if(cooMat[j][1]==i)
				nzCount++;
		}
		csrMat[i][1]=csrMat[i-1][1]+nzCount;
		nzCount=0;
	}
	
//		for(i=0;i<nRow+1;i++)
//		printf("%d %d %d\n",csrMat[i][0],csrMat[i][1],csrMat[i][2]);
//		printf("\n");
}

void cooToCsc(int cooMat[][3],int cscMat[][3], int nNonZero,int nCol){
    int ptr,nzCount,index;
    int i,j;
    
    sortSparse(cooMat,nNonZero,"col");
	
	nzCount = 0;

	for(i=0;i<nNonZero;i++){
		cscMat[i][0] = cooMat[i][0];
		cscMat[i][1] = cooMat[i][1];
	}
	
	cscMat[0][2] = 1;
    for(i=1;i<nCol+1;i++){
		for(j=0;j<nNonZero;j++){
			if(cooMat[j][2]==i)
				nzCount++;
		}
		cscMat[i][2]=cscMat[i-1][2]+nzCount;
		nzCount=0;
	}
	
	sortSparse(cooMat,nNonZero,"row");
}

void cscToCoo(int cscMat[][3], int cooMat[][3], int nCol){
	int ptr = 1;
	int i,index=0;
	int nNonZero = cscMat[nCol][2]-1;
	
	for(i=0;i<nNonZero;i++){
		cooMat[i][0] = cscMat[i][0];
		cooMat[i][1] = cscMat[i][1];
	}
	for(ptr=0;ptr<nCol;ptr++){
		for(i=cscMat[ptr][2];i<cscMat[ptr+1][2];i++){
			cooMat[i-1][2] = index+1;
		}
		index++;
	}
	
	sortSparse(cooMat,nNonZero,"row");

}

void csrToCoo(int csrMat[][3],int cooMat[][3], int nRow){
	int ptr = 1;
	int i,index=0;
	int nNonZero = csrMat[nRow][1]-1;
	
	for(i=0;i<nNonZero;i++){
		cooMat[i][0] = csrMat[i][0];
		cooMat[i][2] = csrMat[i][2];
	}
	for(ptr=0;ptr<nRow;ptr++){
		for(i=csrMat[ptr][1];i<csrMat[ptr+1][1];i++){
			cooMat[i-1][1] = index+1;
		}
		index++;
	}
	
//	for(i=0;i<nNonZero;i++)
//		printf("%d %d %d\n",cooMat[i][0],cooMat[i][1],cooMat[i][2]);
//	printf("\n");

}

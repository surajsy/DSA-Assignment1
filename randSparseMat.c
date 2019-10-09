#include<stdio.h>
#include "sparse.h"

int sparseArray[NROW_MAX*NCOL_MAX];

void randSparseMat(int nRow, int nCol, int* nNonZero, int nNegative, int cooMat[][3]){
    int index;
    int i,count=0,nCount=nNegative;
    srand(time(0));
	index = rand()%7;

    for(i=0;i<*nNonZero;i++){
        index = (ALPHA1*index + BETA1*i)%(nRow*nCol);
        if(sparseArray[index]!=0){ 
			count++;
			continue;
		}
        else{
			if(nCount!=0){
				sparseArray[index] = -1*((ALPHA2*index+BETA2*i)%10 + 1);
				nCount--;
			}
			else sparseArray[index] = (ALPHA2*index+BETA2*i)%10 + 1;
		}
		
//		printf("index=%d\n",index);
//		printf("sparsearray[i]=%d\n",sparseArray[index]);
    }
	*nNonZero = *nNonZero - count;
    index = 0;
    for(i=0;i<nRow*nCol;i++){
        if(sparseArray[i]==0) continue;

        else{
            cooMat[index][0] = sparseArray[i];
            cooMat[index][1] = i/nCol + 1;
            cooMat[index][2] = i%nCol + 1;
            index++;
        }
    }
//	printCoo(nRow,nCol,*nNonZero,cooMat);
	sortSparse(cooMat,*nNonZero,"row");
}


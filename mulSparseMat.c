#include "sparse.h"

int mulSparseMat(int A[][3], int nRowA, int nColA, int B[][3], int nRowB, int nColB, int C[][3]){
//	int nNZA = A[nRowA+1][1]-1;
//	int nNZB = B[nColB+1][2]-1;
//	int tempA[NMAX][3];
//	int tempB[NMAX][3];
//	int tempBt[NMAX][3];
	int i,j,index;//,index2,index3;
	int cptr,rptr;
	
	if (nRowB!=nColA){ 
		printf("Invalid matrix dimensions...\n");
		return 0;
	}
//	csrToCoo(A,tempA,nRowA);
//	cscToCoo(B,tempB,nColB);
	
//	transpose(nNZB,tempB,tempBt);
	index=0;
//	index2=0;
//	index3=0;
	rptr = 0;
//	printf("%d %d %d %d\n",nRowA,nColA,nRowB,nColB);
	while(rptr<nRowA){
		cptr = 0;
		while(cptr<nColB){
			i=A[rptr][1];
			j=B[cptr][2];
//			printf("%d %d\n",i,j);
			while(i<A[rptr+1][1] && j<B[cptr+1][2]){
//				printf("%d %d\n",i,j);
				if(A[i-1][2]==B[j-1][1]){
					C[index][0]=C[index][0]+A[i-1][0]*B[j-1][0];
					C[index][1]=rptr+1;
					C[index][2]=cptr+1;
					i++;j++;
				}
				else 
					if(A[i-1][2]<B[j-1][1]) i++;
					else j++;
			}
//			printf("%d\n",C[index][0]);
			if(C[index][0]!=0) index++;
			cptr++;
		}
		rptr++;
	}
//	printf("%d\n",index);
//	for(i=0;i<index;i++)
//		printf("%d %d %d\n",C[i][0],C[i][1],C[i][2]);
//	printf("\n");
//	sortSparse(C,index,"row");
	return index;
}

void transpose(int nNonZero,int A[][3],int At[][3]){
	int i;
	
	for(i=0;i<nNonZero;i++){
		At[i][0]=A[i][0];
		At[i][1]=A[i][2];
		At[i][2]=A[i][1];
	}
	sortSparse(At,nNonZero,"row");
}

int sparseRowOp(int A[][3],int nRow,int nCol,int r1,int k1,int r2,int k2,int rAcsc[][3]){
	int i,j,index1,count,index,index3;
	int nNZ,nR1,nR2,rptr;
	int temp1[NMAX][3],temp2[NMAX][3],rA[NMAX][3];
	
	nNZ = A[nCol][2]-1;
	count=0;
	index3=0;
	rptr=0;
	i=0;
	cscToCoo(A,temp1,nCol);
	cooToCsr(temp1,temp2,nNZ,nRow);
	nR1 = temp2[r1][1]-temp2[r1-1][1];
	nR2 = temp2[r2][1]-temp2[r2-1][1];
	
//	printCsr(nRow,nCol,temp2);
//	printf("\n");
//	printCoo(nRow,nCol,nNZ,temp1);
//	printf("\n");
		
	if(nR1==0 && nR2==0){
		for(i=0;i<nNZ;i++){
			rA[i][0]=temp1[i][0];
			rA[i][1]=temp1[i][1];
			rA[i][2]=temp1[i][2];
		}
	}
	
	else if(nR2==0){
		index=0;
		for(i=0;i<nNZ;i++){
			if(temp1[i][1]==r1) rA[index][0]=k1*temp1[i][0];
			else rA[index][0]=temp1[i][0];
			if(rA[index][0]!=0){
				rA[index][1]=temp1[i][1];
				rA[index][2]=temp1[i][2];
				index++;
			}
		}
		nNZ = index;
	}
	else if(nR1==0){
		for(i=0;i<nNZ;i++){
			if(temp1[i][1]>r1) break;
			rA[i][0]=temp1[i][0];
			rA[i][1]=temp1[i][1];
			rA[i][2]=temp1[i][2];
		}
		index = i;
		j = temp2[r2-1][1]-1;
		while(j<temp2[r2][1]-1){
			if(k2==0) break;
			rA[index][0]=k2*temp1[j][0];
			rA[index][1]=r1;
			rA[index][2]=temp1[j][2];
			index++;j++;
		}
		for(;i<nNZ;i++){
			rA[index][0]=temp1[i][0];
			rA[index][1]=temp1[i][1];
			rA[index][2]=temp1[i][2];
			index++;
		}
		nNZ = index;
	}
	else{
		index3=0;
		for(i=0;i<nNZ;i++){
			if(temp1[i][1]==r1) break;
			rA[index3][0]=temp1[i][0];
			rA[index3][1]=temp1[i][1];
			rA[index3][2]=temp1[i][2];
			index3++;
		}

		index=i;
		j = temp2[r2-1][1]-1;
		while(index<temp2[r1][1]-1 && j<temp2[r2][1]-1){
			if(k1==0 || k2==0) break;
			
			if(temp1[index][2]==temp1[j][2]) {
				rA[index3][0]=k1*temp1[index][0]+k2*temp1[j][0];
				if(rA[index3][0]!=0){
					rA[index3][1]=r1;
					rA[index3][2]=temp1[index][2];
					index3++;
				}
				index++;j++;
				//printf("%d\n",index3);
			}
			else if(temp1[index][2]<temp1[j][2]){
				rA[index3][0]=k1*temp1[index][0];
				rA[index3][1]=r1;
				rA[index3][2]=temp1[index][2];
				index++;index3++;
			}
			else{
				rA[index3][0]=k2*temp1[j][0];
				rA[index3][1]=r1;
				rA[index3][2]=temp1[j][2];
				j++;index3++;
			}
		}
		
		while(index<temp2[r1][1]-1){
			if(k1==0) break;
			rA[index3][0]=k1*temp1[index][0];
			rA[index3][1]=r1;
			rA[index3][2]=temp1[index][2];
			index++;index3++;
		}
		
		while(j<temp2[r2][1]-1){
			if(k2==0) break;
			rA[index3][0]=k2*temp1[j][0];
			rA[index3][1]=r1;
			rA[index3][2]=temp1[j][2];
			j++;index3++;
		}
		
		for(;i+nR1<nNZ;i++){
			rA[index3][0]=temp1[i+nR1][0];
			rA[index3][1]=temp1[i+nR1][1];
			rA[index3][2]=temp1[i+nR1][2];
			index3++;//printf("%d\n",index3);
		}
		nNZ = index3;
	}
//	printCoo(nRow,nCol,i+count-nR1,rA);
//	printf("\n");
	cooToCsc(rA,rAcsc,nNZ,nCol);
	return nNZ;
}
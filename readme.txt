ReadMe for Assigment1: Sparse Matrix representations(COO,CSR,CSC)

Source file			Functions defined	Description

assignment1.c		main				Driver function

randSparseMat.c		randSparseMat		Given the number of rows,cols,% of non zero elements generates a random matrix in COO representation

transform.c		sortSparse		Sorts a given COO form matrix w.r.t row/col as specified
			cooToCsr		Converts COO form to CSR form
			cooToCsc		Converts COO form to CSC form
			csrToCoo		Converts CSR form to COO form
			cscToCoo		Converts CSC form to COO form

mulSparseMat.c		mulSparseMat		Given 2 matrices, one in CSR form, another in CSC form, outputs the product in COO form
			transpose		Computes the transpose of the given COO matrix
			sparseRowOp		Given a matrix, 2 row indices and weights, it does the row operation

printSparseMat.c	printSparseMat		Prints any specified sparse representation in matrix form
			printCooMat		Prints COO sparse representation in matrix form
			printCoo		Prints COO representation of the matrix, given a COO matrix
			printCsr		Prints CSR representation of the matrix, given a CSR matrix
			printCsc		Prints CSC representation of the matrix, given a CSC matrix

Header: sparse.h

The sparse representations are stored in a 2D integer array of size NMAX*3. Here NMAX is defined as 150(row)*100(col)(max input size)
col 0 represents value
col 1 represents row index in COO form/ row ptr in CSR form
col 2 represents col index in COO form/ col ptr in CSC form 

Program flow:(Follow the prompts)

1) Input dimensions and % non zero elements for random matrix. Random matrix prints out.
(Note: Values in random matrix restricted to -10 to 10)

2) Input dimensions, no. of non zero elements, and values for 1st matrix. Matrix prints out in all 3 forms

3) Input row indices and weights for row operation. CSC matrix and matrix form prints out.

4) Input dimensions, no. of non zero elements, and values for 2nd matrix. Matrix prints out in all 3 forms

5) Multiplication of 1st and 2nd matrix is performed and product is printed out.


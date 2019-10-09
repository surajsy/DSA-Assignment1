sparse.out: assignment1.o randSparseMat.o printSparseMat.o transform.o mulSparseMat.o
	gcc assignment1.o randSparseMat.o printSparseMat.o transform.o mulSparseMat.o -o sparse.out

assignment1.o: assignment1.c sparse.h
	gcc -c assignment1.c sparse.h

randSparseMat.o: randSparseMat.c transform.c sparse.h
	gcc -c randSparseMat.c transform.c sparse.h

printSparseMat.o: printSparseMat.c transform.c sparse.h 
	gcc -c printSparseMat.c transform.c sparse.h

transform.o: transform.c sparse.h
	gcc -c transform.c sparse.h
	
mulSparseMat.o: mulSparseMat.c transform.c sparse.h
	gcc -c mulSparseMat.c transform.c sparse.h
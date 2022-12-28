compile:program run
program:lib ana
	gcc matrixLib.o main.o -o program
lib:
	gcc -c matrixLib.c -o matrixLib.o
ana:
	gcc -c main.c -o main.o
run:
	program.exe
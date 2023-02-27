/**
* @file matrixLib.h
* @description In this project, we are expected to read data from the file,
* make some statistical calculations using various functions
* on the read data set, and write these calculations to the file.
* @assignment MatrixFunctionsAndFileOperations
* @date 27.12.2022
* @author Beyza Yıldızlı beyzayildizli10@gmail.com
*/

#ifndef MATRIXLIB_h
# define MATRIXLIB_h

void fillVektor(float *, int, int);
void fillMatrix(float **, int, int, int);
float *returnVector(int);
float **returnMatrix(int, int);
void freeMatrix(float **, int);
float mean(float *, int);
float covariance(float *, float *, int);
float correlation(float *, float *, int);
float **matrixMultiplication(float **, float **, int, int, int, int);
float **matrixTranspose(float **, int row, int col);
float *rowMeans(float **, int, int);
float *columnMeans(float **, int, int);
float **covarianceMatrix(float **, int, int);
float determinant(float **, int);
void printVector(float *, int);
void printMatrix(float **, int, int);


#endif

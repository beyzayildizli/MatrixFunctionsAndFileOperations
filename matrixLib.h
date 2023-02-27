/**
* @file matrixLib.h
* @description Bu projede, Bu projede, dosyadan veri okumamız, okunan veri seti üzerinde 
* çeşitli fonksiyonları kullanarak bazı istatistiksel hesaplamaları
* yapmamız ve bu hesapları dosyaya yazmamız beklenmektedir.
* @assignment Proje2
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

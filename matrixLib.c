/**
* @file matrixLib.c
* @description In this project, we are expected to read data from the file,
* make some statistical calculations using various functions
* on the read data set, and write these calculations to the file.
* @assignment MatrixFunctionsAndFileOperations
* @date 27.12.2022
* @author Beyza Yıldızlı beyzayildizli10@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void fillVektor(float *vektor, int size, int num){
    srand(num);
    for(int i=0; i<size;i++){
        vektor[i]=1+(rand()%10);
    }
}

void fillMatrix(float **matris, int row, int col, int num){
    srand(num);
    for(int a=0; a<row;a++){
        for(int b=0; b<col;b++){
            matris[a][b]=1+(rand()%10);
        }   
    }
}


/*Parametre olarak vektörün boyutunu alıyor ve geriye
dinamik olarak oluşturduğu bir boyutlu vektörü döndürüyor.*/
float *returnVector(int size){
    float *dizi=(float*) malloc(sizeof(float)*size);
    return dizi;
}

/*Parametre olarak matrisin satir ve sütun değerlerini alıyor ve geriye
dinamik olarak oluşturulan 2 boyutlu bir matris döndürüyor.*/
float **returnMatrix(int row, int col){
    float **dizi=(float**) malloc(sizeof(float*)*row);
    for (int i=0; i<row; i++){
        dizi[i] = malloc(sizeof(float)*col);
    }
    
    return dizi;
}

/*Dinamik olarak oluşturulmuş 2 boyutlu matrisi ve sütun (row) değerini parametre olarak alıyor
ve heap’ten alınan bu alanı sisteme geri iade ediyor.*/
void freeMatrix(float **mat, int row){
    for(int a=0; a<row;a++){
        free(mat[a]);
    }
    free(mat);
}

/*Parametre olarak bir boyutlu bir vektör ve boyutunu alıyor, geriye bu vektörün ortalamasını
döndürüyor. Bunun için önce tüm elemanları toplam adlı değişkende topladım. Ardından
return yaparken bu sonucu eleman sayısına böldüm.*/
float mean(float *vec, int size){
    float toplam=0;
    for(int i=0; i<size; i++){
        toplam+=vec[i];
    }
    return toplam/size; //ortalama hesaplamak için eleman sayısına böldüm.
}

/*Parametre olarak 2 adet boyutları aynı bir boyutlu vektörü ve boyutlarını alıyor,
geriye bu iki vektörün kovaryansını döndürüyor*/
float covariance(float *vec1, float *vec2, int size){
    float xOrt=mean(vec1, size); //1. vektörün değerleri ortalaması
    float yOrt=mean(vec2, size); //2. vektörün değerleri ortalaması
    float covariance=0.0;
    //Her değeri bulunduğu vektörün ortalamasından çıkarıyoruz ve iki vektörün aynı indexteki değerlerini çarpıp covariance'a ekliyoruz. 
    for(int i=0; i<size; i++){
           covariance+=(vec1[i]-xOrt)*(vec2[i]-yOrt);
    }
    covariance/=(size-1);//covarience değerini bulmak için bulduğumuz sonucu eleman sayısının 1 eksiğine bölüyoruz.
    return covariance;
}

/*Parametre olarak 2 adet boyutları aynı bir boyutlu vektör ve boyutlarını alacak, geriye bu iki vektörün 
korelasyonunu döndürecek.*/
float correlation(float *vec, float *vec2, int size){
    float xOrt=mean(vec, size);
    float yOrt=mean(vec2, size);
    float toplamX, toplamY=0.0;
    for(int i=0; i<size; i++){
        toplamX+=(vec[i]-xOrt)*(vec[i]-xOrt);
        toplamY+=(vec2[i]-yOrt)*(vec2[i]-yOrt);
    }
    toplamX/=(size-1);
    toplamY/=(size-1);
    float corel=covariance(vec, vec2, size)/(sqrt(toplamX*toplamY));
    return corel;
}

/*Parametre olarak dinamik olarak oluşturulan iki adet 2 boyutlu matrisi ve boyut değerlerini (row, col) alacak,
geriye bu iki matrisin çarpımını geri döndürecektir. Fonksiyon matris çarpım kuralını kontrol etmelidir. Çarpım 
matrisi, fonksiyon içerisinde dinamik olarak oluşturulmalıdır.*/
float **matrixMultiplication(float **mat1, float **mat2, int row1, int col1, int row2, int col2){
    int multiRow=row1; //çarpımın satır sayısı ilk matrisin satır sayısına eşittir.
    int multiCol=col2; //çarpımın sütun sayısı 2. matrisin sütun sayısına eşittir.
    float **multiplication=returnMatrix(multiRow, multiCol);
    if(col1==row2){
        for(int a=0; a<multiRow;a++){
            for(int b=0; b<multiCol;b++){
                float toplam=0;
                for(int i=0; i<col1; i++){
                    toplam+=mat1[a][i]*mat2[i][b];
                }
                multiplication[a][b]=toplam;
            }    
        }
        return multiplication;
    }else{
        printf("Matris carpimi yapabilmek icin 1. matrisin sutun sayisi 2. matrisin satir sayisina esit olmalidir!");
        exit(1);
    }
}

/*Parametre olarak dinamik olarak oluşturulmuş 2 boyutlu matrisi ve boyutlarını alıyor, geriye bu matrisin 
transpozunu döndürüyor.*/
float **matrixTranspose(float **mat, int row, int col){
    //n*m lik bir matrisin transpozu m*n'lik olacağından yeni matrisimizi oluştururken satır ve sütun sayısını ters yazıyoruz
    float **matrixTranspose=returnMatrix(col, row);
    for(int a=0; a<row;a++){
        for(int b=0; b<col;b++){
            matrixTranspose[b][a]=mat[a][b];
        }   
    }
    return matrixTranspose;
}

/*Parametre olarak 2 boyutlu matrisi ve boyutlarını alıyor, bu matrisin satırlarının ortalamasını
tutan bir vektör döndürüyor.*/
float *rowMeans(float **mat, int row, int col){
    float *rowMeans=returnVector(row);
    for(int a=0; a<row;a++){
        rowMeans[a]=mean(mat[a], col);
    }
    return rowMeans;
}

/*Parametre olarak 2 boyutlu matrisi ve boyutlarını alıyor, bu matrisin sütunlarının ortalamasını
tutan bir vektör döndürüyor.*/
float *columnMeans(float **mat, int row, int col){
    float *columnMeans=returnVector(col);
    for(int a=0; a<col; a++){
        float toplam=0.0;
        for(int b=0; b<row;b++){
            toplam+=mat[b][a];
        }
        columnMeans[a]=(toplam/row);
    }
    return columnMeans;
}

/*Parametre olarak matrisi ve boyutlarını alacak, bu matrisin (sütun bazında) varyans kovaryans matrisini 
döndürüyor. */
float **covarianceMatrix(float **mat, int row, int col){
    float *colMeans = columnMeans(mat, row, col);
        float **mat2=returnMatrix(row, col);
        for(int a=0; a<row;a++){
            for(int b=0; b<col;b++){
                mat2[a][b]=(mat[a][b]-colMeans[b]);
            }   
        }
        float **transpose = matrixTranspose(mat2, row, col);

        float **mat3 = returnMatrix(col, col);
        mat3 = matrixMultiplication(transpose, mat2, col, row, row, col);

        float **mat4=returnMatrix(col, col);
        for(int a=0; a<col;a++){
            for(int b=0; b<col;b++){
                mat4[a][b]=mat3[a][b]/(float)row;
            }   
        }
        return mat4;
}

//Parametre olarak aldığı 2 boyutlu 3x3 boyutlu matrisin determinantını döndürecektir.
float determinant(float **mat, int row){
    if(row==3){
        //2 kere genişlet
    int col=row+2;
    for(int i=0; i<row;i++){
        mat[i]=realloc(mat[i], col*sizeof(float));  
    }

    //ilk 2 sütundaki değerleri son iki sütuna da yaz
    for(int a=0; a<row; a++){
        for(int b=3; b<col; b++){
            mat[a][b]=mat[a][b-3];
        }    
    }

    //artıları hesapla
    float *artilar=returnVector(3);
    for(int a=0; a<col-2; a++){
        float carpim = 1.0;
        int i=a;
        for(int b=0; b<row; b++){
            carpim*=mat[b][i];
            i++;
        }
        //printf("%f ", carpim);
        artilar[a] = carpim;
    }

    //eksileri hesapla
    float *eksiler=returnVector(3);
    for(int a=0; a<col-2; a++){
        float carpim = 1.0;
        int i=a;
        for(int b=row-1; b>-1; b--){
            carpim*=mat[b][i];
            i++;
        }
        eksiler[a] = carpim;
    }

    //determinant hesapla
    float det=0;
    for(int i=0; i<3; i++){
        det+=artilar[i];
        det-=eksiler[i];
    }
    //matrisi eski haline getir.
    col=row;
    for(int i=0; i<row;i++){
        mat[i]=realloc(mat[i], col*sizeof(float));  
    }
    return det;
    }else{
        printf("Bu fonksiyon sadece 3x3 matrislerde determinant vermektedir.");
        exit(1);
    }
}

//Parametre olarak aldığı bir boyutlu vektörü ekrana yazdırıyor
void printVector(float *vec, int N){
    for(int i=0; i<N;i++){
        printf("%.2f ",vec[i]);
    }
}

//Parametre olarak aldığı 2 boyutlu matrisi ekrana matris formunda yazdırıyor.
void printMatrix(float** mat, int row, int col){
    for(int a=0; a<row;a++){
        for(int b=0; b<col;b++){
            printf("%.2f ",mat[a][b]); 
        }   
        printf("\n"); 
    }
}


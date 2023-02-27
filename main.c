/**
* @file main.c
* @description In this project, we are expected to read data from the file,
* make some statistical calculations using various functions
* on the read data set, and write these calculations to the file.
* @assignment MatrixFunctionsAndFileOperations
* @date 27.12.2022
* @author Beyza Yıldızlı beyzayildizli10@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "matrixLib.h"

typedef enum{
    Irissetosa = 1,
    Irisversicolor,
    Irisvirginica
}IrisSpecies;

typedef struct{
    float sepalLengthCm;
    float sepalWidthCm;
    float petalLengthCm;
    float petalWidthCm;
    IrisSpecies species;
}IrisDataType;

float variance(int n, float * arr);
void ortalamaHesabi(FILE *, float**);
void varyansHesabi(FILE *, float**);
void korelasyonHesabi(FILE *, float**);
void covaryansHesabi(FILE *, float**);

void verileriDiziyeDoldurVeYazdir(IrisDataType *);
void dizidekiVerileriMatriseEkle(IrisDataType *, float **);
void yeniBirDosyayaOzellikYazdir(float **);

int main(){
    int size=150;
    IrisDataType *dizi=(IrisDataType*) malloc(sizeof(IrisDataType)*size);

    // csv dosyasını açıyoruz, dosyadaki verileri okuyoruz ve bir diziye ekliyoruz. Ardından dosyayı kapatıyoruz
    verileriDiziyeDoldurVeYazdir(dizi);

    // 150x4 matris olusturuyoruz
    float **ozellikMatrisi = returnMatrix(150, 4);

    //dizideki verileri matrise ekliyoruz
    dizidekiVerileriMatriseEkle(dizi, ozellikMatrisi);

    //özellik matrisini yazdırıyoruz
    printf("\n\nOzellik Matrisi:\n");
    printMatrix(ozellikMatrisi, 150, 4);

    //yeni bir dosya oluşturup belirli işlemlerin sonuçlarını yazdırıyoruz
    yeniBirDosyayaOzellikYazdir(ozellikMatrisi);

    return 0;
}

void verileriDiziyeDoldurVeYazdir(IrisDataType *dizi){
    //csv dosyasını açıyoruz
    FILE *fp = fopen("Iris.csv", "r");
    if (fp == NULL) {
        printf("Dosya açilamadi!\n");
    }
    // Dosyadaki verileri okuyoruz ve bir diziye ekliyoruz
    char line[100]; // satır için geçici bir dizi
    int i=-2;
    while (fgets(line, sizeof(line), fp)) {
        if(i<0){  //ilk 2 satırı atlıyoruz
            strtok(line, ",");
        }else{    // diğer satırlarıı virgüller kullanarak ayrıştırıyoruz
            char *veri;

            //id'yi atlıyoruz:
            veri = strtok(line, ",");

            veri = strtok(NULL, ",");
            dizi[i].sepalLengthCm = atof(veri);

            veri = strtok(NULL, ",");
            dizi[i].sepalWidthCm = atof(veri);

            veri = strtok(NULL, ",");
            dizi[i].petalLengthCm = atof(veri);

            veri = strtok(NULL, ",");
            dizi[i].petalWidthCm= atof(veri);

            veri = strtok(NULL, ",");
           
            if (strcmp(veri, "Iris-setosa\n") == 0) {
                dizi[i].species = Irissetosa;
            } else if (strcmp(veri, "Iris-versicolor\n") == 0) {
                dizi[i].species = Irisversicolor;
            } else if (strcmp(veri, "Iris-virginica\n") == 0) {
                dizi[i].species = Irisvirginica;
            } else{
                dizi[i].species = 0;
            }

            // Verileri yazdırıyoruz
           printf("%.1f, %.1f, %.1f, %.1f, %d\n", dizi[i].sepalLengthCm, dizi[i].sepalWidthCm, dizi[i].petalLengthCm, dizi[i].petalWidthCm, dizi[i].species);
        }
        i++;
    } 
    // Dosyayı kapatıyoruz
    fclose(fp);
}

void dizidekiVerileriMatriseEkle(IrisDataType *dizi, float **matris){
    for(int i=0; i<150; i++){
        matris[i][0] = dizi[i].sepalLengthCm;
        matris[i][1] = dizi[i].sepalWidthCm;
        matris[i][2] = dizi[i].petalLengthCm;
        matris[i][3] = dizi[i].petalWidthCm;
    }
}

void ortalamaHesabi(FILE *fp, float** matris){
    fprintf(fp, "SepalLengthCm, SepalWidthCm, PetalLengthCm ve PetalWidthCm özelliklerinin ortalama değerleri:\n\n");
    float *ort = columnMeans(matris, 150, 4);
    fprintf(fp, "SepalLengthCm: %f\n",ort[0]);
    fprintf(fp, "SepalWidthCm: %f\n",ort[1]);
    fprintf(fp, "PetalLengthCm: %f\n",ort[2]);
    fprintf(fp, "PetalWidthCm: %f\n",ort[3]);
    fprintf(fp, "\n\n");
}

void varyansHesabi(FILE *fp, float** matris){
    fprintf(fp, "SepalLengthCm, SepalWidthCm, PetalLengthCm ve PetalWidthCm özelliklerinin varyans değerleri:\n\n");
    float **transp = matrixTranspose(matris, 150, 4);
    float *sLength = transp[0];
    float *sWidth = transp[1];
    float *pLength = transp[2];
    float *pWidth = transp[3];

    fprintf(fp, "SepalLengthCm: %f\n",variance(150, sLength));
    fprintf(fp, "SepalWidthCm: %f\n",variance(150, sWidth));
    fprintf(fp, "PetalLengthCm: %f\n",variance(150, pLength));
    fprintf(fp, "PetalWidthCm: %f\n",variance(150, pWidth));
    fprintf(fp, "\n\n");
}

float variance(int n, float * dizi) {
    float ort =  mean(dizi, n);
    float toplam = 0.0;
    for (int i = 0; i < n; i++) {
        toplam += (dizi[i]-ort) * (dizi[i]-ort);
    }
    return toplam / n;
}

void korelasyonHesabi(FILE *fp, float** matris){
    fprintf(fp, "3 özellik çiftinin birbirleriyle korelasyonu:\n\n");
    float **transp = matrixTranspose(matris, 150, 4);
    float *sLength = transp[0];
    float *sWidth = transp[1];
    float *pLength = transp[2];
    float *pWidth = transp[3];
    
    fprintf(fp, "Petal Length ve Petal Width özelliklerinin birbirleriyle korelasyonu: ");
    fprintf(fp, "%f\n",correlation(pLength, pWidth, 150));

    fprintf(fp, "Sepal Length ve Petal Length özelliklerinin birbirleriyle korelasyonu: ");
    fprintf(fp, "%f\n",correlation(sLength, pLength, 150));

    fprintf(fp, "Sepal Length ve Petal Width özelliklerinin birbirleriyle korelasyonu: ");
    fprintf(fp, "%f\n",correlation(sLength, pWidth, 150));

    fprintf(fp, "\n\n");
}

void covaryansHesabi(FILE *fp, float** matris){
    fprintf(fp, "Özellik matrisinin covaryans matrisi:\n\n");
    float ** cov = covarianceMatrix(matris, 150, 4);
    for(int a=0; a<4;a++){
        for(int b=0; b<4;b++){
            fprintf(fp, "%.2f ",cov[a][b]); 
        }   
        fprintf(fp, "\n\n");
    }
}

void yeniBirDosyayaOzellikYazdir(float **matris){
    // Dosya açma işlemi. "w" parametresi ile dosyayı yazma modunda açıyoruz
    FILE *fp = fopen("IrisStatistic.txt", "w");
    if (fp == NULL) {
        printf("Dosya açilamadi!\n");
    }

    // Dosyaya hesaplamaları yazdırıyoruz
    ortalamaHesabi(fp, matris);
    varyansHesabi(fp, matris);
    korelasyonHesabi(fp, matris);
    covaryansHesabi(fp, matris);
    
    // Dosya kapatıyoruz
    fclose(fp);
}

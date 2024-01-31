# Iris Dataset Statistical Analysis

## Project Description

This project involves reading data from a file named "Iris.csv," performing statistical calculations using various functions, and writing these calculations to a file.

## Files

- **Iris.csv:** Contains information such as "Id, SepalLengthCm, SepalWidthCm, PetalLengthCm, PetalWidthCm, Species."
- **main.c:** The main source file of the project. It handles reading data, creating matrices, performing statistical calculations, and writing results to a file.
- **matrixLib.c:** Contains the implementation of functions for matrix operations and statistical calculations.
- **matrixLib.h:** Header file containing function prototypes and necessary definitions.
- **Makefile:** Makefile for compiling and running the project.

## Functions

### main.c

- **verileriDiziyeDoldurVeYazdir:** Reads the data from the "Iris.csv" file and stores it in an array.
- **dizidekiVerileriMatriseEkle:** Adds data from the array to a 150x4 matrix.
- **yeniBirDosyayaOzellikYazdir:** Performs statistical calculations on the feature matrix and writes them to a file named "IrisStatistic.txt."

### matrixLib.c ve matrixLib.h

- **returnVector:** Creates a vector of specified size.
- **returnMatrix:** Creates a matrix of specified rows and columns.
- **freeMatrix:** Frees the dynamically allocated matrix.
- **mean:** Calculates the mean of a vector.
- **covariance:** Calculates the covariance between two vectors.
- **correlation:** Calculates the correlation between two vectors.
- **matrixMultiplication:** Calculates the product of two matrices.
- **matrixTranspose:** Transposes a matrix.
- **rowMeans:** Calculates the row means of a matrix.
- **columnMeans:** Calculates the column means of a matrix.
- **covarianceMatrix:** Calculates the variance-covariance matrix of a matrix.
- **determinant:** Calculates the determinant of a matrix.
- **printVector:** Prints a vector to the screen.
- **printMatrix:** Prints a matrix to the screen.

## Usage

Place your project files in a folder and then follow the steps below in the terminal or command prompt:

1. **Compile:**
    ```bash
    make program
    ```

2. **Run:**
    ```bash
    make run
    ```

## Statistics and Results

After running the project, a file named "IrisStatistic.txt" will be created. This file contains the following statistics:
- Mean values of SepalLengthCm, SepalWidthCm, PetalLengthCm, and PetalWidthCm features.
- Variance values of SepalLengthCm, SepalWidthCm, PetalLengthCm, and PetalWidthCm features.
- Correlation between the three pairs of features.
- Covariance matrix of the feature matrix.

## Screenshot:
![ss](https://github.com/beyzayildizli/MatrixFunctionsAndFileOperations/assets/77398074/0839cd18-70fd-4455-9bac-f690fb88a358)


## Credits
This project was developed by Beyza Yıldızlı.
You can find me on [LinkedIn](https://www.linkedin.com/in/beyzayildizli/) or [GitHub](https://github.com/beyzayildizli)


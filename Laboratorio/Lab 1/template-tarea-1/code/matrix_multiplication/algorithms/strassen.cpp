#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Matrix;

// Funciones auxiliares para gestionar matrices
Matrix add(const Matrix& A, const Matrix& B, int size) {
    Matrix res(size, vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            res[i][j] = A[i][j] + B[i][j];
    return res;
}

Matrix subtract(const Matrix& A, const Matrix& B, int size) {
    Matrix res(size, vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            res[i][j] = A[i][j] - B[i][j];
    return res;
}

// Algoritmo de Strassen
Matrix strassen(const Matrix& A, const Matrix& B, int n) {
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int k = n / 2;
    Matrix a11(k, vector<int>(k)), a12(k, vector<int>(k)), a21(k, vector<int>(k)), a22(k, vector<int>(k));
    Matrix b11(k, vector<int>(k)), b12(k, vector<int>(k)), b21(k, vector<int>(k)), b22(k, vector<int>(k));

    // Dividir matrices en 4 submatrices
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + k];
            a21[i][j] = A[i + k][j];
            a22[i][j] = A[i + k][j + k];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + k];
            b21[i][j] = B[i + k][j];
            b22[i][j] = B[i + k][j + k];
        }
    }

    // Calcular las 7 multiplicaciones de Strassen
    Matrix p1 = strassen(add(a11, a22, k), add(b11, b22, k), k);       // P1 = (A11+A22)(B11+B22)
    Matrix p2 = strassen(add(a21, a22, k), b11, k);                   // P2 = (A21+A22)B11
    Matrix p3 = strassen(a11, subtract(b12, b22, k), k);              // P3 = A11(B12-B22)
    Matrix p4 = strassen(a22, subtract(b21, b11, k), k);              // P4 = A22(B21-B11)
    Matrix p5 = strassen(add(a11, a12, k), b22, k);                   // P5 = (A11+A12)B22
    Matrix p6 = strassen(subtract(a21, a11, k), add(b11, b12, k), k); // P6 = (A21-A11)(B11+B12)
    Matrix p7 = strassen(subtract(a12, a22, k), add(b21, b22, k), k); // P7 = (A12-A22)(B21+B22)

    // Combinar resultados para formar la matriz C
    Matrix c(n, vector<int>(n));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            c[i][j]         = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
            c[i][j + k]     = p3[i][j] + p5[i][j];
            c[i + k][j]     = p2[i][j] + p4[i][j];
            c[i + k][j + k] = p1[i][j] - p2[i][j] + p3[i][j] + p6[i][j];
        }
    }
    return c;
}
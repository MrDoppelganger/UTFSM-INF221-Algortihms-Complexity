#include <iostream>
#include <vector>

using namespace std;

// Definimos un alias para facilitar la lectura de matrices
typedef vector<vector<int>> Matrix;

/**
 * Multiplicación de Matrices (Método Naive)
 * @param A: Matriz izquierda
 * @param B: Matriz derecha
 * @return La matriz resultante C = A * B
 */
Matrix multiplyNaive(const Matrix& A, const Matrix& B) {
    int filasA = A.size();
    int columnasA = A[0].size();
    int columnasB = B[0].size();

    // Inicializamos la matriz resultante C con ceros
    // Tamaño: filas de A x columnas de B
    Matrix C(filasA, vector<int>(columnasB, 0));

    // El triple bucle anidado clásico
    for (int i = 0; i < filasA; i++) {           // Recorre filas de A
        for (int j = 0; j < columnasB; j++) {     // Recorre columnas de B
            for (int k = 0; k < columnasA; k++) { // Realiza el producto punto
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

int main() {
    // Ejemplo rápido 2x2
    Matrix A = {{1, 2}, {3, 4}};
    Matrix B = {{5, 6}, {7, 8}};

    Matrix resultado = multiplyNaive(A, B);

    cout << "Resultado de la multiplicacion naive:" << endl;
    for (const auto& fila : resultado) {
        for (int val : fila) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
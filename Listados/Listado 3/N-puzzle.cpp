//----------------Librerias--------------------
#include <iostream>
#include <vector>
#include <string>
#include <cmath> // Para usar la funcion abs()

using namespace std;

/*
    ------------Funcion-----------------
    calcularScatter: 
        Funcion encargada de calcular la "dispersion" 
    o suma de distancias Manhattan de cada pieza del 
    puzzle hasta su posicion objetivo.
    ------------Parametros----------------
    const vector<string>& tablero: Matriz de 4x4 con el estado actual.
    --------------Return------------------
    int: Devuelve la suma total de las distancias.
    ----------------------------------
*/
int calcularScatter(const vector<string>& tablero)
{
    int dispersion_total = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            char pieza = tablero[i][j];

            // El espacio vacio '.' no se cuenta para la dispersion
            if (pieza == '.')
            {
                continue;
            }

            // Calculamos el valor numerico de la pieza (A=0, B=1, ..., O=14)
            int valor = pieza - 'A';

            // Calculamos la fila y columna en la que DEBERIA estar
            // Como es una cuadricula 4x4, usamos division y modulo
            int fila_objetivo = valor / 4;
            int col_objetivo = valor % 4;

            // Sumamos la distancia Manhattan: |fila_actual - fila_objetivo| + |col_actual - col_objetivo|
            dispersion_total += abs(i - fila_objetivo) + abs(j - col_objetivo);
        }
    }

    return dispersion_total;
}

int main()
{
    //------------------Inicializacion---------------------------
    // Optimización para que cin/cout sean mucho más rápidos
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //------------------Lectura de Datos-------------------------
    vector<string> tablero(4);
    
    // El input siempre son exactamente 4 lineas de texto
    if (!(cin >> tablero[0])) return 0; // Por si el archivo está vacío
    cin >> tablero[1] >> tablero[2] >> tablero[3];

    //Procesamos
    int resultado = calcularScatter(tablero);

    //------------------Salida-----------------------------------
    cout << resultado << "\n";

    return 0;
}
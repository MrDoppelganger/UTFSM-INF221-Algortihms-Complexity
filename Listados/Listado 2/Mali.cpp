//----------------Librerias--------------------
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    ------------Funcion-----------------
    calcularMinimaSumaMaxima: 
        Calcula la minima suma maxima posible emparejando 
    los elementos de A (de menor a mayor) con los de B 
    (de mayor a menor) usando sus frecuencias.
    ------------Parametros----------------
    const vector<int>& frecA_orig: Frecuencias de la lista A.
    const vector<int>& frecB_orig: Frecuencias de la lista B.
    --------------Return------------------
    int: La minima suma maxima encontrada en la ronda actual.
    ----------------------------------
*/
int calcularMinimaSumaMaxima(const vector<int>& frecA_orig, const vector<int>& frecB_orig)
{
    // Creamos copias locales porque iremos "gastando" (restando) 
    // las frecuencias a medida que formamos las parejas.
    vector<int> frecA = frecA_orig;
    vector<int> frecB = frecB_orig;

    int maxima_suma = 0;
    
    // Punteros: A busca desde el más pequeño (1), B busca desde el más grande (100)
    int pA = 1;   
    int pB = 100; 

    // Mientras estemos dentro de los límites posibles (1 a 100)
    while (pA <= 100 && pB >= 1)
    {
        // Avanzamos los punteros hasta encontrar un numero que tenga frecuencia > 0
        while (pA <= 100 && frecA[pA] == 0) pA++;
        while (pB >= 1 && frecB[pB] == 0) pB--;

        // Si encontramos números válidos en ambas listas, los emparejamos
        if (pA <= 100 && pB >= 1)
        {
            // Actualizamos la maxima suma encontrada hasta ahora
            maxima_suma = max(maxima_suma, pA + pB);

            // Vemos cuántas parejas idénticas podemos formar de una sola vez
            // (Nos limitará el número que tenga menor cantidad disponible)
            int pares_formados = min(frecA[pA], frecB[pB]);
            
            // Descontamos las frecuencias que acabamos de emparejar
            frecA[pA] -= pares_formados;
            frecB[pB] -= pares_formados;
        }
    }

    return maxima_suma;
}

int main()
{
    //------------------Inicializacion---------------------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    //------------------Lectura de Datos-------------------------
    // Verificamos la lectura de la cantidad de rondas
    if (!(cin >> n)) return 0;

    // Inicializamos vectores de frecuencia de tamaño 101 en ceros.
    // Usamos 101 para que el índice coincida exactamente con el número (0 a 100).
    vector<int> frecuenciaA(101, 0);
    vector<int> frecuenciaB(101, 0);

    //------------------Procesamiento y Salida-------------------
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;

        // Aumentamos la frecuencia de los números recibidos en esta ronda
        frecuenciaA[a]++;
        frecuenciaB[b]++;

        // Calculamos e imprimimos el resultado de la ronda actual
        cout << calcularMinimaSumaMaxima(frecuenciaA, frecuenciaB) << "\n";
    }

    return 0;
}
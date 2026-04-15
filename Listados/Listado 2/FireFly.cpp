//----------------Librerias--------------------
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    ------------Funcion-----------------
    calcularMejorRuta: 
        Calcula el numero minimo de obstaculos que 
    se deben destruir y cuantos niveles de altura 
    permiten lograr ese minimo.
    ------------Parametros----------------
    int h: Altura total de la cueva.
    const vector<int>& suelo: Frecuencias de estalagmitas.
    const vector<int>& techo: Frecuencias de estalactitas.
    --------------Return------------------
    pair<int, int>: Un par donde el primer valor es el 
    minimo de impactos y el segundo es la cantidad de niveles.
    ----------------------------------
*/
pair<int, int> calcularMejorRuta(int h, vector<int>& suelo, vector<int>& techo)
{
    // Acumulamos de arriba hacia abajo (Suffix Sums).
    // Si hay una estalagmita de tamaño 5, tambien bloquea los niveles 4, 3, 2 y 1.
    for (int i = h - 1; i >= 1; i--)
    {
        suelo[i] += suelo[i + 1];
        techo[i] += techo[i + 1];
    }

    int minimo_impactos = 200005; // Un numero mayor al N maximo posible
    int niveles_optimos = 0;

    // Evaluamos cada nivel de altura posible para la luciernaga (1 hasta H)
    for (int nivel = 1; nivel <= h; nivel++)
    {
        // Las estalagmitas (suelo) impactan directamente segun el nivel.
        int impactos_suelo = suelo[nivel];

        // Las estalactitas (techo) cuelgan desde arriba. 
        // Si el nivel es 'nivel', la distancia desde el techo es (h - nivel + 1).
        int impactos_techo = techo[h - nivel + 1];

        int total_impactos = impactos_suelo + impactos_techo;

        if (total_impactos < minimo_impactos)
        {
            // Encontramos un nuevo record, reiniciamos el contador de niveles
            minimo_impactos = total_impactos;
            niveles_optimos = 1;
        }
        else if (total_impactos == minimo_impactos)
        {
            // Encontramos otro nivel que empata con el record actual
            niveles_optimos++;
        }
    }

    return {minimo_impactos, niveles_optimos};
}

int main()
{
    //------------------Inicializacion---------------------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, h;

    //------------------Lectura de Datos-------------------------
    if (!(cin >> n >> h)) return 0;

    // Vectores de frecuencias instanciados en 0. 
    // Tamaño h + 1 para que los indices coincidan con las alturas (1 a h).
    vector<int> estalagmitas(h + 1, 0); // Suelo
    vector<int> estalactitas(h + 1, 0); // Techo

    for (int i = 0; i < n; i++)
    {
        int tamaño;
        cin >> tamaño;

        // Alternamos: los indices pares (0, 2, 4...) son del suelo, los impares del techo
        if (i % 2 == 0)
        {
            estalagmitas[tamaño]++;
        }
        else
        {
            estalactitas[tamaño]++;
        }
    }

    //------------------Procesamiento----------------------------
    // Obtenemos los resultados desde nuestra funcion
    pair<int, int> resultado = calcularMejorRuta(h, estalagmitas, estalactitas);

    //------------------Salida-----------------------------------
    cout << resultado.first << " " << resultado.second << "\n";

    return 0;
}
//---------------------------------Librerias--------------------------
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    //---------------------------Inicializacion----------------------------
    // Trucazo
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int c, n;

    // Iteramos entre todos los casos de prueba, hasta llegar al final
    while (cin >> c >> n)
    {
        //Creamos nuestros arreglos principales
        vector<int> valores(n);
        vector<int> pesos(n);

        //Obtenemos los valores del problema
        for (int i = 0; i < n; i++)
        {
            cin >> valores[i] >> pesos[i];
        }

        //-------------------------------------Algoritmo-----------------------------
        //Creamos la matriz que se encargara de guardar el desarrollo del problema
        vector<vector<int>> dp(n + 1, vector<int>(c + 1, 0));

        // Rellenamos la tabla DP iterando objeto por objeto, y capacidad por capacidad
        for (int i = 1; i <= n; i++)
        {
            for (int w = 0; w <= c; w++)
            {
                // Si el peso del objeto actual (indice i-1) es menor o igual a la capacidad evaluada 'w'
                if (pesos[i - 1] <= w)
                {
                    // Tomamos el máximo entre NO incluir el objeto y SÍ incluirlo
                    dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - pesos[i - 1]] + valores[i - 1]);
                }
                else
                {
                    // Si el objeto no cabe, heredamos obligatoriamente el valor máximo sin incluirlo
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }

        //----------------------------------Reconstrcción----------------------------
        // Creamos nuestro estado inicial para obtener el camino de vuelta a la ruta
        vector<int> elegidos;
        int w_actual = c;

        // Recorremos de atrás hacia adelante
        for (int i = n; i > 0 && w_actual > 0; i--)
        {
            //Si el valor maximo en (i,w) es diferente al valor de arriba, entonces este objeto esta entre
            if (dp[i][w_actual] != dp[i - 1][w_actual])
            {
                // Guardamos el valor del objeto y restamos el peso de la mochila
                elegidos.push_back(i - 1); 
                w_actual -= pesos[i - 1];  
            }
        }

        //------------------Salida-----------------------------------
        // Mostramos la cantidad de elementos seleccionados
        cout << elegidos.size() << "\n";
        
        // mostramos los indices elegidos 
        for (int i = 0; i < elegidos.size(); i++)
        {
            cout << elegidos[i] << (i == elegidos.size() - 1 ? "" : " "); // Hay que separarlos por espacios
        }
        cout << "\n";
    }

    return 0;
}
//------------------------------------Librerias------------------------------
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    //------------------Inicializacion---------------------------
    // Trucazo
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    // iteramos hasta toparnos con el final al encontrar el 0.
    while (cin >> n && n != 0)
    {
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }

        //-----------------------------------------ALgoritmo----------------------------
        // creamos el arreglo dp que almacenará la longitud de la subsecuencia creciente más larga, partimos inicialmente en 1
        vector<int> dp(n, 1);
        int max_len = 0;

        // Llenamos la tabla DP de atrás hacia adelante para que luego nos resulte mas sencillo reconstruir la solución
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i + 1; j < n; j++)
            {
                // Si el elemento de la derecha es mayor, saltamos hacia el
                if (arr[i] < arr[j])
                {
                    dp[i] = max(dp[i], 1 + dp[j]);
                }
            }
            // Actualizamos la longitud máxima global que hemos encontrado
            max_len = max(max_len, dp[i]);
        }

        //--------------------------Reconstrucción de la Respuesta-----------------------------
        //Ahora necesitamos la secuencia con los valroes mas pequeños
        vector<int> resultado;
        int longitud_buscada = max_len;
        // todo los valores son igual o mayor a 0, asi que usmaos -1 para comparar
        int valor_anterior = -1; 
        int indice_actual = -1;

        while (longitud_buscada > 0)
        {
            int mejor_indice = -1;
            int mejor_valor = 2e9; //Inicializamos con un numero absurdamente grande

            // Buscamos hacia adelante desde nuestro último salto
            for (int i = indice_actual + 1; i < n; i++)
            {
                //Comprobamos que se puede conectar con el anterior y demas. 
                if (arr[i] > valor_anterior && dp[i] == longitud_buscada)
                {
                    // Queremos el valor más pequeño posible (lexicográficamente menor)
                    if (arr[i] < mejor_valor)
                    {
                        mejor_valor = arr[i];
                        mejor_indice = i;
                    }
                }
            }

            // Damos el salto: guardamos el mejor elemento encontrado y actualizamos los rastreadores
            resultado.push_back(arr[mejor_indice]);
            valor_anterior = arr[mejor_indice];
            indice_actual = mejor_indice;
            
            // Ahora necesitamos buscar una subsecuencia que sea 1 elemento más corta
            longitud_buscada--;
        }

        //------------------Salida-----------------------------------
        // Imprimimos el tamaño máximo
        cout << max_len;
        
        // Imprimimos los valores reconstruidos separados por un espacio
        for (int i = 0; i < resultado.size(); i++)
        {
            cout << " " << resultado[i];
        }
        cout << "\n";
    }

    return 0;
}
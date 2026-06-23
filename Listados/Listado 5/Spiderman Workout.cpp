//-------------------------------Librerias-------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    //------------------Inicializacion---------------------------
    // trucazo
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Creamos un "infinito" practico
    const int INF = 1e9;
    int N;
    cin >> N;

    //Iteramos la cantidad de casos de poruebas
    for (int caso = 0; caso < N; caso++)
    {
        //establecemos las variables iniiciales.
        int M;
        cin >> M;
        vector<int> d(M + 1);
        int suma_total = 0;
        
        for (int i = 1; i <= M; i++)
        {
            cin >> d[i];
            suma_total += d[i];
        }

       //Como necesitamos bajar lo subido, esto requiere que el valor sea par
        if (suma_total % 2 != 0)
        {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        //--------------------------------Algoritmo---------------------------------------
        //Creamos nuestra matriz que almacenara el conocimiento del algoritmo
        vector<vector<int>> dp(M + 1, vector<int>(suma_total + 1, INF));
        // Matriz extra para reconstruir el camino. Guardaremos 'U' o 'D'.
        vector<vector<char>> dir(M + 1, vector<char>(suma_total + 1, ' '));

        // Caso base: Al inicio (0 movimientos), estamos en la calle (altura 0) y nuestro pico maximo historico es 0.
        dp[0][0] = 0;

        // Llenamos la tabla evaluando movimiento a movimiento
        for (int i = 1; i <= M; i++)
        {
            for (int h = 0; h <= suma_total; h++)
            {
                //Opcion 1: Llegamos a esta altura 'h' SUBIENDO ('U').
                if (h - d[i] >= 0 && dp[i - 1][h - d[i]] != INF)
                {
                    // Nuestro nuevo pico maximo es el maximo entre nuestra altura actual (h) y el pico maximo que ya traíamos acumulado.
                    int pico_maximo = max(h, dp[i - 1][h - d[i]]);
                    
                    // Si este camino nos da un pico menor que el que teniamos registrado, lo tomamos
                    if (pico_maximo < dp[i][h])
                    {
                        dp[i][h] = pico_maximo;
                        dir[i][h] = 'U';
                    }
                }

                // Opcion 2: Llegamos a esta altura 'h' BAJANDO ('D')
                if (h + d[i] <= suma_total && dp[i - 1][h + d[i]] != INF)
                { 
                    //Como estamos bajando, nuestro pico historico es el ultimo que teniamos registrado
                    int pico_maximo = dp[i - 1][h + d[i]];
                    
                    if (pico_maximo < dp[i][h])
                    {
                        dp[i][h] = pico_maximo;
                        dir[i][h] = 'D';
                    }
                }
            }
        }

        //-------------------------Reconstruccion-------------------------
        // Nos piden terminar a nivel de la calle. Verificamos si es posible:
        if (dp[M][0] == INF)
        {
            cout << "IMPOSSIBLE\n";
        }
        else
        {
            string resultado = "";
            int h_actual = 0; // Queremos terminar en altura 0

            // Reconstruimos el camino de atras hacia adelante (Backtracking)
            for (int i = M; i >= 1; i--)
            {
                char movimiento = dir[i][h_actual];
                resultado += movimiento;

                // Revertimos la altura para buscar de donde veniamos en el paso anterior
                if (movimiento == 'U')
                {
                    h_actual = h_actual - d[i]; // Si aqui llegué subiendo, antes estaba mas abajo
                }
                else
                {
                    h_actual = h_actual + d[i]; // Si aqui llegué bajando, antes estaba mas arriba
                }
            }

            // Como construimos el string del ultimo movimiento al primero, lo invertimos
            reverse(resultado.begin(), resultado.end());
            cout << resultado << "\n";
        }
    }

    return 0;
}
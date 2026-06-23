//------------------Librerias--------------------
#include "common.h"
#include <algorithm>
#include <vector>

using namespace std;

//------------------Algoritmo Principal------------------
/*
    ------------Funcion-----------------
    solve_dp: Funcion encargada de resolver el problema aplicando 
        programacion dinamica al estilo Knapsack 2D.
    ------------Parametros----------------
    int n: Numero de animes.
    long long M: Tiempo maximo disponible.
    long long E: Energia maxima disponible.
    const vector<Anime>& animes: Vector con los datos de los animes.
    --------------Return------------------
    long long: La satisfaccion maxima que se puede obtener.
    ----------------------------------
*/
long long solve_dp(int n, long long M, long long E, const vector<Anime>& animes) {
    //------------------Inicializacion------------------
    // Matriz DP de tamaño (M + 1) x (E + 1)
    // dp[m][e] = max satisfaccion usando a lo sumo 'm' tiempo y 'e' energia
    vector<vector<long long>> dp(M + 1, vector<long long>(E + 1, 0));

    //------------------Procesamiento------------------
    for (int i = 0; i < n; ++i) {
        // Para cada anime, necesitamos una nueva matriz para no usar un capitulo del mismo anime 
        // multiplicidad de veces. Alternativamente, iteramos de M a 0 y de E a 0.
        // Copiamos el estado anterior.
        vector<vector<long long>> next_dp = dp;
        
        const Anime& anime = animes[i];
        int q = anime.q;
        
        // Iteramos por todos los prefijos posibles de este anime
        long long t_acum = 0;
        long long c_acum = 0;
        long long v_acum = 0;

        for (int k = 1; k <= q; ++k) {
            t_acum += anime.capitulos[k - 1].t;
            c_acum += anime.capitulos[k - 1].c;
            v_acum += anime.capitulos[k - 1].v;
            
            long long v_total = v_acum;
            if (k == q) {
                v_total += anime.b; // Sumar bono por completar
            }

            // Actualizamos la DP temporal iterando sobre todos los estados de M y E posibles
            for (long long m = M; m >= t_acum; --m) {
                for (long long e = E; e >= c_acum; --e) {
                    if (dp[m - t_acum][e - c_acum] + v_total > next_dp[m][e]) {
                        next_dp[m][e] = dp[m - t_acum][e - c_acum] + v_total;
                    }
                }
            }
        }
        
        // Actualizamos la DP global para el siguiente anime
        dp = next_dp;
    }

    //------------------Salida------------------
    long long max_satisfaccion = 0;
    for (long long m = 0; m <= M; ++m) {
        for (long long e = 0; e <= E; ++e) {
            if (dp[m][e] > max_satisfaccion) {
                max_satisfaccion = dp[m][e];
            }
        }
    }

    return max_satisfaccion;
}

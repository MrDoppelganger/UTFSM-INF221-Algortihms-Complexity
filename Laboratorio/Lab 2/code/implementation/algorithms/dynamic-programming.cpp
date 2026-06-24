//------------------Librerias--------------------
#include "common.h"
#include <algorithm>
#include <vector>

using namespace std;


/*
    ------------Funcion-----------------
    resolverDP: 
        Funcion encargada de resolver el problema aplicando 
        programacion dinamica al estilo de la mochila 2D.
    ------------Parametros----------------
    int n: Numero de animes.
    long long M: Tiempo maximo disponible.
    long long E: Energia maxima disponible.
    const vector<Anime>& animes: Vector con los datos de los animes.
    --------------Return------------------
    long long: La satisfaccion maxima que se puede obtener.
    ----------------------------------
*/
long long resolverDP(int n, long long M, long long E, const vector<Anime>& animes) 
{
    //-------------------------Inicializacion--------------------------------
    // Matriz DP de tamaño (M + 1)x(E + 1) donde guardamos las maximas satisfacción
    vector<vector<long long>> dp(M + 1, vector<long long>(E + 1, 0));

    //----------------------------Algoritmo-----------------------------------
    for (int i = 0; i < n; ++i) 
    {
        // Creamos una nueva matriz por anime, para no usar un capitulo del mismo anime. Copiamos el estado anterior
        vector<vector<long long>> next_dp = dp;
        const Anime& ANIME = animes[i];
        int q = ANIME.q;
        // Iteramos por todos los prefijos posibles de este anime
        long long t_acum = 0;
        long long c_acum = 0;
        long long v_acum = 0;

        for (int k = 1; k <= q; ++k) 
        {
            t_acum += ANIME.capitulos[k - 1].t;
            c_acum += ANIME.capitulos[k - 1].c;
            v_acum += ANIME.capitulos[k - 1].v;
            
            long long v_total = v_acum;
            // Sumamos el bono por completar de ser necesario
            if (k == q) 
            {
                v_total += ANIME.b; 
            }

            // Actualizamos la DP temporal iterando sobre todos los estados de M y E posibles
            for (long long m = M; m >= t_acum; --m) 
            {
                for (long long e = E; e >= c_acum; --e) 
                {
                    if (dp[m - t_acum][e - c_acum] + v_total > next_dp[m][e]) 
                    {
                        next_dp[m][e] = dp[m - t_acum][e - c_acum] + v_total;
                    }
                }
            }
        }
        
        // Actualizamos la DP global para el siguiente anime
        dp = next_dp;
    }

    //------------------Salida------------------
    long long satisfaccion_maxima = 0;
    for (long long m = 0; m <= M; ++m) 
    {
        for (long long e = 0; e <= E; ++e) 
        {
            if (dp[m][e] > satisfaccion_maxima) 
            {
                satisfaccion_maxima = dp[m][e];
            }
        }
    }

    return satisfaccion_maxima;
}

//------------------Librerias--------------------
#include "common.h"
#include <vector>

using namespace std;

//------------------Algoritmo Principal------------------
/*
    ------------Funcion-----------------
    resolverGreedyVdivT: 
        Funcion encargada de resolver el problema aplicando 
        un algoritmo greedy basado en la rentabilidad de tiempo (v/t).
    ------------Parametros----------------
    int n: Numero de animes.
    long long M: Tiempo maximo disponible.
    long long E: Energia maxima disponible.
    const vector<Anime>& animes: Vector con los datos de los animes.
    --------------Return------------------
    long long: La satisfaccion maxima que se obtuvo mediante el greedy.
    ----------------------------------
*/
long long resolverGreedyVdivT(int n, long long M, long long E, const vector<Anime>& animes) 
{
    //------------------Inicializacion------------------
    long long t_actual = 0;
    long long e_actual = 0;
    long long v_total = 0;
    // Arreglo para llevar el control de en qué capitulo vamos para cada anime
    vector<int> capitulo_actual(n, 0);
    // Arreglo para saber si un anime ya fue descartado
    vector<bool> descartados(n, false);

    //------------------Procesamiento------------------
    while (true) 
    {
        int mejor_anime = -1;
        double mejor_ratio = -1.0;
        long long mejor_v = 0; // Para sumar la satisfaccion real despues
        
        // Buscamos el anime cuyo siguiente capitulo de la mayor rentabilidad (v/t)
        for (int i = 0; i < n; ++i) 
        {
            if (descartados[i]) continue;
            
            int cap_idx = capitulo_actual[i];
            if (cap_idx >= animes[i].q) 
            {
                descartados[i] = true;
                continue;
            }
            
            long long v_actual = animes[i].capitulos[cap_idx].v;
            long long t_actual = animes[i].capitulos[cap_idx].t;
            
            if (cap_idx == animes[i].q - 1) 
            {
                v_actual += animes[i].b;
            }
            
            // Calculamos la rentabilidad
            double ratio = 0.0;
            if (t_actual > 0) 
            {
                ratio = (double)v_actual / t_actual;
            } else 
            {
                ratio = 999999999.0; // Si t es 0, la rentabilidad es practicamente infinita
            }
            
            if (ratio > mejor_ratio) 
            {
                mejor_ratio = ratio;
                mejor_anime = i;
                mejor_v = v_actual;
            }
        }
        
        if (mejor_anime == -1) break;
        
        int cap_idx = capitulo_actual[mejor_anime];
        long long t_cost = animes[mejor_anime].capitulos[cap_idx].t;
        long long e_cost = animes[mejor_anime].capitulos[cap_idx].c;
        
        if (t_actual + t_cost <= M && e_actual + e_cost <= E) 
        {
            t_actual += t_cost;
            e_actual += e_cost;
            v_total += mejor_v; 
            
            capitulo_actual[mejor_anime]++;
        } else 
        {
            descartados[mejor_anime] = true;
        }
    }

    return v_total;
}

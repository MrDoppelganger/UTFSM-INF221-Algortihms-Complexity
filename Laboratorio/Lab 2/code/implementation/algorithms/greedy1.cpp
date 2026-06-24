//------------------Librerias--------------------
#include "common.h"
#include <vector>

using namespace std;

//------------------Algoritmo Principal------------------
/*
    ------------Funcion-----------------
    resolverGreedyV: 
        Funcion encargada de resolver el problema aplicando 
        un algoritmo greedy basado en la satisfaccion (v).
    ------------Parametros----------------
    int n: Numero de animes.
    long long M: Tiempo maximo disponible.
    long long E: Energia maxima disponible.
    const vector<Anime>& animes: Vector con los datos de los animes.
    --------------Return------------------
    long long: La satisfaccion maxima que se obtuvo mediante el greedy.
    ----------------------------------
*/
long long resolverGreedyV(int n, long long M, long long E, const vector<Anime>& animes) 
{
    //-----------------------Inicializacion---------------------------------
    long long t_actual = 0;
    long long e_actual = 0;
    long long v_total = 0;
    // Arreglo para llevar el control de en qué capitulo vamos para cada anime
    vector<int> capitulo_actual(n, 0);
    // Arreglo para saber si un anime ya fue descartado (porque no alcanza el tiempo o energia)
    vector<bool> descartados(n, false);

    //-------------------------------Procesamiento---------------------------
    while (true) 
    {
        int mejor_anime = -1;
        long long mejor_v = -1;
        
        // Buscamos el anime cuyo siguiente capitulo de la mayor satisfaccion
        for (int i = 0; i < n; ++i) 
        {
            if (descartados[i]) continue;
            
            int cap_idx = capitulo_actual[i];
            // Si ya vimos todos los capitulos, se descarta
            if (cap_idx >= animes[i].q) 
            {
                descartados[i] = true;
                continue;
            }
            
            long long v_actual = animes[i].capitulos[cap_idx].v;
            
            // Si es el ultimo capitulo, le sumamos el bono a su "valor"
            if (cap_idx == animes[i].q - 1) 
            {
                v_actual += animes[i].b;
            }
            
            if (v_actual > mejor_v) 
            {
                mejor_v = v_actual;
                mejor_anime = i;
            }
        }
        
        // Si no encontramos ningun anime valido, terminamos
        if (mejor_anime == -1) break;
        
        // Revisamos si el mejor capitulo encontrado cabe en el tiempo y energia restantes
        int cap_idx = capitulo_actual[mejor_anime];
        long long t_cost = animes[mejor_anime].capitulos[cap_idx].t;
        long long e_cost = animes[mejor_anime].capitulos[cap_idx].c;
        
        if (t_actual + t_cost <= M && e_actual + e_cost <= E) 
        {
            // Lo elegimos
            t_actual += t_cost;
            e_actual += e_cost;
            v_total += mejor_v; // Ya trae el bono si era el ultimo
            
            capitulo_actual[mejor_anime]++;
        } else 
        {
            // No cabe, lo descartamos definitivamente
            descartados[mejor_anime] = true;
        }
    }

    //------------------Salida------------------
    return v_total;
}

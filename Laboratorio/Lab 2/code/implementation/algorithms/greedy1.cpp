//------------------Librerias--------------------
#include "common.h"
#include <vector>

using namespace std;

//------------------Algoritmo Principal------------------
/*
    ------------Funcion-----------------
    solve_greedy1: Funcion encargada de resolver el problema aplicando 
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
long long solve_greedy1(int n, long long M, long long E, const vector<Anime>& animes) {
    //------------------Inicializacion------------------
    long long current_t = 0;
    long long current_e = 0;
    long long total_v = 0;
    
    // Arreglo para llevar el control de en qué capitulo vamos para cada anime
    vector<int> current_chapter(n, 0);
    // Arreglo para saber si un anime ya fue descartado (porque no alcanza el tiempo o energia)
    vector<bool> discarded(n, false);

    //------------------Procesamiento------------------
    while (true) {
        int best_anime = -1;
        long long best_v = -1;
        
        // Buscamos el anime cuyo siguiente capitulo de la mayor satisfaccion
        for (int i = 0; i < n; ++i) {
            if (discarded[i]) continue;
            
            int cap_idx = current_chapter[i];
            // Si ya vimos todos los capitulos, se descarta
            if (cap_idx >= animes[i].q) {
                discarded[i] = true;
                continue;
            }
            
            long long v_actual = animes[i].capitulos[cap_idx].v;
            
            // Si es el ultimo capitulo, le sumamos el bono a su "valor"
            if (cap_idx == animes[i].q - 1) {
                v_actual += animes[i].b;
            }
            
            if (v_actual > best_v) {
                best_v = v_actual;
                best_anime = i;
            }
        }
        
        // Si no encontramos ningun anime valido, terminamos
        if (best_anime == -1) break;
        
        // Revisamos si el mejor capitulo encontrado cabe en el tiempo y energia restantes
        int cap_idx = current_chapter[best_anime];
        long long t_cost = animes[best_anime].capitulos[cap_idx].t;
        long long e_cost = animes[best_anime].capitulos[cap_idx].c;
        
        if (current_t + t_cost <= M && current_e + e_cost <= E) {
            // Lo elegimos
            current_t += t_cost;
            current_e += e_cost;
            total_v += best_v; // Ya trae el bono si era el ultimo
            
            current_chapter[best_anime]++;
        } else {
            // No cabe, lo descartamos definitivamente
            discarded[best_anime] = true;
        }
    }

    //------------------Salida------------------
    return total_v;
}

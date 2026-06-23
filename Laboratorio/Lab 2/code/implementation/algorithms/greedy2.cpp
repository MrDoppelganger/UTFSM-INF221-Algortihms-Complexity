//------------------Librerias--------------------
#include "common.h"
#include <vector>

using namespace std;

//------------------Algoritmo Principal------------------
/*
    ------------Funcion-----------------
    solve_greedy2: Funcion encargada de resolver el problema aplicando 
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
long long solve_greedy2(int n, long long M, long long E, const vector<Anime>& animes) {
    //------------------Inicializacion------------------
    long long current_t = 0;
    long long current_e = 0;
    long long total_v = 0;
    
    // Arreglo para llevar el control de en qué capitulo vamos para cada anime
    vector<int> current_chapter(n, 0);
    // Arreglo para saber si un anime ya fue descartado
    vector<bool> discarded(n, false);

    //------------------Procesamiento------------------
    while (true) {
        int best_anime = -1;
        double best_ratio = -1.0;
        long long best_v = 0; // Para sumar la satisfaccion real despues
        
        // Buscamos el anime cuyo siguiente capitulo de la mayor rentabilidad (v/t)
        for (int i = 0; i < n; ++i) {
            if (discarded[i]) continue;
            
            int cap_idx = current_chapter[i];
            if (cap_idx >= animes[i].q) {
                discarded[i] = true;
                continue;
            }
            
            long long v_actual = animes[i].capitulos[cap_idx].v;
            long long t_actual = animes[i].capitulos[cap_idx].t;
            
            if (cap_idx == animes[i].q - 1) {
                v_actual += animes[i].b;
            }
            
            // Calculamos la rentabilidad
            double ratio = 0.0;
            if (t_actual > 0) {
                ratio = (double)v_actual / t_actual;
            } else {
                ratio = 999999999.0; // Si t es 0, la rentabilidad es practicamente infinita
            }
            
            if (ratio > best_ratio) {
                best_ratio = ratio;
                best_anime = i;
                best_v = v_actual;
            }
        }
        
        if (best_anime == -1) break;
        
        int cap_idx = current_chapter[best_anime];
        long long t_cost = animes[best_anime].capitulos[cap_idx].t;
        long long e_cost = animes[best_anime].capitulos[cap_idx].c;
        
        if (current_t + t_cost <= M && current_e + e_cost <= E) {
            current_t += t_cost;
            current_e += e_cost;
            total_v += best_v; 
            
            current_chapter[best_anime]++;
        } else {
            discarded[best_anime] = true;
        }
    }

    //------------------Salida------------------
    return total_v;
}

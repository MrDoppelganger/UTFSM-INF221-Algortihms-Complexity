//------------------Librerias--------------------
#include "common.h"
#include <algorithm>
#include <vector>

using namespace std;

//------------------Funciones Auxiliares------------------
/*
    ------------Funcion-----------------
    backtrack: 
        Funcion recursiva que explora todas las combinaciones validas de 
        prefijos de capitulos para cada anime.
    ------------Parametros----------------
    int index:                  Indice del anime actual que estamos procesando.
    int n:                      Cantidad total de animes.
    long long current_t:        Tiempo acumulado actual.
    long long current_e:        Energia acumulada actual.
    long long current_v:        Satisfaccion acumulada actual.
    long long M:                Tiempo maximo disponible.
    long long E:                Energia maxima disponible.
    const vector<Anime>& animes: Vector con los datos de los animes.
    long long& max_satisfaccion: Referencia a la maxima satisfaccion encontrada.
    --------------Return------------------
    void: No retorna nada, actualiza max_satisfaccion por referencia.
    ----------------------------------
*/
void backtrack(int index, int n, long long current_t, long long current_e, long long current_v,
            long long M, long long E, const vector<Anime>& animes, long long& max_satisfaccion) 
{
    
    //------------------Caso Base------------------
    if (index == n) 
    {
        if (current_v > max_satisfaccion) 
        {
            max_satisfaccion = current_v;
        }
        return;
    }

    //------------------Procesamiento------------------
    // Opcion 1: No ver ningun capitulo del anime actual
    backtrack(index + 1, n, current_t, current_e, current_v, M, E, animes, max_satisfaccion);

    // Opciones 2 a q+1: Ver los primeros k capitulos del anime actual
    long long t_acum = 0;
    long long c_acum = 0;
    long long v_acum = 0;

    const Anime& anime_actual = animes[index];
    int q = anime_actual.q;

    for (int k = 1; k <= q; ++k) {
        t_acum += anime_actual.capitulos[k - 1].t;
        c_acum += anime_actual.capitulos[k - 1].c;
        v_acum += anime_actual.capitulos[k - 1].v;

        // Si agregar este capitulo excede los limites, no podemos seguir con prefijos mas largos
        if (current_t + t_acum > M || current_e + c_acum > E) {
            break; 
        }

        long long v_total_actual = current_v + v_acum;
        // Si vimos todos los capitulos (k == q), sumamos el bono
        if (k == q) {
            v_total_actual += anime_actual.b;
        }

        backtrack(index + 1, n, current_t + t_acum, current_e + c_acum, v_total_actual, M, E, animes, max_satisfaccion);
    }
}

//------------------Algoritmo Principal------------------
/*
    ------------Funcion-----------------
    solve_brute_force: Funcion encargada de resolver el problema aplicando 
        fuerza bruta.
    ------------Parametros----------------
    int n: Numero de animes.
    long long M: Tiempo maximo disponible.
    long long E: Energia maxima disponible.
    const vector<Anime>& animes: Vector con los datos de los animes.
    --------------Return------------------
    long long: La satisfaccion maxima que se puede obtener.
    ----------------------------------
*/
long long solve_brute_force(int n, long long M, long long E, const vector<Anime>& animes) {
    long long max_satisfaccion = 0;
    backtrack(0, n, 0, 0, 0, M, E, animes, max_satisfaccion);
    return max_satisfaccion;
}

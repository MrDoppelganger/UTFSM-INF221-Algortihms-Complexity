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
    int index: Indice del anime actual que estamos procesando.
    int n: Cantidad total de animes.
    long long t_actual: Tiempo acumulado actual.
    long long e_actual: Energia acumulada actual.
    long long v_actual: Satisfaccion acumulada actual.
    long long M: Tiempo maximo disponible.
    long long E: Energia maxima disponible.
    const vector<Anime>& animes: Vector con los datos de los animes.
    long long& satisfaccion_maxima: Referencia a la maxima satisfaccion encontrada.
    --------------Return------------------
    void: No retorna nada, actualiza satisfaccion_maxima por referencia.
    ----------------------------------
*/
void backtrack(int index, int n, long long t_actual, long long e_actual, long long v_actual, long long M,
            long long E, const vector<Anime> &animes, long long &satisfaccion_maxima) 
{
    //-----------------------------Caso Base-----------------------------
    // Si el indice es igual al numero de animes, hemos evaluado todas las
    // opciones
    if (index == n) 
    {
        if (v_actual > satisfaccion_maxima) 
        {
        satisfaccion_maxima = v_actual;
        }
        return;
    }

    //-----------------------------Procesamiento-----------------------------
    // Opcion 1: No ver ningun capitulo del anime actual
    backtrack(index + 1, n, t_actual, e_actual, v_actual, M, E, animes, satisfaccion_maxima);

    // Opciones 2: Ver los primeros k capitulos del anime actual
    long long t_acum = 0;
    long long c_acum = 0;
    long long v_acum = 0;

    const Anime &anime_actual = animes[index];
    int q = anime_actual.q;

    for (int k = 1; k <= q; ++k) 
    {
        t_acum += anime_actual.capitulos[k - 1].t;
        c_acum += anime_actual.capitulos[k - 1].c;
        v_acum += anime_actual.capitulos[k - 1].v;
        // Si agregar este capitulo excede los limites, no podemos seguir con prefijos mas largos
        if (t_actual + t_acum > M || e_actual + c_acum > E) 
        {
            break;
        }

        long long v_total_actual = v_actual + v_acum;
        // Si vimos todos los capitulos (k == q), sumamos el bono
        if (k == q) 
        {
            v_total_actual += anime_actual.b;
        }

        backtrack(index + 1, n, t_actual + t_acum, e_actual + c_acum,
        v_total_actual, M, E, animes, satisfaccion_maxima);
    }
}

/*
    ------------Funcion-----------------
    resolverFuerzaBruta: 
        Funcionprincipal encargada de resolver 
        el problema aplicando fuerza bruta.
    ------------Parametros----------------
    int n: Numero de animes.
    long long M: Tiempo maximo disponible.
    long long E: Energia maxima disponible.
    const vector<Anime>& animes: Vector con los datos de los animes.
    --------------Return------------------
    long long: La satisfaccion maxima que se puede obtener.
    ----------------------------------
*/
long long resolverFuerzaBruta(int n, long long M, long long E, const vector<Anime> &animes) 
{
  long long satisfaccion_maxima = 0;
  backtrack(0, n, 0, 0, 0, M, E, animes, satisfaccion_maxima);

  return satisfaccion_maxima;
}
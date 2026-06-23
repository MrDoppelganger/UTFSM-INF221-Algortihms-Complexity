//------------------Librerias--------------------
#pragma once
#include <string>
#include <vector>

using namespace std;
//------------------Estructuras------------------
/*
    -----------------Struct---------------------
    Clase Capitulo:
        Estructura encargada de almacenar las caracteristicas
        de cada capitulo
    ---------------Parametros-------------------    
    long long t: tiempo en minutos del capitulo
    long long c: costo de energia del capitulo
    long long v: puntaje de satisfaccion
    --------------------------------------------
 */
struct Capitulo {
    long long t; 
    long long c; 
    long long v; 
};

/*
    -----------------Struct---------------------
    Clase Anime:
       Clase para guardar la informacion de cada
       anime.
    ---------------Parametros-------------------    
    string nombre:  string que almacena el nombre del anime
    int q:          Cantidad de capitulos
    long long b:    Bono de satisfaccion por completar
    vector<Capitulo> capitlos:  lista de capitulos
    --------------------------------------------
 */
struct Anime {
    string nombre;
    int q; 
    long long b; 
    vector<Capitulo> capitulos;
};

//------------------Declaracion de Algoritmos------------------
long long solve_brute_force(int n, long long M, long long E, const vector<Anime>& animes);
long long solve_dp(int n, long long M, long long E, const vector<Anime>& animes);
long long solve_greedy1(int n, long long M, long long E, const vector<Anime>& animes);
long long solve_greedy2(int n, long long M, long long E, const vector<Anime>& animes);

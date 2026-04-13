//----------------Librerias--------------------
#include <iostream>
#include <vector> 
#include <algorithm>
#include <iterator>

using namespace std;

/*
    ------------Funcion-----------------
    pasosSorting: 
        Funcion encargada de ordenar y devolver
    la cantidad de pasos que se dieron para ordenar
    las alturas de los niños
    ------------Parametros----------------
    const vector<int>& arr: Vector con las alturas de los niños
    --------------Return------------------
    int: Devuelve el numero de pasos que se dieron 
    para ordenar el a los niños.
    ----------------------------------
*/
int pasosSorting(const vector<int>& arr)
{
    //Creamos el estado inicial del arreglo donde se iran colocando los niños ordenadamente.
    vector<int> fila_ordenada;
    fila_ordenada.push_back(arr[0]);

    //Creamos la variable que almacenara el valor del retorno.
    int cantidad_pasos = 0;

    //Iteramos por la lista -1 para ir insertando a cada persona.
    for(int i = 1; i < 20; i++)
    {
        //Buscamos la posicion del primer niño que mida mas.
        auto pos = upper_bound(fila_ordenada.begin(), fila_ordenada.end(), arr[i]);
        
        //obtenemos la cantidad de pasos hacia atras que se deben dar.
        cantidad_pasos += distance(pos, fila_ordenada.end());

        //Insertamos al niño en la posición deseada.
        fila_ordenada.insert(pos, arr[i]);
    }

    //Retornamos la cantidad de pasos que se dieron.
    return cantidad_pasos;
}

int main()
{
    //------------------Inicializacion---------------------------
    // Optimización para que cin/cout sean mucho más rápidos
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //Creacion de variables iniciales
    int p;

    //-----------------
}
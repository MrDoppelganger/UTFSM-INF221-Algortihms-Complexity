//----------------Librerias--------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
    ------------Funcion-----------------
    sincronizarListas: 
        Funcion encargada de ordenar la segunda lista
    para que coincida con el orden de las correspondencias
    de la primera lista.
    ------------Parametros----------------
    const vector<int>& lista1: Primera lista con el orden original.
    const vector<int>& lista2: Segunda lista desordenada.
    --------------Return------------------
    vector<int>: La segunda lista reordenada segun la correspondencia.
    ----------------------------------
*/
vector<int> sincronizarListas(const vector<int>& lista1, const vector<int>& lista2)
{
    int n = lista1.size();
    
    // Creamos copias para poder ordenarlas sin perder el orden original
    vector<int> lista1_ordenada = lista1;
    vector<int> lista2_ordenada = lista2;
    
    sort(lista1_ordenada.begin(), lista1_ordenada.end());
    sort(lista2_ordenada.begin(), lista2_ordenada.end());
    
    // Mapa para guardar la correspondencia: valor_lista1 -> valor_lista2
    // unordered_map es muy eficiente (O(1)) para buscar valores asociados.
    unordered_map<int, int> correspondencia;
    
    for (int i = 0; i < n; i++)
    {
        // El elemento i-esimo mas pequeño de la lista 1 corresponde
        // al elemento i-esimo mas pequeño de la lista 2.
        correspondencia[lista1_ordenada[i]] = lista2_ordenada[i];
    }
    
    // Creamos la lista resultante aplicando el mapa al orden original de lista1
    vector<int> resultado(n);
    for (int i = 0; i < n; i++)
    {
        resultado[i] = correspondencia[lista1[i]];
    }
    
    return resultado;
}

int main()
{
    //------------------Inicializacion---------------------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    bool primer_caso = true;

    //------------------Lectura de Datos-------------------------
    // El programa debe terminar cuando n sea igual a 0.
    while (cin >> n && n != 0)
    {
        // El formato de salida pide una linea en blanco ENTRE las listas resultantes
        if (!primer_caso)
        {
            cout << "\n";
        }
        primer_caso = false;

        vector<int> lista1(n);
        for (int i = 0; i < n; i++)
        {
            cin >> lista1[i];
        }

        vector<int> lista2(n);
        for (int i = 0; i < n; i++)
        {
            cin >> lista2[i];
        }

        //------------------Procesamiento----------------------------
        vector<int> lista_sincronizada = sincronizarListas(lista1, lista2);

        //------------------Salida-----------------------------------
        for (int i = 0; i < n; i++)
        {
            cout << lista_sincronizada[i] << "\n";
        }
    }

    return 0;
}
//----------------Librerias--------------------
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    ------------Funcion-----------------
    isPrime: 
        Verifica de manera eficiente si un numero 
    es primo.
    ------------Parametros----------------
    int n: Numero a evaluar.
    --------------Return------------------
    bool: True si es primo, False en caso contrario.
    ----------------------------------
*/
bool isPrime(int n) 
{
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) 
    {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

/*
    ------------Funcion-----------------
    precomputarLosingStates: 
        Calcula todos los estados perdedores (L) 
    hasta el N maximo consultado, evaluando los 
    caminos posibles (concepto de backtracking).
    ------------Parametros----------------
    int max_n: El valor maximo de N entre todos los testcases.
    --------------Return------------------
    vector<int>: Lista de estados perdedores ordenados.
    ----------------------------------
*/
vector<int> precomputarLosingStates(int max_n)
{
    vector<int> L;
    L.push_back(0);
    L.push_back(3); // Conocemos los primeros dos estados perdedores

    for (int i = 4; i <= max_n; i++)
    {
        // Optimizacion: Si N % 4 es 1 o 2, matematicamente SIEMPRE 
        // pueden llegar a un estado perdedor. (No necesitamos explorarlos).
        if (i % 4 == 1 || i % 4 == 2) continue;

        bool puede_ganar = false;
        
        // Simulamos las ramas del arbol (backtracking) hacia estados previos.
        // Un movimiento valido es 'p - 1', asi que la distancia debe ser 'p - 1'.
        // Esto equivale a verificar si (distancia + 1) es un numero primo.
        for (int j = (int)L.size() - 1; j >= 0; j--)
        {
            int distancia = i - L[j];
            if (isPrime(distancia + 1))
            {
                puede_ganar = true; // Encontramos un camino a un estado perdedor
                break;              // Podamos esta rama
            }
        }

        // Si no encontro ningun camino hacia un estado perdedor, este mismo es perdedor
        if (!puede_ganar)
        {
            L.push_back(i);
        }
    }
    return L;
}

int main()
{
    //------------------Inicializacion---------------------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;

    //------------------Lectura de Datos-------------------------
    if (!(cin >> q)) return 0;

    vector<int> consultas(q);
    int max_n = 0;

    for (int i = 0; i < q; i++)
    {
        cin >> consultas[i];
        if (consultas[i] > max_n)
        {
            max_n = consultas[i];
        }
    }

    //------------------Procesamiento----------------------------
    // Precomputamos los estados solo hasta el N mas grande solicitado
    // para no gastar tiempo en numeros innecesarios.
    vector<int> losing_states = precomputarLosingStates(max_n);

    //------------------Salida-----------------------------------
    for (int i = 0; i < q; i++)
    {
        int n = consultas[i];
        
        // Si el estado inicial N es un estado perdedor, Bob gana (ya que Alice tira primero).
        // Usamos busqueda binaria (binary_search) para verificarlo rapidisimo en O(log M).
        if (binary_search(losing_states.begin(), losing_states.end(), n))
        {
            cout << "Bob\n";
        }
        else
        {
            cout << "Alice\n";
        }
    }

    return 0;
}
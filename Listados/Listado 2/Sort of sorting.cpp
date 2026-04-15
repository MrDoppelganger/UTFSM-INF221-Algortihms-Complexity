//----------------Librerias--------------------
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/*
    ------------Funcion-----------------
    compararDosLetras: 
        Funcion de comparacion personalizada que solo 
    toma en cuenta los primeros dos caracteres.
    ------------Parametros----------------
    const string& a: Primer apellido a comparar.
    const string& b: Segundo apellido a comparar.
    --------------Return------------------
    bool: True si las primeras dos letras de 'a' son
    menores a las de 'b' en orden ASCII.
    ----------------------------------
*/
bool compararDosLetras(const string& a, const string& b)
{
    // Comparamos el prefijo de longitud 2 de cada string
    return a.substr(0, 2) < b.substr(0, 2);
}

/*
    ------------Funcion-----------------
    ordenarApellidos: 
        Funcion encargada de aplicar un ordenamiento 
    estable basado en las primeras dos letras.
    ------------Parametros----------------
    vector<string>& lista: Referencia al vector de nombres.
    --------------Return------------------
    void: Modifica el vector original.
    ----------------------------------
*/
void ordenarApellidos(vector<string>& lista)
{
    // Usamos stable_sort para garantizar que si los criterios 
    // de comparacion son iguales, se mantenga el orden de entrada.
    stable_sort(lista.begin(), lista.end(), compararDosLetras);
}

int main()
{
    //------------------Inicializacion---------------------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    bool primer_caso = true;

    //------------------Lectura de Datos-------------------------
    // El programa termina cuando n es 0.
    while (cin >> n && n != 0)
    {
        // El problema pide una linea en blanco ENTRE casos.
        if (!primer_caso)
        {
            cout << "\n";
        }
        primer_caso = false;

        vector<string> apellidos(n);
        for (int i = 0; i < n; i++)
        {
            cin >> apellidos[i];
        }

        //------------------Procesamiento----------------------------
        ordenarApellidos(apellidos);

        //------------------Salida-----------------------------------
        for (int i = 0; i < n; i++)
        {
            cout << apellidos[i] << "\n";
        }
    }

    return 0;
}
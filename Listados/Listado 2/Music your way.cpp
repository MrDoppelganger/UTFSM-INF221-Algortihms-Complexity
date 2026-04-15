//----------------Librerias--------------------
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

/*
    ------------Funcion-----------------
    obtenerIndiceAtributo: 
        Busca la posicion (columna) de un atributo especifico 
    dentro de la lista de atributos.
    ------------Parametros----------------
    const vector<string>& atributos: Vector con los nombres de las columnas.
    const string& comando: Nombre del atributo que se desea buscar.
    --------------Return------------------
    int: Devuelve el indice del atributo (0, 1, 2...). 
    Retorna -1 si no se encuentra (aunque el problema garantiza que existira).
    ----------------------------------
*/
int obtenerIndiceAtributo(const vector<string>& atributos, const string& comando)
{
    for (int i = 0; i < atributos.size(); i++)
    {
        if (atributos[i] == comando)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    //------------------Inicializacion---------------------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string linea_inicial;

    //------------------Lectura de Datos-------------------------
    // Leemos la primera linea completa para obtener los atributos
    if (!getline(cin, linea_inicial)) return 0;

    vector<string> atributos;
    stringstream ss(linea_inicial);
    string atributo;
    
    // Separamos la linea por espacios para guardar cada atributo
    while (ss >> atributo)
    {
        atributos.push_back(atributo);
    }
    
    int cantidad_columnas = atributos.size();
    int m; // Cantidad de canciones
    cin >> m;

    // Creamos una matriz (vector de vectores) para guardar las canciones.
    // Cada cancion es un vector de strings que representa una fila.
    vector<vector<string>> canciones(m, vector<string>(cantidad_columnas));

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < cantidad_columnas; j++)
        {
            cin >> canciones[i][j];
        }
    }

    int n; // Cantidad de comandos de ordenamiento
    cin >> n;

    //------------------Procesamiento y Salida-------------------
    for (int i = 0; i < n; i++)
    {
        string comando;
        cin >> comando;

        int indice_columna = obtenerIndiceAtributo(atributos, comando);

        // Usamos una funcion Lambda para comparar dinamicamente la columna deseada.
        // El [indice_columna] permite que la funcion "capture" esa variable.
        stable_sort(canciones.begin(), canciones.end(), 
            [indice_columna](const vector<string>& a, const vector<string>& b) 
            {
                return a[indice_columna] < b[indice_columna];
            }
        );

        // Imprimimos la linea en blanco solo ENTRE las listas (no antes de la primera)
        if (i > 0)
        {
            cout << "\n";
        }

        // Imprimimos los encabezados (atributos)
        for (int j = 0; j < cantidad_columnas; j++)
        {
            cout << atributos[j] << (j == cantidad_columnas - 1 ? "" : " ");
        }
        cout << "\n";

        // Imprimimos la matriz de canciones ordenada
        for (int f = 0; f < m; f++)
        {
            for (int c = 0; c < cantidad_columnas; c++)
            {
                cout << canciones[f][c] << (c == cantidad_columnas - 1 ? "" : " ");
            }
            cout << "\n";
        }
    }

    return 0;
}
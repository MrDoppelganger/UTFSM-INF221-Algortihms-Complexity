//----------------Librerias--------------------
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

/*
    ------------Funcion-----------------
    generarPinturas: 
        Funcion recursiva (Backtracking) que genera todas las 
    combinaciones validas de colores, contando el total y 
    guardando la primera (que por el orden de exploracion, 
    sera la favorita de Catherine).
    ------------Parametros----------------
    int N: Cantidad total de colores.
    const vector<vector<bool>>& adyacencias_malas: Matriz de restricciones.
    vector<bool>& usados: Arreglo para saber que color ya usamos.
    vector<int>& actual: La pintura que estamos construyendo.
    int& total_validas: Contador de pinturas correctas encontradas.
    vector<int>& favorita: Guarda la primera pintura valida encontrada.
    --------------Return------------------
    void: Explora los caminos y modifica las variables por referencia.
    ----------------------------------
*/
void generarPinturas(int N, const vector<vector<bool>>& adyacencias_malas, vector<bool>& usados, vector<int>& actual, int& total_validas, vector<int>& favorita)
{
    // Caso Base: Hemos colocado los N colores exitosamente.
    if (actual.size() == N)
    {
        total_validas++;
        
        // Si la pintura favorita esta vacia, significa que esta es la PRIMERA
        // pintura valida que encontramos. Como exploramos los colores en orden 
        // de preferencia, esta es garantizadamente la favorita.
        if (favorita.empty())
        {
            favorita = actual;
        }
        return;
    }

    // Backtracking: Intentamos colocar cada color disponible.
    // El bucle va de 0 a N-1. Como el color 0 es el mas preferido,
    // estamos aplicando una eleccion Greedy dentro del Backtracking.
    for (int i = 0; i < N; i++)
    {
        if (!usados[i])
        {
            // PODA: Verificamos la restriccion de adyacencia.
            // Si ya hay colores puestos, el ultimo color puesto no debe
            // ser incompatible con el color 'i' que queremos poner.
            if (!actual.empty() && adyacencias_malas[actual.back()][i])
            {
                continue; // Si son incompatibles, podamos esta rama y probamos otro color
            }

            // 1. ELEGIR
            usados[i] = true;
            actual.push_back(i);

            // 2. EXPLORAR
            generarPinturas(N, adyacencias_malas, usados, actual, total_validas, favorita);

            // 3. DESHACER (Backtrack)
            actual.pop_back();
            usados[i] = false;
        }
    }
}

int main()
{
    //------------------Inicializacion---------------------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;

    //------------------Lectura de Datos-------------------------
    if (!(cin >> t)) return 0;

    for (int caso = 0; caso < t; caso++)
    {
        int n;
        cin >> n;

        // Mapas para traducir entre el nombre del color (string) y un ID (int).
        // El ID 0 sera el mas preferido, el ID N-1 el menos preferido.
        unordered_map<string, int> color_a_id;
        vector<string> id_a_color(n);

        for (int i = 0; i < n; i++)
        {
            string color;
            cin >> color;
            color_a_id[color] = i;
            id_a_color[i] = color;
        }

        int m;
        cin >> m;

        // Matriz booleana para busquedas de O(1) al validar restricciones
        vector<vector<bool>> adyacencias_malas(n, vector<bool>(n, false));

        for (int i = 0; i < m; i++)
        {
            string c1, c2;
            cin >> c1 >> c2;
            int id1 = color_a_id[c1];
            int id2 = color_a_id[c2];
            
            // La restriccion es bidireccional
            adyacencias_malas[id1][id2] = true;
            adyacencias_malas[id2][id1] = true;
        }

        //------------------Procesamiento----------------------------
        vector<bool> usados(n, false);
        vector<int> combinacion_actual;
        vector<int> pintura_favorita;
        int total_pinturas = 0;

        generarPinturas(n, adyacencias_malas, usados, combinacion_actual, total_pinturas, pintura_favorita);

        //------------------Salida-----------------------------------
        cout << total_pinturas << "\n";
        
        for (int i = 0; i < n; i++)
        {
            cout << id_a_color[pintura_favorita[i]] << (i == n - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}
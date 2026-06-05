//----------------------Librerias--------------------
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    //------------------Inicializacion-----------------
    //Trucazo
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //Guardamos los tamaños de los arreglos
    int n,m;
    cin >> n >> m;

    //Creamos las Listas que almacenaran la información del problema
    vector<int> tareas(n), ventanas(m);  
    for(int i = 0; i < n; i++)
    {
        cin >> tareas[i];
    }
    for(int i = 0; i < m; i++)
    {
        cin >> ventanas[i];
    }
    //ordenamos ambos arreglos
    sort(tareas.begin(), tareas.end());
    sort(ventanas.begin(), ventanas.end());
    //------------------------Algoritmo-----------------
    int tareas_ptr = 0;     // Puntero para las tareas
    int ventanas_ptr = 0;   // Puntero para las ventanas
    int checks = 0;         //Numero de tareas cumpletadas

   // iteramos mientras tengamos tareas o ventanas con la que poder trabajar
    while (tareas_ptr < n && ventanas_ptr < m) {
        // Revisamos si la tarea actual cabe en la inicial
        if (tareas[tareas_ptr] <= ventanas[ventanas_ptr]) {
            checks++;
            tareas_ptr++;  // Pasamos a la siguiente tarea
            ventanas_ptr++;  // Esta ventana ya fue utilizada
        } else {
            //si no cabe la tarea en esta ventana, ninguna lo hara, asi que descartamos
            ventanas_ptr++;
        }
    }
    //entregamos el resultado de tareas completadas:
    cout << checks << "\n";

    return 0;
}
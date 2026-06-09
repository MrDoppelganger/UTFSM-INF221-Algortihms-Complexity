//-------------------Librerias--------------------
#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int main()
{
    //------------------Inicialización------------------
    //Trucazo
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    //Recibimos los valores de n y m
    int n, m;
    if (!(cin >> n >> m)) return 0;

    //Creamos una cola de prioridad que nos almacena las tareas en bloques pair dentro de un min-heap
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> tareas;
    
    for(int i = 0; i < n; i++)
    {
        int llegada, duracion;
        cin >> llegada >> duracion;
        tareas.push({llegada, duracion});
    }

    //Cola de prioridad para llevar el registro de las máquinas que se van desocupando.
    priority_queue<int, vector<int>, greater<int>> maquinas_libres;

    //Contador final
    int ahorros = 0;       

    //------------------Algoritmo-----------------------
    //Procesamos directamente investigador por investigador
    while(!tareas.empty())
    {
        //sacamos al investigador que vamos a revisar
        pair<int, int> trabajo_pc = tareas.top();
        tareas.pop();    
        
        int llegada = trabajo_pc.first;
        int duracion = trabajo_pc.second;

        // Si la máquina que lleva más tiempo libre ya superó los 'm' minutos de inactividad, se bloqueó. limpieza de maquinas
        while(!maquinas_libres.empty())
        {
            int tiempo_libre = maquinas_libres.top();
            
            if((llegada - tiempo_libre) > m) 
            {
                // Pasaron más de m minutos, la descartamos
                maquinas_libres.pop();
            }
            else
            {
                // Al ser un min-heap, si la más antigua no ha expirado, las demás que se liberaron después tampoco.
                break;
            }
        }

        // Revisamos si queda al menos una máquina libre que se haya desocupado ANTES o IGUAL a la llegada
        if(!maquinas_libres.empty() && maquinas_libres.top() <= llegada)
        {
            // en caso de que haya maquina libre, osamos la máquina que se desocupó primero y ahorramos un desbloqueo
            ahorros++;
            maquinas_libres.pop(); // La sacamos porque este investigador la ocupará
        }
        //El investigador actual dejará su máquina libre en el futuro, la agregamos al registro
        int tiempo_salida = llegada + duracion;
        maquinas_libres.push(tiempo_salida);
    }

    //------------------Salida-----------------------
    // Al final retornamos la cantidad de desbloqueos que se lograron ahorrar
    cout << ahorros << "\n";

    return 0;
}
//---------------------------------Librerias-------------------------------------
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
    -----------------Struct---------------------
    Clase Arista:
       Clase estructural para guardar la información de las aristas
    Parametros:
        int origen: Nodo de origen de la arista.
        int destino: Nodo de destino de la arista.
        int peso: Peso de la arista.
    --------------------------------------------
 */
struct Arista {
    int origen;
    int destino;
    int peso;
};

/*
    ----------------Funcion-----------------
    propagarCicloNegativo: 
        Funcion encargada de realizar un BFS (Busqueda en Anchura) 
        para marcar todos los nodos que son alcanzables desde un 
        ciclo de peso negativo (ya que sus caminos pueden ser 
        infinitamente pequeños).
    ------------Parametros----------------
    queue<int>& cola: Cola con los nodos inicialmente detectados en un ciclo.
    const vector<vector<int>>& adyacencia: Lista de adyacencia del grafo.
    vector<bool>& en_ciclo_negativo: Arreglo booleano para marcar nodos.
    --------------Return------------------
    void: Modifica el arreglo directamente por referencia.
    ----------------------------------
*/
void propagarCicloNegativo(queue<int>& cola, const vector<vector<int>>& adyacencia, vector<bool>& en_ciclo_negativo)
{
    while (!cola.empty())
    {
        int u = cola.front();
        cola.pop();

        for (int v : adyacencia[u])
        {
            // Si el vecino aun no esta marcado, lo marcamos y lo metemos a la cola
            if (!en_ciclo_negativo[v])
            {
                en_ciclo_negativo[v] = true;
                cola.push(v);
            }
        }
    }
}

int main()
{
    //--------------------------------Inicializacion-----------------------------------------------
    // Trucazo
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //Establecemos un "infinito" practico
    const int INF = 1e9;
    int n, m, q, s;
    bool primer_caso = true;

    // Iteramos hasta toparnos con los 4 ceros 
    while (cin >> n >> m >> q >> s && (n != 0 || m != 0 || q != 0 || s != 0))
    {
        // colocamos un espacio entremedio de cada iteracion
        if (!primer_caso) cout << "\n";
        primer_caso = false;

        vector<Arista> aristas(m);
        // Lista de adyacencia normal, la usaremos despues para el BFS
        vector<vector<int>> adyacencia(n);

        //Sacamos la informacion del problema
        for (int i = 0; i < m; i++)
        {
            cin >> aristas[i].origen >> aristas[i].destino >> aristas[i].peso;
            adyacencia[aristas[i].origen].push_back(aristas[i].destino);
        }

        //-----------------------------Algoritmo-------------------------------------
        vector<int> dist(n, INF);
        dist[s] = 0;

        // Aplicamos bellman-ford relajando n-1 veces
        for (int i = 0; i < n - 1; i++)
        {
            for (const auto& arista : aristas)
            {
                // Si el nodo de origen es alcanzable y encontramos un camino mas corto
                if (dist[arista.origen] != INF && dist[arista.origen] + arista.peso < dist[arista.destino])
                {
                    dist[arista.destino] = dist[arista.origen] + arista.peso;
                }
            }
        } 
        //Hacemos la iteracion extra para detectar ciclos negativos
        vector<bool> en_ciclo_negativo(n, false);
        queue<int> cola;

        for (const auto& arista : aristas)
        {
            if (dist[arista.origen] != INF && dist[arista.origen] + arista.peso < dist[arista.destino])
            {
                if (!en_ciclo_negativo[arista.destino])
                {
                    en_ciclo_negativo[arista.destino] = true;
                    cola.push(arista.destino); // Lo guardamos para propagar el efecto
                }
            }
        }

        // Propagamos el efecto del ciclo negativo a todos los nodos alcanzables
        propagarCicloNegativo(cola, adyacencia, en_ciclo_negativo);

        //------------------Salida-----------------------------------
        for (int i = 0; i < q; i++)
        {
            int destino;
            cin >> destino;

            if (dist[destino] == INF)
            {
                cout << "Impossible\n";
            }
            else if (en_ciclo_negativo[destino])
            {
                cout << "-Infinity\n";
            }
            else
            {
                cout << dist[destino] << "\n";
            }
        }
    }

    return 0;
}
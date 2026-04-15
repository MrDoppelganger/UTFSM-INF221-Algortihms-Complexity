//----------------Librerias--------------------
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    ------------Funcion-----------------
    calcularDesperdicio: 
        Calcula la cantidad total de microlitros de 
    pintura desperdiciada al comprar la lata mas 
    pequeña posible que satisfaga cada requerimiento.
    ------------Parametros----------------
    const vector<long long>& latas: Tamaños de latas disponibles (ordenadas).
    const vector<long long>& requerimientos: Cantidad necesaria por color.
    --------------Return------------------
    long long: El total de pintura desperdiciada.
    ----------------------------------
*/
long long calcularDesperdicio(const vector<long long>& latas, const vector<long long>& requerimientos)
{
    // Usamos long long para evitar desbordamiento (Overflow)
    long long desperdicio_total = 0;

    for (int i = 0; i < requerimientos.size(); i++)
    {
        // lower_bound usa busqueda binaria para encontrar el PRIMER 
        // elemento que sea MAYOR O IGUAL al valor buscado.
        auto it = lower_bound(latas.begin(), latas.end(), requerimientos[i]);

        // El problema garantiza que siempre habra una lata lo suficientemente grande,
        // por lo que 'it' siempre apuntara a un valor valido.
        long long tamaño_comprado = *it;
        
        // Sumamos lo que sobra al total
        desperdicio_total += (tamaño_comprado - requerimientos[i]);
    }

    return desperdicio_total;
}

int main()
{
    //------------------Inicializacion---------------------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;

    //------------------Lectura de Datos-------------------------
    if (!(cin >> n >> m)) return 0;

    // Usamos long long para los tamaños y requerimientos
    vector<long long> tamaños_latas(n);
    for (int i = 0; i < n; i++)
    {
        cin >> tamaños_latas[i];
    }

    vector<long long> colores_necesitados(m);
    for (int i = 0; i < m; i++)
    {
        cin >> colores_necesitados[i];
    }

    //------------------Procesamiento----------------------------
    // ORDENAMOS los tamaños de las latas de menor a mayor.
    // Esto es un requisito estricto para poder usar lower_bound despues.
    sort(tamaños_latas.begin(), tamaños_latas.end());

    long long desperdicio = calcularDesperdicio(tamaños_latas, colores_necesitados);

    //------------------Salida-----------------------------------
    cout << desperdicio << "\n";

    return 0;
}
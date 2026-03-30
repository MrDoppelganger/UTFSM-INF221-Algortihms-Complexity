//-----------------Librerias----------------
#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

//----------------Estructuras de datos------------------
// Creamos una estructura para almacenar la cantidad y el precio de una orden
struct Orden {
    int precio;
    int acciones;
};

// Comparador para el Max-Heap (Compradores: el mayor precio tiene prioridad)
struct Comparador_Compra {
    bool operator()(const Orden& a, const Orden& b) {
        return a.precio < b.precio;
    }
};

// Comparador para el Min-Heap (Vendedores: el menor precio tiene prioridad)
struct Comparador_Venta {
    bool operator()(const Orden& a, const Orden& b) {
        return a.precio > b.precio;
    }
};

/*
    ------------Funcion-----------------
    gestor_bolsa: 
        Funcion encargada de leer las ordenes de compra y venta,
        almacenarlas en colas de prioridad (Heaps) y procesar
        los tratos (matches) en tiempo real para obtener los
        precios de ask, bid y stock tras cada movimiento.
    ------------Parametros----------------
    None:
    --------------Return------------------
    None:
    ----------------------------------
*/
void gestor_bolsa()
{
    //----------------Inicialización de datos------------------
    int numero_ordenes;
    if (!(cin >> numero_ordenes)) return;

    // Colas de prioridad para manejar el libro de órdenes eficientemente
    priority_queue<Orden, vector<Orden>, Comparador_Compra> compradores; // Max-Heap
    priority_queue<Orden, vector<Orden>, Comparador_Venta> vendedores;   // Min-Heap

    // Variables persistentes durante el caso de prueba para almacenar el estado
    int stock_price = -1; // -1 representará que aún no hay tratos ("-")

    //---------------Algoritmo de ejecución---------------------
    for (int i = 0; i < numero_ordenes; i++)
    {
        // Variables para leer la línea: "order_type x shares at y"
        string tipo_orden, ignorar_shares, ignorar_at;
        int cantidad_acciones, precio_deseado;

        cin >> tipo_orden >> cantidad_acciones >> ignorar_shares >> ignorar_at >> precio_deseado;

        // Creamos la orden actual
        Orden orden_actual = {precio_deseado, cantidad_acciones};

        // Ingresamos la orden al Heap correspondiente
        if (tipo_orden == "buy")
        {
            compradores.push(orden_actual);
        }
        else if (tipo_orden == "sell")
        {
            vendedores.push(orden_actual);
        }

        // --- Proceso de Emparejamiento (Match) ---
        // Verificamos si hay trato: necesitamos un comprador, un vendedor, y que el precio de compra sea >= al de venta
        while (!compradores.empty() && !vendedores.empty() && 
               compradores.top().precio >= vendedores.top().precio)
        {
            // Extraemos a los mejores candidatos de ambas colas
            Orden mejor_comprador = compradores.top();
            Orden mejor_vendedor = vendedores.top();

            // Los sacamos temporalmente para actualizar sus cantidades
            compradores.pop();
            vendedores.pop();

            // La cantidad del trato es el mínimo entre lo que pide el comprador y lo que ofrece el vendedor
            int acciones_intercambiadas = min(mejor_comprador.acciones, mejor_vendedor.acciones);

            // El precio del trato SIEMPRE es el precio de venta (ask price), según las reglas del problema
            stock_price = mejor_vendedor.precio;

            // Restamos las acciones intercambiadas
            mejor_comprador.acciones -= acciones_intercambiadas;
            mejor_vendedor.acciones -= acciones_intercambiadas;

            // Si a alguno le sobraron acciones, lo regresamos a su Heap
            if (mejor_comprador.acciones > 0)
            {
                compradores.push(mejor_comprador);
            }
            if (mejor_vendedor.acciones > 0)
            {
                vendedores.push(mejor_vendedor);
            }
        }

        //---------------Impresión de resultados---------------------
        // Determinamos el Ask Price (menor vendedor)
        if (vendedores.empty()) {
            cout << "- ";
        } else {
            cout << vendedores.top().precio << " ";
        }

        // Determinamos el Bid Price (mayor comprador)
        if (compradores.empty()) {
            cout << "- ";
        } else {
            cout << compradores.top().precio << " ";
        }

        // Determinamos el Stock Price (último trato)
        if (stock_price == -1) {
            cout << "-\n";
        } else {
            cout << stock_price << "\n";
        }
    }
}

int main() 
{
    // ----------Optimizador para la consola---------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //------------Lectura de casos de prueba-------------------
    int casos_prueba;
    if (cin >> casos_prueba) 
    {
        while (casos_prueba--) 
        {
            gestor_bolsa();
        }
    }
    return 0;
}
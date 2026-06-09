//-------------------------------------Librerias------------------------------
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

int main()
{
    //------------------------------Inicializacion------------------------------
    //Trucazo
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //Guardamos los datos(el ratio T y la cantidad de verduras N)
    double t;
    int n;
    cin >> t >> n;

    vector<double> pesos(n);            //Creamos la lista que almacenara los pesos originales
    vector<int> pedazos(n, 1);          //Vector para llevar la cuenta de en cuantas partes hemos dividido cada verdura
    double min_actual = 1000000000.0;   //Variable para el peso minimo actual (lo iniciamos en un numero gigante)

    //Guardamos en un max heap todo los pedazos en un pair con el peso actual y el indice original
    priority_queue<pair<double, int>> verduras_max;

    //iteramos para guardar todo los ratos que quedan
    for(int i = 0; i < n; i++)
    {
        cin >> pesos[i];
        verduras_max.push({pesos[i], i});
        
        //Aprovechamos de encontrar el pedazo mas chico inicial
        min_actual = min(min_actual, pesos[i]); 
    }

    //------------------------Algorimto-----------------
    //Contador para los cortes totales
    int cortes_totales = 0;

    // iteramos mientras la razon entre el mas chico y el mas grande sea menor o igual a T
    while((min_actual / verduras_max.top().first) <= t)
    {
        //Sacamos al gordito de la queue
        pair<double, int> mas_pesado = verduras_max.top();
        verduras_max.pop();
        int indice = mas_pesado.second;
        
        //Cortamos este pedazo aumentando en 1 sus divisiones
        pedazos[indice]++;
        cortes_totales++;

        //Calculamos el nuevo peso de los pedacitos de esa verdura
        double nuevo_peso = pesos[indice] / pedazos[indice];
        //Actualizamos el minimo por si este nuevo pedacito quedo mas chico que el minimo que ya teniamos
        min_actual = min(min_actual, nuevo_peso);
        //Metemos de vuelta la verdura al heap pero con su nuevo peso
        verduras_max.push({nuevo_peso, indice});
    }

    //Entregamos el resultado de cuantos cortes se necesitaron:
    cout << cortes_totales << "\n";

    return 0;
}
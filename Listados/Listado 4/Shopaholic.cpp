//-----------------------------Librerias-----------------------
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    //-----------------------Inicializacion-----------------------
    //Trucazo
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //Guardamos la cantidad de articulos que va a comprar
    int n;
    if (!(cin >> n)) return 0;

    //Creamos la lista que almacenara los precios de cada cosa
    vector<int> precios(n);  
    for(int i = 0; i < n; i++)
    {
        cin >> precios[i];
    }

    //Ordenamos la lista de precios de mayor a menor
    sort(precios.begin(), precios.end(), greater<int>());

    //------------------------Algorimto-----------------
    //Variable para acumular el descuento maximo (long long por si rebalsamos)
    long long descuento = 0;

    //Iteramos desde el tercer elemento y asi vamos saltando por que son los con descuentos
    for(int i = 2; i < n; i += 3)
    {
        descuento += precios[i];
    }

    //entregamos el resultado de lo que logramos aorrar:
    cout << descuento << "\n";

    return 0;
}
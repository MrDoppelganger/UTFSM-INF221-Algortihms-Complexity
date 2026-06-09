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

    //Guardamos los datos del problema (longitud, distancia minima, numero de pajaros)
    int l, d, n;
    if (!(cin >> l >> d >> n)) return 0;

    //Si el cable es muy corto (menos de 6cm por lado), no cabe ni un pajaro, abortamos
    if (l < 12) {
        cout << 0 << "\n";
        return 0;
    }

    //Creamos la Lista que almacenara las posiciones de los pajaros actuales
    vector<int> pajaros(n);  
    for(int i = 0; i < n; i++)
    {
        cin >> pajaros[i];
    }

    //Ordenamos el arreglo para procesarlos de izquierda a derecha
    sort(pajaros.begin(), pajaros.end());

    //------------------------Algoritmo-----------------
    //Numero de pajaros adicionales que podemos meter
    int nuevos = 0;

    //Caso 1: El cable esta vacio, podemos usar todo el espacio disponible
    if (n == 0) 
    {
        //Calculamos el espacio real (le quitamos 6cm de cada lado) y lo dividimos en bloques de 'd'
        nuevos = ((l - 12) / d) + 1;
    }
    //Caso 2: Ya hay pajaros. Calculamos los espacios libres por partes.
    else 
    {
        //Tramo 1 Desde el poste izquierdo hasta el primer pajaro
        nuevos += (pajaros[0] - 6) / d;

        //Tramo 2 Los huecos entre los pajaros ya sentados
        for(int i = 1; i < n; i++)
        {
            //Vemos la distancia entre el pajaro actual y el anterior y le restamos 1 
            nuevos += ((pajaros[i] - pajaros[i - 1]) / d) - 1;
        }

        //Tramo 3 Desde el ultimo pajaro hasta el poste derecho (l - 6)
        nuevos += (l - 6 - pajaros[n - 1]) / d;
    }

    //entregamos el resultado de pajaros nuevos que caben:
    cout << nuevos << "\n";

    return 0;
}
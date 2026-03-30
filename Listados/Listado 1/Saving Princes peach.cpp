//-----------------Librerias---------------
#include <iostream>
#include <set>

using namespace std;

int main()
{
    //----------Inicialización-------------
    //optimizacion de la consola
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //Creamos las variables iniciales para almacenar los datos.
    int obstaculos_totales, obstaculos_mario;
    if(!(cin >> obstaculos_totales >> obstaculos_mario)) return 0;

    //Creamos nuestro Set, para mantener ordenado e irrepetible los obstaculos que se registraron.
    set<int> registro;

    //---------------Algoritmo--------------
    //Iteramos guardando cada uno de los obstaculos visto por mario
    for(int i = 0; i < obstaculos_mario; i++)
    {
        int registro_prima;
        if(!(cin >> registro_prima)) return 0; 

        //insertamos a nuestro set.
        registro.insert(registro_prima);
    }

    //ahora realizamos un print de todo los obstaculos que se salto mario
    for(int i = 0; i < obstaculos_totales; i++)
    {
        //Comprobamos que el valor no haya sido registrado por mario.
        if(registro.count(i) == 0)
        {
            cout << i << "\n";
        }
    }
    //E imprimimos el mensaje final usando el tamaño de nuestro set
    cout << "Mario got " << registro.size() << " of the dangerous obstacles.";

    return 0;
}
//----------------Librerias--------------------
#include <iostream>
#include <vector>

using namespace std;

/*
    ------------Funcion-----------------
    descifrarByte: 
        Utiliza Fuerza Bruta para encontrar el byte original. 
    Prueba todos los valores posibles (0-255), los cifra y 
    comprueba cual coincide con el byte recibido.
    ------------Parametros----------------
    int byte_recibido: El valor del byte ya "desordenado" (cifrado).
    --------------Return------------------
    int: El valor del byte original (descifrado).
    ----------------------------------
*/
int descifrarByte(int byte_recibido)
{
    // Fuerza Bruta: El dominio de un byte es pequeñisimo (0 a 255).
    // Probamos cada uno de los valores posibles.
    for (int x = 0; x <= 255; x++)
    {
        // Aplicamos la ecuacion del problema: x ^ (x << 1)
        int intento_cifrado = (x ^ (x << 1)) & 255;

        // Si el resultado de cifrar 'x' nos da exactamente el byte que recibimos...
        // ¡Encontramos el byte original!
        if (intento_cifrado == byte_recibido)
        {
            return x;
        }
    }
    
    // Por seguridad, aunque el problema garantiza que habra solucion.
    return 0; 
}

int main()
{
    //------------------Inicializacion---------------------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    //------------------Lectura de Datos-------------------------
    if (!(cin >> n)) return 0;

    vector<int> mensaje_cifrado(n);
    for (int i = 0; i < n; i++)
    {
        cin >> mensaje_cifrado[i];
    }

    //------------------Procesamiento y Salida-------------------
    // En este caso, podemos procesar e imprimir en el mismo ciclo
    // para ahorrar memoria y tiempo.
    for (int i = 0; i < n; i++)
    {
        int byte_original = descifrarByte(mensaje_cifrado[i]);
        
        // Imprimimos el resultado con un espacio de separacion
        cout << byte_original << (i == n - 1 ? "" : " ");
    }
    
    // Un salto de linea final por buenas practicas de consola
    cout << "\n";

    return 0;
}
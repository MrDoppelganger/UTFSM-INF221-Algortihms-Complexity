//-----------------Librerias----------------
#include <iostream>
#include <string>
#include <deque>

using namespace std;

/*
    ------------Funcion-----------------
    interprete_bapc: 
        Funcion encargada de leer el programa BAPC, el arreglo
        inicial en formato string y procesar las instrucciones 
        'R' y 'D' de forma eficiente usando un deque y un 
        indicador de reversa para evitar mover datos físicos.
    ------------Parametros----------------
    None:
    --------------Return------------------
    None:
    ----------------------------------
*/
void interprete_bapc()
{
    //----------------Inicialización de datos------------------
    // Leemos las instrucciones del programa (Ej: "RDD")
    string programa;
    if(!(cin >> programa)) return;

    // Leemos la cantidad de elementos (aunque no lo usaremos mucho gracias a la lectura dinámica)
    int n;
    cin >> n;

    // Leemos el arreglo crudo como un string (Ej: "[1,2,3]")
    string arreglo_str;
    cin >> arreglo_str;

    // Creamos nuestro deque para almacenar los números enteros
    deque<int> numeros;

    // Parseamos el string "[x1,x2,...,xn]" para extraer los enteros reales
    string numero_temporal = "";
    // Empezamos en i = 1 para saltarnos el corchete de apertura '['
    for (int i = 1; i < arreglo_str.length(); i++)
    {
        char caracter = arreglo_str[i];
        
        // Si es un digito, lo agregamos a nuestro numero temporal
        if (caracter >= '0' && caracter <= '9')
        {
            numero_temporal += caracter;
        }
        // Si encontramos una coma o el corchete de cierre ']', guardamos el numero completo
        else if (caracter == ',' || caracter == ']')
        {
            // Verificamos que no esté vacío (necesario para el caso especial "[]")
            if (!numero_temporal.empty())
            {
                // Convertimos el string a entero y lo metemos al deque
                numeros.push_back(stoi(numero_temporal));
                numero_temporal = ""; // Reiniciamos para el siguiente numero
            }
        }
    }

    //---------------Algoritmo de ejecución---------------------
    // Variable clave para controlar si el arreglo está invertido lógicamente
    bool reversa = false;

    // Procesamos cada instrucción de la cadena de comandos
    for (char instruccion : programa)
    {
        if (instruccion == 'R')
        {
            // Invertimos el estado lógico en O(1)
            reversa = !reversa;
        }
        else if (instruccion == 'D')
        {
            // Verificamos si la lista está vacía para lanzar el error
            if (numeros.empty())
            {
                cout << "error\n";
                return; // Terminamos la ejecución de este caso inmediatamente
            }
            
            // Si NO está invertida, la orden 'D' elimina el primer elemento real
            if (!reversa)
            {
                numeros.pop_front();
            }
            // Si está invertida, el "inicio" es en realidad el final actual
            else
            {
                numeros.pop_back();
            }
        }
    }

    //---------------Impresión de resultados---------------------
    // Construimos la salida final respetando el formato requerido "[x,y,z]"
    cout << "[";
    if (!numeros.empty())
    {
        if (!reversa)
        {
            // Imprimimos de inicio a fin normal
            for (auto it = numeros.begin(); it != numeros.end(); ++it)
            {
                cout << *it;
                // Agregamos la coma solo si NO es el último elemento
                if (next(it) != numeros.end()) cout << ",";
            }
        }
        else
        {
            // Imprimimos de fin a inicio (usando iteradores en reversa rbegin/rend)
            for (auto it = numeros.rbegin(); it != numeros.rend(); ++it)
            {
                cout << *it;
                if (next(it) != numeros.rend()) cout << ",";
            }
        }
    }
    cout << "]\n";
}

int main() 
{
    // ----------Optimizador para la consola---------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //------------Lectura de casos de prueba-------------------
    int casos;
    if (cin >> casos) 
    {
        while (casos--) 
        {
            interprete_bapc();
        }
    }
    return 0;
}
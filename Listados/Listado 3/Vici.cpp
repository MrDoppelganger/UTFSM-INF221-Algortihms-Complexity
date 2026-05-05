//----------------Librerias--------------------
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    ------------Funcion-----------------
    generarPermutaciones: 
        Funcion recursiva (Backtracking) que genera todas 
    las permutaciones posibles de los digitos intercambiandolos.
    ------------Parametros----------------
    string& actual: El string con los digitos actuales.
    int indice: El indice que estamos fijando en esta llamada recursiva.
    int valor_original: El valor numerico de X (para comparar).
    int& mejor_valor: Referencia para guardar el mejor resultado encontrado.
    --------------Return------------------
    void: Explora los caminos y modifica 'mejor_valor' por referencia.
    ----------------------------------
*/
void generarPermutaciones(string& actual, int indice, int valor_original, int& mejor_valor)
{
    // Caso Base: Si el indice llega al final, tenemos una permutacion completa.
    if (indice == actual.length())
    {
        // Convertimos el string a entero para comparar (stoi = string to int)
        int valor_actual = stoi(actual);

        // Si es mayor que el original, pero mas pequeño que nuestro record actual, lo actualizamos.
        if (valor_actual > valor_original && valor_actual < mejor_valor)
        {
            mejor_valor = valor_actual;
        }
        return;
    }

    // Backtracking: Probamos poner cada digito restante en la posicion 'indice'
    for (int i = indice; i < actual.length(); i++)
    {
        // 1. ELEGIR: Intercambiamos el digito en 'indice' con el digito en 'i'
        swap(actual[indice], actual[i]);

        // 2. EXPLORAR: Llamada recursiva para fijar el siguiente digito
        generarPermutaciones(actual, indice + 1, valor_original, mejor_valor);

        // 3. DESHACER (Backtrack): Devolvemos el string a su estado original 
        // para la siguiente iteracion del ciclo
        swap(actual[indice], actual[i]);
    }
}

int main()
{
    //------------------Inicializacion---------------------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string x;

    //------------------Lectura de Datos-------------------------
    if (!(cin >> x)) return 0;

    //------------------Procesamiento----------------------------
    int valor_original = stoi(x);
    
    // Inicializamos el mejor valor con un numero inalcanzable (infinito)
    int mejor_valor = 9999999; 

    // Iniciamos la recursion desde el indice 0
    generarPermutaciones(x, 0, valor_original, mejor_valor);

    //------------------Salida-----------------------------------
    // Si el mejor_valor nunca cambio, significa que no habia ningun numero mayor
    if (mejor_valor == 9999999)
    {
        cout << 0 << "\n";
    }
    else
    {
        cout << mejor_valor << "\n";
    }

    return 0;
}
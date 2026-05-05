//----------------Librerias--------------------
#include <iostream>
#include <string>
#include <stack>

using namespace std;

/*
    ------------Funcion-----------------
    evaluarWFF: 
        Evalua la formula logica para una combinacion
    especifica de valores de verdad.
    ------------Parametros----------------
    const string& formula: La formula en notacion prefija.
    int estado: Un entero de 0 a 31 cuyos bits representan 
                los valores de p, q, r, s, y t.
    --------------Return------------------
    bool: El resultado final de evaluar la formula.
    ----------------------------------
*/
bool evaluarWFF(const string& formula, int estado)
{
    stack<bool> pila;

    // Evaluamos la formula en notacion prefija de DERECHA a IZQUIERDA
    for (int i = formula.length() - 1; i >= 0; i--)
    {
        char c = formula[i];

        // Si es una variable, obtenemos su valor desde los bits del 'estado'
        if (c >= 'p' && c <= 't')
        {
            // 'p' es el bit 0, 'q' es el bit 1, ..., 't' es el bit 4
            int bit = c - 'p'; 
            bool valor_variable = (estado >> bit) & 1;
            pila.push(valor_variable);
        }
        // Si es el operador unario NOT
        else if (c == 'N')
        {
            bool w = pila.top(); 
            pila.pop();
            pila.push(!w);
        }
        // Si es un operador binario (K, A, C, E)
        else
        {
            // El primer elemento que sacamos es 'w' (izquierdo), 
            // el segundo es 'x' (derecho), gracias a que leemos al reves.
            bool w = pila.top(); pila.pop();
            bool x = pila.top(); pila.pop();

            if (c == 'K') // AND
            {
                pila.push(w && x);
            }
            else if (c == 'A') // OR
            {
                pila.push(w || x);
            }
            else if (c == 'C') // IMPLIES (w -> x es equivalente a !w || x)
            {
                pila.push(!w || x);
            }
            else if (c == 'E') // EQUALS (w == x)
            {
                pila.push(w == x);
            }
        }
    }

    // Al final, la pila debe contener exactamente 1 elemento: el resultado.
    return pila.top();
}

/*
    ------------Funcion-----------------
    esTautologia: 
        Verifica si la formula es verdadera para
    absolutamente todas las combinaciones posibles.
    ------------Parametros----------------
    const string& formula: La formula a evaluar.
    --------------Return------------------
    bool: True si es tautologia, False en caso contrario.
    ----------------------------------
*/
bool esTautologia(const string& formula)
{
    // Hay 5 variables (p, q, r, s, t), lo que da 2^5 = 32 estados posibles.
    for (int estado = 0; estado < 32; estado++)
    {
        // Si para algun estado la formula es falsa, ya no es tautologia.
        if (!evaluarWFF(formula, estado))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    //------------------Inicializacion---------------------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string entrada;

    //------------------Lectura de Datos y Procesamiento---------
    // Leemos hasta que nos den el "0" que indica el fin.
    while (cin >> entrada && entrada != "0")
    {
        //------------------Salida-----------------------------------
        if (esTautologia(entrada))
        {
            cout << "tautology\n";
        }
        else
        {
            cout << "not\n";
        }
    }

    return 0;
}
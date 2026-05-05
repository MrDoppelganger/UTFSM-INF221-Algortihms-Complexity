//----------------Librerias--------------------
#include <iostream>
#include <string>

using namespace std;

/*
    ------------Funcion-----------------
    contarPalabras: 
        Funcion recursiva (Backtracking) que explora todas 
    las combinaciones validas agrupando las letras en 3 
    categorias (Vocales, Consonantes sin L, y L).
    ------------Parametros----------------
    const string& s: La cadena de texto original.
    int index: La posicion actual que estamos analizando.
    int consec_vocales: Contador de vocales seguidas.
    int consec_consonantes: Contador de consonantes seguidas.
    bool tiene_L: Bandera que indica si ya pusimos una 'L'.
    --------------Return------------------
    long long: El total de palabras agradables que se pueden formar 
    desde el estado actual. (Usamos long long porque el numero crece mucho).
    ----------------------------------
*/
long long contarPalabras(const string& s, int index, int consec_vocales, int consec_consonantes, bool tiene_L)
{
    // 1. PODA (Pruning): Si rompemos las reglas, este camino es invalido.
    // Devolvemos 0 y dejamos de explorar esta rama.
    if (consec_vocales == 3 || consec_consonantes == 3)
    {
        return 0;
    }

    // 2. CASO BASE: Llegamos al final de la palabra.
    if (index == s.length())
    {
        // La palabra solo es agradable si contiene al menos una 'L'.
        if (tiene_L) return 1;
        else return 0;
    }

    // Si la letra ya esta definida en el string original, no decidimos, 
    // solo actualizamos los contadores y avanzamos.
    if (s[index] != '_')
    {
        char c = s[index];
        bool es_vocal = (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
        bool es_L = (c == 'L');

        if (es_vocal)
        {
            return contarPalabras(s, index + 1, consec_vocales + 1, 0, tiene_L);
        }
        else
        {
            return contarPalabras(s, index + 1, 0, consec_consonantes + 1, tiene_L || es_L);
        }
    }
    // 3. BACKTRACKING: Si es un espacio '_', exploramos nuestros 3 universos paralelos
    else 
    {
        long long total = 0;

        // Opcion A: Ponemos una Vocal. Hay 5 vocales, asi que multiplicamos el resultado de esta rama por 5.
        // Las consonantes consecutivas se reinician a 0.
        total += 5LL * contarPalabras(s, index + 1, consec_vocales + 1, 0, tiene_L);

        // Opcion B: Ponemos una Consonante (que NO sea L). Hay 20 de estas.
        // Las vocales consecutivas se reinician a 0.
        total += 20LL * contarPalabras(s, index + 1, 0, consec_consonantes + 1, tiene_L);

        // Opcion C: Ponemos la letra 'L'. Hay 1 sola letra 'L'.
        // Se comporta como consonante, pero vuelve 'tiene_L' a true.
        total += 1LL * contarPalabras(s, index + 1, 0, consec_consonantes + 1, true);

        return total;
    }
}

int main()
{
    //------------------Inicializacion---------------------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string palabra;

    //------------------Lectura de Datos-------------------------
    if (!(cin >> palabra)) return 0;

    //------------------Procesamiento----------------------------
    // Iniciamos el Backtracking desde la posicion 0, sin letras previas.
    long long total_palabras = contarPalabras(palabra, 0, 0, 0, false);

    //------------------Salida-----------------------------------
    cout << total_palabras << "\n";

    return 0;
}
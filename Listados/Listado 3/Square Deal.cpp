//----------------Librerias--------------------
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Estructura para manejar los rectangulos facilmente
struct Rectangulo {
    long long h, w;
};

/*
    ------------Funcion-----------------
    verificarFormas: 
        Comprueba si una combinacion especifica de 3 
    rectangulos (ya rotados y ordenados) logra formar 
    el cuadrado de lado L.
    ------------Parametros----------------
    const vector<Rectangulo>& comb: Los 3 rectangulos en un orden y rotacion especifico.
    long long L: El tamaño del lado del cuadrado que queremos formar.
    --------------Return------------------
    bool: True si logran formar el cuadrado, False si no.
    ----------------------------------
*/
bool verificarFormas(const vector<Rectangulo>& comb, long long L)
{
    // Forma 1: Los tres apilados verticalmente (o horizontalmente, es equivalente)
    // Condicion: Los 3 tienen ancho L, y la suma de sus alturas es L.
    if (comb[0].w == L && comb[1].w == L && comb[2].w == L &&
        (comb[0].h + comb[1].h + comb[2].h == L)) 
    {
        return true;
    }

    // Forma 2: Un rectangulo abarca un lado completo, y los otros dos rellenan el resto.
    // Condicion: El primero tiene ancho L. Los otros dos tienen la misma altura,
    // esta altura es exactamente lo que falta (L - h1), y sus anchos suman L.
    if (comb[0].w == L && 
        comb[1].h == comb[2].h && 
        comb[1].h == (L - comb[0].h) && 
        (comb[1].w + comb[2].w == L)) 
    {
        return true;
    }

    return false;
}

/*
    ------------Funcion-----------------
    buscarCombinaciones: 
        Funcion recursiva (Backtracking) que explora 
    todas las permutaciones y rotaciones posibles.
    ------------Parametros----------------
    const vector<Rectangulo>& originales: Lista de los 3 rectangulos iniciales.
    vector<bool>& usados: Arreglo para saber que rectangulo ya pusimos.
    vector<Rectangulo>& actuales: La combinacion que estamos construyendo.
    long long L: El tamaño del lado del cuadrado a formar.
    bool& posible: Referencia para guardar si encontramos solucion.
    --------------Return------------------
    void: Explora los caminos y modifica 'posible'.
    ----------------------------------
*/
void buscarCombinaciones(const vector<Rectangulo>& originales, vector<bool>& usados, vector<Rectangulo>& actuales, long long L, bool& posible)
{
    // Poda (Pruning): Si ya encontramos que es posible, dejamos de explorar otros caminos.
    if (posible) return;

    // Caso Base: Hemos colocado y rotado los 3 rectangulos.
    if (actuales.size() == 3)
    {
        if (verificarFormas(actuales, L))
        {
            posible = true;
        }
        return;
    }

    // Backtracking: Intentamos colocar cada rectangulo disponible
    for (int i = 0; i < 3; i++)
    {
        if (!usados[i])
        {
            // 1. ELEGIR
            usados[i] = true;

            // ---- EXPLORAR OPCION A: Sin rotar ----
            actuales.push_back(originales[i]);
            buscarCombinaciones(originales, usados, actuales, L, posible);
            actuales.pop_back(); // Deshacer para la siguiente opcion

            // ---- EXPLORAR OPCION B: Rotado ----
            // Optimizacion: Si es un cuadrado (h == w), rotarlo no cambia nada.
            if (originales[i].h != originales[i].w)
            {
                actuales.push_back({originales[i].w, originales[i].h}); // Insertamos invertido
                buscarCombinaciones(originales, usados, actuales, L, posible);
                actuales.pop_back(); // Deshacer
            }

            // 3. DESHACER (Liberamos el rectangulo para que otra rama lo use)
            usados[i] = false;
        }
    }
}

int main()
{
    //------------------Inicializacion---------------------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<Rectangulo> rectangulos(3);
    long long area_total = 0;

    //------------------Lectura de Datos-------------------------
    for (int i = 0; i < 3; i++)
    {
        if (!(cin >> rectangulos[i].h >> rectangulos[i].w)) return 0;
        area_total += (rectangulos[i].h * rectangulos[i].w);
    }

    //------------------Procesamiento----------------------------
    // Calculamos si el area total tiene raiz cuadrada exacta
    long long L = round(sqrt(area_total));
    
    // Si la raiz al cuadrado no es igual al area, nunca sera un cuadrado
    if (L * L != area_total)
    {
        cout << "NO\n";
        return 0;
    }

    vector<bool> usados(3, false);
    vector<Rectangulo> combinacion_actual;
    bool es_posible = false;

    // Iniciamos la recursion de fuerza bruta
    buscarCombinaciones(rectangulos, usados, combinacion_actual, L, es_posible);

    //------------------Salida-----------------------------------
    if (es_posible)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }

    return 0;
}
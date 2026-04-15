//----------------Librerias--------------------
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Estructura para almacenar a cada persona
struct Persona {
    string nombre;
    vector<int> jerarquia;
};

/*
    ------------Funcion-----------------
    procesarJerarquia: 
        Funcion encargada de convertir el string de 
    clase social en un vector numerico ordenado desde 
    la jerarquia mas importante a la menos importante.
    ------------Parametros----------------
    const string& clase_str: String con las clases separadas por guion.
    --------------Return------------------
    vector<int>: Vector con valores numericos (3=upper, 2=middle, 1=lower) 
    rellenado hasta 10 niveles.
    ----------------------------------
*/
vector<int> procesarJerarquia(const string& clase_str)
{
    vector<int> valores;
    stringstream ss(clase_str);
    string token;

    // Leemos cada palabra separada por guiones
    while (getline(ss, token, '-'))
    {
        if (token == "upper") valores.push_back(3);
        else if (token == "middle") valores.push_back(2);
        else if (token == "lower") valores.push_back(1);
    }

    // Invertimos el arreglo porque la ultima palabra (la de mas a la derecha) 
    // es la jerarquia base y la mas importante.
    reverse(valores.begin(), valores.end());

    // El problema indica que los sub-niveles faltantes se asumen como "middle".
    // Como el problema dice que pueden ser hasta 10 palabras, rellenamos hasta 10.
    while (valores.size() < 10)
    {
        valores.push_back(2); // 2 equivale a "middle"
    }

    return valores;
}

/*
    ------------Funcion-----------------
    compararPersonas: 
        Funcion de comparacion para ordenar a las 
    personas de mayor a menor clase social.
    ------------Parametros----------------
    const Persona& a: Primera persona a comparar.
    const Persona& b: Segunda persona a comparar.
    --------------Return------------------
    bool: True si 'a' tiene mayor clase que 'b' o, en 
    caso de empate, si el nombre de 'a' es menor alfabeticamente.
    ----------------------------------
*/
bool compararPersonas(const Persona& a, const Persona& b)
{
    // Comparamos nivel por nivel (desde el mas al menos importante)
    for (int i = 0; i < 10; i++)
    {
        if (a.jerarquia[i] != b.jerarquia[i])
        {
            // Queremos orden descendente (el numero mayor va primero)
            return a.jerarquia[i] > b.jerarquia[i];
        }
    }
    
    // Si todos los niveles son iguales, desempatamos por orden alfabetico
    return a.nombre < b.nombre;
}

int main()
{
    //------------------Inicializacion---------------------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;

    //------------------Lectura de Datos-------------------------
    // Verificamos si hay casos de prueba a leer
    if (!(cin >> t)) return 0;

    for (int caso = 0; caso < t; caso++)
    {
        int n;
        cin >> n;
        cin.ignore(); // Limpiamos el salto de linea que deja el 'cin >> n' en el buffer

        vector<Persona> personas;

        for (int i = 0; i < n; i++)
        {
            string linea;
            getline(cin, linea);

            // La estructura de la linea es "nombre: clase1-clase2 class"
            size_t pos_dos_puntos = linea.find(':');
            string nombre = linea.substr(0, pos_dos_puntos);

            // Extraemos solo la parte de las clases con guiones
            // +2 para saltar el ": " y -6 para ignorar la palabra " class" al final de la linea
            size_t inicio_clase = pos_dos_puntos + 2;
            size_t fin_clase = linea.rfind(" class");
            string clase_str = linea.substr(inicio_clase, fin_clase - inicio_clase);

            //------------------Procesamiento----------------------------
            Persona p;
            p.nombre = nombre;
            p.jerarquia = procesarJerarquia(clase_str);
            personas.push_back(p);
        }

        // Ordenamos usando la funcion personalizada (usamos sort normal porque 
        // nuestro desempate alfabetico ya cubre casos identicos)
        sort(personas.begin(), personas.end(), compararPersonas);

        //------------------Salida-----------------------------------
        for (int i = 0; i < n; i++)
        {
            cout << personas[i].nombre << "\n";
        }
        
        // Imprimimos los 30 signos de igual como pide el output
        cout << "==============================\n";
    }

    return 0;
}
//-----------------Librerias----------------
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <sys/resource.h>
#include <algorithm>

using namespace std;

//-----------------Prototipos Externos-----------------
// Algoritmos provenientes de otros archivos
void mergeSort(vector<int>& arr, int left, int right);
void quickSort(vector<int> &vec, int low, int high);
vector<int> sortArray(vector<int>& arr);

/*
    ------------Funcion-----------------
    leer_entrada: 
        Funcion encargada de leer un archivo de texto y 
        almacenar los valores enteros secuenciales en un vector.
    ------------Parametros----------------
    nombre_archivo: string constante con la ruta del archivo a leer.
    --------------Return------------------
    vector<int>: vector con los datos extraidos del archivo.
    ----------------------------------
*/
vector<int> leer_entrada(const string& nombre_archivo) 
{
    ifstream archivo(nombre_archivo);
    vector<int> resultado;
    int valor;
    
    // Iteramos leyendo cada valor hasta el EOF
    while (archivo >> valor) 
    {
        resultado.push_back(valor);
    }
    
    return resultado;
}

/*
    ------------Funcion-----------------
    escribir_salida: 
        Funcion encargada de iterar por un vector y guardar 
        sus elementos en un archivo de texto, separados por espacios.
    ------------Parametros----------------
    nombre_archivo: string constante con la ruta del archivo a escribir.
    arreglo: vector constante con los datos a guardar.
    --------------Return------------------
    None:
    ----------------------------------
*/
void escribir_salida(const string& nombre_archivo, const vector<int>& arreglo) 
{
    ofstream archivo(nombre_archivo);
    
    for (size_t i = 0; i < arreglo.size(); ++i) 
    {
        // Verificamos si es el ultimo elemento para no dejar un espacio en blanco extra al final
        archivo << arreglo[i] << (i == arreglo.size() - 1 ? "" : " ");
    }
}

int main(int argc, char* argv[]) 
{
    // ----------Optimizador para la consola---------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //-----------------Inicializacion------------------
    // Verificamos que se hayan pasado los argumentos correctos por consola
    if (argc < 5) 
    {
        cerr << "Usage: " << argv[0] << " <algorithm> <input_file> <output_file> <measurement_file>" << endl;
        cerr << "Algorithms: mergesort, quicksort, stdsort" << endl;
        return 1;
    }

    string algoritmo = argv[1];
    string archivo_entrada = argv[2];
    string archivo_salida = argv[3];
    string archivo_mediciones = argv[4];

    // Cargamos los datos a nuestro vector principal
    vector<int> arreglo = leer_entrada(archivo_entrada);
    int n = arreglo.size();

    //-------------Algoritmo--------------------
    // Iniciamos el cronometro para medir el rendimiento
    auto inicio = chrono::high_resolution_clock::now();

    // Ejecutamos el algoritmo solicitado
    if (algoritmo == "mergesort") 
    {
        if (!arreglo.empty()) 
        {
            mergeSort(arreglo, 0, (int)arreglo.size() - 1);
        }
    } 
    else if (algoritmo == "quicksort") 
    {
        if (!arreglo.empty()) 
        {
            quickSort(arreglo, 0, (int)arreglo.size() - 1);
        }
    } 
    else if (algoritmo == "stdsort") 
    {
        sortArray(arreglo);
    } 
    else 
    {
        cerr << "Unknown algorithm: " << algoritmo << endl;
        return 1;
    }

    // Detenemos el cronometro y calculamos la diferencia
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> diferencia = fin - inicio;

    // Medimos el consumo pico de memoria (Resident Set Size)
    struct rusage uso_memoria;
    getrusage(RUSAGE_SELF, &uso_memoria);
    long memoria_kb = uso_memoria.ru_maxrss; // en kilobytes para Linux

    //---------------Guardado de resultados---------------------
    // Guardamos el arreglo ya ordenado en el archivo de salida
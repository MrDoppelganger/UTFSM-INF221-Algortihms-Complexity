//-----------------Librerias----------------
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/resource.h>
#include <vector>

using namespace std;

//-----------------Tipos de datos-----------------
// Renombramos los tipos para que el codigo sea mas limpio
typedef vector<int> vi;
typedef vector<vi> vii;

//-----------------Prototipos Externos-----------------
// Algoritmos provenientes de otros archivos
void mulMat(vii &m1, vii &m2, vii &res);
void Strassen_algorithm(vii &A, vii &B, vii &C, int size);

/*
    ------------Funcion-----------------
    leer_matriz: 
        Funcion encargada de leer un archivo de texto linea por linea
        y convertir los valores numericos en una matriz bidimensional 
        (vector de vectores).
    ------------Parametros----------------
    nombre_archivo: string constante con la ruta del archivo a leer.
    --------------Return------------------
    vii (vector<vector<int>>): matriz con los datos extraidos del archivo.
    ----------------------------------
*/
vii leer_matriz(const string &nombre_archivo) 
{
    ifstream archivo(nombre_archivo);
    vii matriz;
    string linea;
    
    while (getline(archivo, linea)) 
    {
        // Ignoramos lineas vacias
        if (linea.empty()) continue;
            
        stringstream ss(linea);
        vi fila;
        int valor;
        
        while (ss >> valor) 
        {
            fila.push_back(valor);
        }
        
        if (!fila.empty())
        {
            matriz.push_back(fila);
        }
    }
    
    return matriz;
}

/*
    ------------Funcion-----------------
    escribir_matriz: 
        Funcion encargada de iterar por una matriz bidimensional y guardar 
        sus elementos en un archivo de texto, fila por fila.
    ------------Parametros----------------
    nombre_archivo: string constante con la ruta del archivo a escribir.
    matriz: vii (vector de vectores) constante con los datos a guardar.
    --------------Return------------------
    None:
    ----------------------------------
*/
void escribir_matriz(const string &nombre_archivo, const vii &matriz) 
{
    ofstream archivo(nombre_archivo);
    
    for (size_t i = 0; i < matriz.size(); ++i) 
    {
        for (size_t j = 0; j < matriz[i].size(); ++j) 
        {
            // Verificamos si es el ultimo elemento de la fila para no dejar un espacio en blanco extra
            archivo << matriz[i][j] << (j == matriz[i].size() - 1 ? "" : " ");
        }
        archivo << "\n";
    }
}

int main(int argc, char *argv[]) 
{
    // ----------Optimizador para la consola---------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //-----------------Inicializacion------------------
    // Verificamos que se hayan pasado los argumentos correctos por consola
    if (argc < 6) 
    {
        cerr << "Usage: " << argv[0] << " <algorithm> <matrix1_file> <matrix2_file> <output_file> <measurement_file>" << endl;
        cerr << "Algorithms: naive, strassen" << endl;
        return 1;
    }

    string algoritmo = argv[1];
    string archivo_m1 = argv[2];
    string archivo_m2 = argv[3];
    string archivo_salida = argv[4];
    string archivo_mediciones = argv[5];

    // Cargamos las matrices desde los archivos
    vii matriz1 = leer_matriz(archivo_m1);
    vii matriz2 = leer_matriz(archivo_m2);

    // Verificamos que las matrices no esten vacias
    if (matriz1.empty() || matriz2.empty()) 
    {
        cerr << "Error: One of the matrices is empty or missing." << endl;
        return 1;
    }

    int n = matriz1.size();
    vii resultado;

    //-------------Algoritmo--------------------
    // Iniciamos el cronometro para medir el rendimiento
    auto inicio = chrono::high_resolution_clock::now();

    // Ejecutamos el algoritmo solicitado
    if (algoritmo == "naive") 
    {
        mulMat(matriz1, matriz2, resultado);
    } 
    else if (algoritmo == "strassen") 
    {
        // El algoritmo de Strassen requiere que la matriz resultado este inicializada en 0
        resultado.assign(n, vi(n, 0));
        Strassen_algorithm(matriz1, matriz2, resultado, n);
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
    long memoria_kb = uso_memoria.ru_maxrss;

    //---------------Guardado de resultados---------------------
    // Guardamos la matriz resultante en el archivo de salida
    escribir_matriz(archivo_salida, resultado);

    // Abrimos el archivo de mediciones en modo Append para no sobreescribir datos anteriores
    ofstream archivo_m(archivo_mediciones, ios::app);
    
    // Si el archivo esta vacio (posicion 0), le ponemos los encabezados (headers)
    if (archivo_m.tellp() == 0) 
    {
        archivo_m << "algorithm,n,time_seconds,memory_kb" << endl;
    }
    
    // Registramos la medicion actual
    archivo_m << algoritmo << "," << n << "," << diferencia.count() << "," << memoria_kb << endl;

    return 0;
}
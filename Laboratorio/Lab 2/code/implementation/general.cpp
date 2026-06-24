//------------------Librerias--------------------
#include "algorithms/common.h"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

//------------------Medicion Aislada------------------
template <typename Func>
long long medirEjecucion(Func funcionObjetivo, long long &resultado_final, double &tiempo_ms) 
{
    // Creamos un conducto (pipe) para comunicar el proceso padre con el hijo
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) 
    {
        cerr << "Error al crear pipe para fork()\n";
        return -1;
    }

    // Bifurcamos el programa para aislar y medir puramente la memoria del algoritmo
    pid_t pid = fork();
    if (pid < 0) 
    {
        cerr << "Error al ejecutar fork()\n";
        return -1;
    }

    if (pid == 0) 
    {
        // Entramos al proceso hijo y bloqueamos el acceso de lectura
        close(pipe_fd[0]);
        
        // Cronometramos la ejecucion exacta de la funcion enviada
        auto inicio = chrono::high_resolution_clock::now();
        long long resultado_local = funcionObjetivo();
        auto fin = chrono::high_resolution_clock::now();
        double duracion_ms = chrono::duration<double, milli>(fin - inicio).count();

        // Transferimos los calculos obtenidos al proceso padre
        if (write(pipe_fd[1], &resultado_local, sizeof(resultado_local)) == -1) 
        {
            cerr << "Error al escribir el resultado en el pipe\n";
        }
        if (write(pipe_fd[1], &duracion_ms, sizeof(duracion_ms)) == -1) 
        {
            cerr << "Error al escribir el tiempo en el pipe\n";
        }
        
        close(pipe_fd[1]);
        exit(0);
    } 
    else 
    {
        // Entramos al proceso padre y bloqueamos el acceso de escritura
        close(pipe_fd[1]);
        long long resultado_local = -1;
        double duracion_ms = -1;

        // Extraemos los calculos transferidos por el proceso hijo
        if (read(pipe_fd[0], &resultado_local, sizeof(resultado_local)) == -1) 
        {
            cerr << "Error al leer el resultado del pipe\n";
        }
        if (read(pipe_fd[0], &duracion_ms, sizeof(duracion_ms)) == -1) 
        {
            cerr << "Error al leer el tiempo del pipe\n";
        }
        close(pipe_fd[0]);

        // Sincronizamos la finalizacion del hijo para capturar su impacto en RAM
        int estado;
        struct rusage uso_recursos;
        wait4(pid, &estado, 0, &uso_recursos);

        resultado_final = resultado_local;
        tiempo_ms = duracion_ms;

        // Retornamos el consumo de memoria residente (Peak RAM) en KB
        return uso_recursos.ru_maxrss;
    }
}

//------------------Funciones Auxiliares------------------
/*
    ------------Funcion-----------------
    leerCasoPrueba:
        Lee el archivo de texto entrante y mapea los datos
        hacia las estructuras de memoria del programa.
    ------------Parametros----------------
    const string& nombre_archivo: Ruta del archivo.
    int& n: Referencia para el numero de animes.
    long long& minutos_maximos: Referencia para el limite de tiempo (M).
    long long& energia_maxima: Referencia para el limite de energia (E).
    vector<Anime>& animes: Referencia al vector donde se alojaran los animes.
    --------------Return------------------
    bool: True si la carga de datos fue exitosa, false en caso de error.
    ----------------------------------
*/
bool leerCasoPrueba(const string &nombre_archivo, int &n, long long &minutos_maximos, long long &energia_maxima, vector<Anime> &animes) 
{
    // Intentamos cargar el archivo indicado por consola
    ifstream archivo_entrada(nombre_archivo);
    if (!archivo_entrada.is_open()) 
    {
        cerr << "Error: No se pudo abrir el archivo " << nombre_archivo << "\n";
        return false;
    }
    
    // Extraemos las limitantes globales de la mochila
    archivo_entrada >> n >> minutos_maximos >> energia_maxima;

    // Dimensionamos la estructura principal para evitar realojamientos de memoria
    animes.resize(n);
    
    // Recolectamos la metadata de cada anime y de sus capitulos
    for (int i = 0; i < n; ++i) 
    {
        archivo_entrada >> animes[i].nombre >> animes[i].q >> animes[i].b;
        animes[i].capitulos.resize(animes[i].q);

        for (int j = 0; j < animes[i].q; ++j) 
        {
            archivo_entrada >> animes[i].capitulos[j].t >> animes[i].capitulos[j].c >> animes[i].capitulos[j].v;
        }
    }

    archivo_entrada.close();
    return true;
}

//------------------Main------------------
int main(int argc, char *argv[]) 
{
    //------------------Inicializacion------------------
    // Optimizamos los flujos estandar para acelerar la lectura de datos
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Comprobamos la inyeccion correcta de argumentos por consola
    if (argc < 2) 
    {
        cerr << "Uso: " << argv[0] << " <ruta_al_testcase>\n";
        return 1;
    }

    string nombre_archivo = argv[1];

    int n;
    long long minutos_maximos, energia_maxima;
    vector<Anime> animes;

    // Delegamos la interpretacion del archivo y verificamos errores
    if (!leerCasoPrueba(nombre_archivo, n, minutos_maximos, energia_maxima, animes)) 
    {
        return 1;
    }

    // Calculamos el universo total de capitulos para nuestras estadisticas
    int total_capitulos = 0;
    for (int i = 0; i < n; i++) 
    {
        total_capitulos += animes[i].q;
    }

    //------------------Procesamiento y Medicion------------------
    long long resultado_fuerza_bruta = -1, resultado_dp = -1, resultado_greedy_1 = -1, resultado_greedy_2 = -1;
    double tiempo_fuerza_bruta = -1, tiempo_dp = -1, tiempo_greedy_1 = -1, tiempo_greedy_2 = -1;
    long long memoria_fuerza_bruta = -1, memoria_dp = -1, memoria_greedy_1 = -1, memoria_greedy_2 = -1;

    // Evaluamos el rendimiento de la heuristica basada en satisfaccion
    memoria_greedy_1 = medirEjecucion([&]() { return resolverGreedyV(n, minutos_maximos, energia_maxima, animes); }, resultado_greedy_1, tiempo_greedy_1);

    // Evaluamos el rendimiento de la heuristica basada en eficiencia
    memoria_greedy_2 = medirEjecucion([&]() { return resolverGreedyVdivT(n, minutos_maximos, energia_maxima, animes); }, resultado_greedy_2, tiempo_greedy_2);

    // Evaluamos el rendimiento de la busqueda del optimo garantizado
    memoria_dp = medirEjecucion([&]() { return resolverDP(n, minutos_maximos, energia_maxima, animes); }, resultado_dp, tiempo_dp);

    // Restringimos Fuerza Bruta a casos de prueba muy reducidos para no colapsar la maquina
    if (n <= 20) 
    {
        memoria_fuerza_bruta = medirEjecucion([&]() { return resolverFuerzaBruta(n, minutos_maximos, energia_maxima, animes); }, resultado_fuerza_bruta, tiempo_fuerza_bruta);
    }

    //------------------Salida de Resultados------------------
    // Aislamos el identificador del caso de prueba para nombrar ordenadamente los logs
    fs::path ruta_archivo(nombre_archivo);
    string nombre_base = ruta_archivo.stem().string(); 

    // Garantizamos la existencia de los directorios receptores
    fs::create_directories("data/outputs");
    fs::create_directories("data/measurements");

    // Generamos un reporte individual con los resultados obtenidos en este test
    string ruta_salida = "data/outputs/output_" + nombre_base + ".txt";
    ofstream archivo_salida(ruta_salida);
    if (archivo_salida.is_open()) 
    {
        archivo_salida << "Resultados para: " << nombre_archivo << "\n";
        archivo_salida << "==============================\n";
        archivo_salida << "Brute Force: " << (resultado_fuerza_bruta != -1 ? to_string(resultado_fuerza_bruta) : "N/A (n muy grande)") << "\n";
        archivo_salida << "Dynamic Programming: " << resultado_dp << "\n";
        archivo_salida << "Greedy 1 (v): " << resultado_greedy_1 << "\n";
        archivo_salida << "Greedy 2 (v/t): " << resultado_greedy_2 << "\n";
        archivo_salida.close();
    }

    // Registramos la telemetria en el dataset central para posteriores graficos
    string ruta_mediciones = "data/measurements/measurements.csv";
    bool existe_archivo = fs::exists(ruta_mediciones);

    ofstream archivo_mediciones(ruta_mediciones, ios::app);
    if (archivo_mediciones.is_open()) 
    {
        // Si el archivo de registro no existe, inyectamos los encabezados de columna
        if (!existe_archivo) 
        {
            archivo_mediciones << "Instancia,N,Q,M,E,Algoritmo,Tiempo_ms,Satisfaccion,Memoria_KB\n";
        }

        // Volcamos la metadata de cada enfoque validando si fueron ejecutados
        if (resultado_fuerza_bruta != -1) 
        {
            archivo_mediciones << nombre_base << "," << n << "," << total_capitulos << "," << minutos_maximos << "," << energia_maxima << ",BruteForce," << tiempo_fuerza_bruta << "," << resultado_fuerza_bruta << "," << memoria_fuerza_bruta << "\n";
        }
        
        archivo_mediciones << nombre_base << "," << n << "," << total_capitulos << "," << minutos_maximos << "," << energia_maxima << ",DP," << tiempo_dp << "," << resultado_dp << "," << memoria_dp << "\n";
        archivo_mediciones << nombre_base << "," << n << "," << total_capitulos << "," << minutos_maximos << "," << energia_maxima << ",Greedy(v)," << tiempo_greedy_1 << "," << resultado_greedy_1 << "," << memoria_greedy_1 << "\n";
        archivo_mediciones << nombre_base << "," << n << "," << total_capitulos << "," << minutos_maximos << "," << energia_maxima << ",Greedy(v/t)," << tiempo_greedy_2 << "," << resultado_greedy_2 << "," << memoria_greedy_2 << "\n";

        archivo_mediciones.close();
    }

    cout << "Ejecucion completada para: " << nombre_base << "\n";
    return 0;
}
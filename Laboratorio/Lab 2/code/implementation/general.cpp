//------------------Librerias--------------------
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <filesystem>
#include "algorithms/common.h"

using namespace std;
namespace fs = std::filesystem;

//------------------Funciones Auxiliares------------------
/*
    ------------Funcion-----------------
    parseTestcase: 
        Lee el archivo de prueba y carga los datos 
        en las estructuras.
    ------------Parametros----------------
    const string& filename: Ruta del archivo.
    int& n: Referencia para el numero de animes.
    long long& M: Referencia para el tiempo maximo.
    long long& E: Referencia para la energia maxima.
    vector<Anime>& animes: Referencia al vector donde se guardaran los animes.
    --------------Return------------------
    bool: True si la lectura fue exitosa, false en caso contrario.
    ----------------------------------
*/
bool parseTestcase(const string& filename, int& n, long long& M, long long& E, vector<Anime>& animes) 
{
    ifstream infile(filename);
    if (!infile.is_open()) 
    {
        cerr << "Error: No se pudo abrir el archivo " << filename << "\n";
        return false;
    }
    infile >> n >> M >> E;

    // establecemos el tamaño de nuestro vector
    animes.resize(n);
    //iteramos para cargar cada anime
    for (int i = 0; i < n; ++i) 
    {
        infile >> animes[i].nombre >> animes[i].q >> animes[i].b;
        animes[i].capitulos.resize(animes[i].q);

        //Iteramos para cargar los capitulos de cada anime.
        for (int j = 0; j < animes[i].q; ++j) {
            infile >> animes[i].capitulos[j].t >> animes[i].capitulos[j].c >> animes[i].capitulos[j].v;
        }
    }

    infile.close();
    return true;
}

//------------------Main------------------
int main(int argc, char* argv[]) {
    //------------------Inicializacion------------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <ruta_al_testcase>\n";
        return 1;
    }

    string filename = argv[1];
    
    int n;
    long long M, E;
    vector<Anime> animes;

    // Parseo de los datos
    if (!parseTestcase(filename, n, M, E, animes)) {
        return 1;
    }

    //------------------Procesamiento y Medicion------------------
    long long res_bf = -1, res_dp = -1, res_g1 = -1, res_g2 = -1;
    double time_bf = -1, time_dp = -1, time_g1 = -1, time_g2 = -1;

    // Ejecucion Greedy 1
    auto start_g1 = chrono::high_resolution_clock::now();
    res_g1 = solve_greedy1(n, M, E, animes);
    auto end_g1 = chrono::high_resolution_clock::now();
    time_g1 = chrono::duration<double, milli>(end_g1 - start_g1).count();

    // Ejecucion Greedy 2
    auto start_g2 = chrono::high_resolution_clock::now();
    res_g2 = solve_greedy2(n, M, E, animes);
    auto end_g2 = chrono::high_resolution_clock::now();
    time_g2 = chrono::duration<double, milli>(end_g2 - start_g2).count();

    // Ejecucion DP
    auto start_dp = chrono::high_resolution_clock::now();
    res_dp = solve_dp(n, M, E, animes);
    auto end_dp = chrono::high_resolution_clock::now();
    time_dp = chrono::duration<double, milli>(end_dp - start_dp).count();

    // Ejecucion Fuerza Bruta (Solo para n pequeño, si no se demorará demasiado)
    if (n <= 10) {
        auto start_bf = chrono::high_resolution_clock::now();
        res_bf = solve_brute_force(n, M, E, animes);
        auto end_bf = chrono::high_resolution_clock::now();
        time_bf = chrono::duration<double, milli>(end_bf - start_bf).count();
    }

    //------------------Salida de Resultados------------------
    // Extraer el nombre base del archivo para nombrar los outputs
    fs::path p(filename);
    string base_filename = p.stem().string(); // Ej: testcases_5_1

    // Asegurar que las carpetas existan
    fs::create_directories("data/outputs");
    fs::create_directories("data/measurements");

    // Guardar outputs (Resultados)
    string output_path = "data/outputs/output_" + base_filename + ".txt";
    ofstream out_file(output_path);
    if (out_file.is_open()) {
        out_file << "Resultados para: " << filename << "\n";
        out_file << "==============================\n";
        out_file << "Brute Force: " << (res_bf != -1 ? to_string(res_bf) : "N/A (n muy grande)") << "\n";
        out_file << "Dynamic Programming: " << res_dp << "\n";
        out_file << "Greedy 1 (v): " << res_g1 << "\n";
        out_file << "Greedy 2 (v/t): " << res_g2 << "\n";
        out_file.close();
    }

    // Guardar mediciones en CSV
    string measure_path = "data/measurements/measurements.csv";
    bool file_exists = fs::exists(measure_path);
    
    ofstream meas_file(measure_path, ios::app);
    if (meas_file.is_open()) {
        // Escribir cabecera si el archivo no existia
        if (!file_exists) {
            meas_file << "Instancia,N,M,E,Algoritmo,Tiempo_ms,Satisfaccion\n";
        }
        
        if (res_bf != -1) {
            meas_file << base_filename << "," << n << "," << M << "," << E << ",BruteForce," << time_bf << "," << res_bf << "\n";
        }
        meas_file << base_filename << "," << n << "," << M << "," << E << ",DP," << time_dp << "," << res_dp << "\n";
        meas_file << base_filename << "," << n << "," << M << "," << E << ",Greedy1," << time_g1 << "," << res_g1 << "\n";
        meas_file << base_filename << "," << n << "," << M << "," << E << ",Greedy2," << time_g2 << "," << res_g2 << "\n";
        
        meas_file.close();
    }

    cout << "Ejecucion completada para: " << base_filename << "\n";
    return 0;
}

//----------------Libreria------------------
#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

int main()
{
    //-----------------Inicializacion----------------
    //Optimizacion para la consola
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //Creamos un vector que se encargara de almacenar todas las palabras dadas
    vector<string> repositorio;
    string palabra_dada;
    while(cin >> palabra_dada)
    {
        repositorio.push_back(palabra_dada);
    }

    //Creamos un set para guardar las combinaciones ordenadas y unicas
    set<string> combinaciones;

    //-------------Algoritmo--------------------
    //Iteramos por cada palabra y mezclamos con las otras para guardarlas en nuestro set
    for(int i = 0; i < repositorio.size(); i++)
    {
        for(int j = 0; j < repositorio.size();j++)
        {
            //Nos asegurmamos de no estar en la misma posición.
            if(i != j)
            {
                //Unimos las palabras i y j
                string palabra_compuesta = repositorio[i] + repositorio[j];
                //Guardamos en nuestro set
                combinaciones.insert(palabra_compuesta);
            }
        }
    }
    //Ahora imprimimos el resultado final
    for(const string& resultado : combinaciones)
    {
        cout << resultado << "\n";
    }
    return 0;
}
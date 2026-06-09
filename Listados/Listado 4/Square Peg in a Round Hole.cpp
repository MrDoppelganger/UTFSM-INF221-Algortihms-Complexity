//-------------------------Librerias----------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath> 

using namespace std;

int main()
{
    //----------------------Inicializacion------------------------------
    //Trucazo
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //Guardamos las variables del problemas
    int n, m, k;
    cin >> n >> m >> k;

    //Creamos la lista para los radios de las parcelas
    vector<double> parcelas(n);
    for(int i = 0; i < n; i++)
    {
        cin >> parcelas[i];
    }

    //Creamos una unica lista para todas las casas (las vamos a transformar a un "radio efectivo")
    vector<double> casas;

    //Leemos las casas circulares (su radio se queda igual, no hay que hacerles nada)
    for(int i = 0; i < m; i++)
    {
        double radio_casa;
        cin >> radio_casa;
        casas.push_back(radio_casa);
    }

    //Leemos las casas cuadradas y las convertimos. 
    for(int i = 0; i < k; i++)
    {
        double lado;
        cin >> lado;
        //Calculamos el radio del circulo imaginario que envolveria a esta casa cuadrada
        double radio_efectivo = (lado * sqrt(2.0)) / 2.0;
        casas.push_back(radio_efectivo);
    }

    //Ordenamos ambos arreglos de menor a mayor para emparejarlos de forma optima
    sort(parcelas.begin(), parcelas.end());
    sort(casas.begin(), casas.end());

    //------------------------Algorimto---------------------------------
    //Contador de cuantas casas logramos ubicar
    int checks = 0;
    
    //Punteros para recorrer las listas desde el inicio
    int parcelas_ptr = 0; 
    int casas_ptr = 0; 

    //iteramos mientras tengamos parcelas y casas por revisar
    while(parcelas_ptr < n && casas_ptr < casas.size())
    {
        //Comprobamos que cabe (teniendo en consideracion no usar el borde)
        if(casas[casas_ptr] < parcelas[parcelas_ptr])
        {
            //Si la casa cabe, la construimos y pasamos a la siguiente casa y a la siguiente parcela
            checks++;
            casas_ptr++;
            parcelas_ptr++;
        }
        //Si la casa no cabe en esta parcela, significa que la parcela es muy chica
        else
        {
            //Descartamos la parcela y probamos con la siguiente.
            parcelas_ptr++;
        }
    }

    //entregamos el resultado de casas construidas:
    cout << checks << "\n";

    return 0;
}
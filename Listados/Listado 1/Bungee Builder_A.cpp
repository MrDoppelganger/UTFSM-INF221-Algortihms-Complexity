//-----------------Librerias----------------
#include <iostream>

using namespace std;

int main()
{
    //----------------Inicialización de datos------------------
    //Almacenamos la cantidad de montañas que hay
    int m;
    if(!(cin >> m)) return 0;
    const int montañas = m;
    //Creamos un array que almacene todas las alturas de las montañas
    int altura[montañas];
    for(int i = 0; i < montañas; i++)
    {
        if(!(cin >> altura[i])) return 0;
    }
    //Creamos una variable encargada de almacenar la altura maxima
    int altura_maxima = 0;
    //---------------Algoritmo de busqueda---------------------
    //analizaremos las alturas maximas que se puede obtener de cada montaña.
    for(int i = 0; i < (montañas - 1); i++)
    {
        //Creamos una variable de comparación
        int altura_maxima_potencial = 0;
        //Seleccionamos una montaña y revisamos cual es el puente con mayor profundidad que puede generar
        for(int j = 0; j < (montañas - i - 1); j++)
        {
            //Revisamos si la montaña es la montaña maxima con la que se puede hacer un puente 
            if(altura[i] <= altura[i + j + 1])
            {
                //vemos si es necesario actualizar la altura
                if(altura_maxima < altura_maxima_potencial)
                {
                    altura_maxima = altura_maxima_potencial;
                }
                //nos salimos del ciclo
                break; 
            }
            //En caso de que la montaña sea menor, debemos actualizar la altura maxima potencial y en algunos casos la general
            else
            {
                //Creamos el comparador prima para ir escogiendo las alturas potenciales maximas
                int altura_potencial_prima = altura[i] - altura[i + j + 1];
                //Actualizamos la altura potencial en caso de que esta sea menor a las anteriormente guardadas
                if(altura_maxima_potencial < altura_potencial_prima)
                {
                    altura_maxima_potencial = altura_potencial_prima;
                }
                //tenemos que revisar si es que el puente que se puede realizar a media altura de i es la maxima.
                else if(altura_maxima_potencial > altura_potencial_prima)
                {
                    //Comparamos nuestra altura maxima con la altura que se puede realizar con este puente
                    if(altura_maxima < (altura_maxima_potencial - altura_potencial_prima))
                    {
                        //actualizamos la altura maxima
                        altura_maxima = altura_maxima_potencial - altura_potencial_prima;
                    }
                }
            }
        }
    }

    //printeamos el resultado final
    cout << altura_maxima << endl;

    return 0;
}
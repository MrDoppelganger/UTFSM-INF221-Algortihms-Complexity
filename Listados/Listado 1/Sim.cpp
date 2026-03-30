//----------libtrerias------------
#include <iostream>
#include <list>
#include <string>

using namespace std;

/*
    ------------Funcion-----------------
    lector: 
        Funcion encargada de leer un texto e interpetar
    los simbolos especiales que aparezcan, con el fin de
    crear una frase.
    ------------Parametros----------------
    None:
    --------------Return------------------
    None:.
    ----------------------------------
*/
void lector()
{
    //CReamos un string que almacene la linea que buscamos interpretar.
    string linea;
    if(!(cin >> ws && getline(cin,linea))) return;

    //Creamos una lista doblemente enlazada para poder trabajar la frase y la posicion del cursor
    list<char> lista;
    // Creamos un itrerador que apuntara al lugar donde se incertara el caracter.
    auto Cursor = lista.end(); 

    //iteramos por cada caracter de nuestro string y detectamos los simbolos especiales.
    for (char character : linea) 
    {
        // Tecla Inicio: Cursor al principio.
        if (character == '[') 
        {
            Cursor = lista.begin();
        }
        // Tecla Fin: Cursor al final.
        else if (character == ']') 
        {
            Cursor = lista.end();
        } 
        // Tecla Retroceso: Borra el caracter de la izquierda.
        else if (character == '<') 
        {
            //Nos aseguramos que el cursor no este en el inicio de la lista
            if (Cursor != lista.begin()) 
            {
                auto borrar = Cursor;
                --borrar; // Retrocedemos para apuntar al carácter previo
                lista.erase(borrar);
                // El itrerador 'Cursor' sigue siendo válido y apunta al mismo sitio
            }
        }
        // Carácter normal: Insertar en la posición del cursor.
        else 
        {
            // insert() coloca el elemento ANTES de la posición de 'Cursor'
            lista.insert(Cursor, character);
        }
    }

    // Construimos un string con la lista doblemente enlazada para mejorar el rendimiento del print
    string resultado(lista.begin(), lista.end());
    cout << resultado << "\n";
}

int main() {
    // ----------Optimizador para la consola---------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //------------Lectura de textos-------------------
    int T;
    if (cin >> T) {
        while (T--) {
            lector();
        }
    }
    return 0;
}
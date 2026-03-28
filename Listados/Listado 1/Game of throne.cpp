//-----------------Librerias----------------
#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    // Creamos unas variables iniciales para su posterior uso.
    int n, k;
    // Leemos la primera linea con las medidas necesarias.
    if (!(cin >> n >> k)) return 0;
    //establecemos las variables como constantes en el codigo
    const int niños = n;
    const int instrucciones = k; 

    // Creamos una pila para almacenar las posiciones en la que se ha estado y seteamos el inicio.
    stack<int> historial;
    historial.push(0); 

    // Instanciamos la variable que trackeara la pos del huevo
    int posActual = 0;

    // ahora procesaremos todas las intrucciones
    for (int i = 0; i < instrucciones; ++i) {
        // le otorgamos el valor de la instruccion a comando.
        string comando;
        cin >> comando;

        //Si es una instruccion undo, debemos saltar a la siguiente instruccion y deshacer los moves.
        if (comando == "undo") {
            int m;
            cin >> m;
            // Para deshacer 'm' lanzamientos, sacamos 'm' elementos de la pila
            for (int j = 0; j < m; ++j) {
                if (!historial.empty()) {
                    historial.pop();
                }
            }
            // La nueva posición es el tope actual de la pila
            posActual = historial.top();
        } 
        // realizamos el movimiento en caso de no ser un undo.
        else {
            // trasnformamos a entero el string de la instruccion
            int t = stoi(comando);
            
            // calculamos la posicion haciendo uso del modulo de tal manera que no afecte el signo
            posActual = (posActual + (t % niños) + niños) % niños;
            // Guardamos la nueva posición en la pila
            historial.push(posActual);
        }
    }

    // El resultado final es el niño que quedó al tope de la pila
    cout << historial.top() << endl;

    return 0;
}
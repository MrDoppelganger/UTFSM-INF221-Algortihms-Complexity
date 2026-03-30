//------------Librerias-----------------
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() 
{
    //------------------Inicializacion---------------------------
    // Optimización para que cin/cout sean mucho más rápidos
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //Creamos una variable n que almacene la cantidad de montañas que hay
    int n;
    if (!(cin >> n)) return 0;

    // Usamos vetor para almacenar las diferentes alturas del arreglo
    vector<int> alturas(n);
    for (int i = 0; i < n; i++) {
        cin >> alturas[i];
    }

    //-------------------Algoritmo----------------------------
    // Si hay menos de 3 montañas, es imposible construir un puente con un salto en medio
    if (n < 3) {
        cout << 0 << "\n";
        return 0;
    }

    // Arreglos para precalcular las alturas máximas
    vector<int> izquierda_maximo(n);
    vector<int> derecha_maximo(n);

    // Llenamos izquierda_maximo: la montaña más alta desde el inicio hasta 'i'
    izquierda_maximo[0] = alturas[0];
    for (int i = 1; i < n; i++) {
        izquierda_maximo[i] = max(izquierda_maximo[i - 1], alturas[i]);
    }

    // Llenamos derecha_maximo: la montaña más alta desde el final hasta 'i'
    derecha_maximo[n - 1] = alturas[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        derecha_maximo[i] = max(derecha_maximo[i + 1], alturas[i]);
    }

    int salto_maximo = 0;

    // Analizamos cada montaña (excluyendo la primera y la última, ya que no pueden estar debajo de un puente)
    for (int i = 1; i < n - 1; i++) {
        // La altura máxima del puente sobre la montaña 'i'
        int altura_puente = min(izquierda_maximo[i - 1], derecha_maximo[i + 1]);
        
        // Si el puente es más alto que la montaña actual, calculamos la caída
        if (altura_puente > alturas[i]) {
            int caida_actual = altura_puente - alturas[i];
            salto_maximo = max(salto_maximo, caida_actual);
        }
    }

    cout << salto_maximo << "\n";

    return 0;
}
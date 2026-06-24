# Documentación de la Implementación

Esta seccion contiene el grueso del proyecto, desde la implementacion de los algoritmos,
hasta los resultados de las pruebas.
---

## <u>Algoritmos Implementados</u>

### 1. Fuerza Bruta (`brute-force.cpp`)
*   **Idea General:** Explora recursivamente todo el árbol de decisiones. Para cada anime,
evalúa todas las opciones posibles (cuántos capítulos consecutivos ver, desde $0$ hasta 
$q_i$). Se queda con la opción que entregue mayor satisfacción total sin superar el tiempo
 ni energía.
*   **Implementación:** Se utiliza una función recursiva principal que avanza índice por 
índice en los animes, pasando como estado el tiempo actual y energía actual gastados. En
caso de llegar al final del arreglo o superar los límites, retorna y compara el máximo 
encontrado globalmente.
*   **Complejidad Temporal:** $\mathcal{O}\left(\prod_{i=1}^{n} (q_i + 1)\right)$. En
el peor de los casos evalúa todas las combinaciones, haciéndolo de un orden exponencial,
practicable únicamente para los casos más pequeños.

### 2. Programación Dinámica (`dynamic-programming.cpp`)
*   **Idea General:** Optimiza el esquema de Fuerza Bruta mediante un enfoque de tabulación
 o memorización. Aprovecha el hecho de que múltiples caminos de evaluación llegan a los 
 mismos remanentes de tiempo y energía, y evita recalcular subproblemas ya resueltos.
*   **Implementación:** Se modela la solución guardando los estados en una tabla/matriz 
multidimensional de la forma `DP[anime][tiempo_restante][energia_restante]`. El estado depende
 de los recursos disponibles en el instante evaluado.
*   **Complejidad Temporal:** $\mathcal{O}\left(n \cdot M \cdot E \cdot \max(q_i)\right)$. 
Este algoritmo pseudo-polinomial es sustancialmente más rápido y capaz de resolver instancias 
grandes de manera mucho mas razonables, considerando que nos asegura una solucion optima. 

### 3. Heurística Greedy 1 : Mejor satisfaccion "v" (`greedy1.cpp`)
*   **Idea General:** Prioriza las opciones de visualización según la **mayor satisfacción neta**
otorgada por el capítulo siguiente a ver, esto nos entregara una solucion sub-optima o en el mejor
de los casos optima idealmente, pero no asegura nada.
*   **Implementación:** En cada iteración, el algoritmo revisa todos los animes no descartados, 
observa su *siguiente capítulo consecutivo*, y extrae aquel que otorgue el valor de satisfacción $v$
más alto (considerando el bono extra si dicho capítulo es el último del anime). Si el capítulo cabe 
en el tiempo y energía restantes, lo selecciona. Si no cabe, descarta ese anime y sigue evaluando el 
resto.
*   **Complejidad Temporal:** En cada iteración busca el mejor entre los $n$ animes activos, realizando
 a lo sumo $\mathcal{O}(Q)$ selecciones (donde $Q$ es la suma total de todos los capítulos $q_i$).
Esto da un tiempo total de $\mathcal{O}(n \cdot Q)$, lo que lo hace considerablemente mas rapido que 
los demas, a costa de no asegurar una solucion optima.

### 4. Heurística Greedy 2: Mejor ratio de satisfaccion dividido tiempo (`greedy2.cpp`)
*   **Idea General:** Prioriza las opciones de visualización en base a la **rentabilidad de tiempo**,
es decir, escoge la mejor opción según el ratio $v / t$ (Satisfacción sobre Tiempo invertido), al igual
que el otro algoritmo Greedy, no asegura un optimo.
*   **Implementación:** Análogamente al primer Greedy, en cada paso evalúa el siguiente capítulo 
disponible de cada anime activo. Calcula su valor real (incluyendo bonos de completación si corresponde)
 dividido por su costo en minutos $t$. Elige el capítulo con el mayor ratio $v / t$. Si alcanzan los 
 recursos para verlo, lo suma; en caso contrario descarta el anime completo y continúa.
*   **Complejidad Temporal:** Idéntico análisis que el primer Greedy, $\mathcal{O}(n \cdot Q)$, al buscar
 el máximo de una lista de tamaño acotado en cada paso.

---

## <u>Programa Principal y Utilidades</u>

### `general.cpp`
Corresponde al archivo que orquesta toda la ejecución del laboratorio. Se encarga de:
1.  Leer la ruta del archivo del caso de prueba (provista por los archivos `.txt`).
2.  Invocar secuencialmente a los 4 algoritmos implementados.
3.  **Medición Aislada:** Utiliza la función `fork()` para bifurcar un proceso hijo distinto por cada 
algoritmo invocado. Dentro del proceso hijo, se corre el algoritmo, se obtiene su `rusage` (uso de recursos
y memoria) y mediante `wait4` desde el padre, obtenemos el uso de RAM (*Maximum Resident Set Size*) de 
forma limpia y exclusiva para el algoritmo en particular, además del tiempo cronometrado usando llamadas 
precisas.

### `common.h`
Header fundamental para la limpieza del proyecto. Unifica y entrega a todos los archivos los tipos de 
datos principales (`struct Anime`, `struct Capitulo`), además de integrar la lectura y entrega de 
resultados. Esto impide la duplicación innecesaria de funciones en cada código individual.

---

## <u>Scripts</u>

### `testcases_generator.py`
Script en Python responsable de generar de manera automatizada las diversas instancias o escenarios
(Chicos, Medianos, Grandes) respetando el formato y las variables restrictivas ($M, E$, cantidad de 
capítulos, satisfacciones y bonos) estipuladas en el enunciado.

### `plot_generator.py`
Se encarga de leer los reportes generados en `.csv` durante la ejecución de `general.cpp` (las 
mediciones). Con ayuda de librerías como `matplotlib`, genera los gráficos PNG comparativos en 
la carpeta de `plots/` para su posterior inclusión en el informe en formato LaTeX.

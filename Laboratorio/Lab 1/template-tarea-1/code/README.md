===========================================================================================================
#                                         Documentación

===========================================================================================================
Nombre: Vicente Rodríguez Rogers		21.303.222-4	202273503-1	
Fecha:  abril-2026
-----------------------------------------------------------------------------------------------------------

## [Herramientas_Utilizadas]

-----------------------------------------------------------------------------------------------------------
- Visual studio code
-----------------------------------------------------------------------------------------------------------

[Ambiente_de_Ejecución_Usado]

-----------------------------------------------------------------------------------------------------------
- Sistema Operativo usado: Ubuntu 22.04.5 LTS
- Lenguaje: C++
-----------------------------------------------------------------------------------------------------------

## [Entrega]

-----------------------------------------------------------------------------------------------------------
La entrega se realiza vía **aula.usm.cl** en formato `.zip`.

-----------------------------------------------------------------------------------------------------------

## [Multiplicacion_de_Matrices]

-----------------------------------------------------------------------------------------------------------
### Algoritmos:
- **Naive**:
    #### Function:
        void multMat: Realiza multiplicaciones directas, paso por paso y rellena el resultado.
    #### Parameter:
        vector<vector<int>>& m1: Matriz 1 con la que multplicaremos.
        vector<vector<int>>& m2: Matriz 2 con la que multiplicaremos.
        vector<vector<int>>& res: Matriz vacia en la que se registrara el resultado.
    #### Return:
        [None]
- **Strassen**:
    #### Function:
        int nextPowerOf2: Calcula la potencia de 2 más cercana (hacia arriba) para un número dado k.
    #### Parameter:
        int k: El valor entero (dimensión de la matriz) que queremos ajustar.
    #### Return:
        int: El valor de la siguiente potencia de 2 (ej. si entra 3, retorna 4)
    -------------
    #### Function:
        void display: Imprime en la consola el contenido de una matriz con un formato visual de barras 
        laterales.
    #### Parameter:
        vector<vector<int>>& C: La matriz que se desea visualizar.
        int m: Número de filas a mostrar.
        int n: Número de columnas a mostrar.
    #### Return:
        [None]
    -------------
    #### Function:
        void add: Realiza la suma algebraica elemento por elemento de dos matrices cuadradas.
    #### Parameter:
        vector<vector<int>> &A: Primera matriz sumando.
        vector<vector<int>> &B: Segunda matriz sumando.
        vector<vector<int>> &C: Matriz de referencia donde se almacenará el resultado de A+B.
        int size: Dimensión de las matrices.
    #### Return:
        [None]
    -----------
    #### Function:
        void sub: Realiza la resta algebraica elemento por elemento de dos matrices cuadradas.
    #### Parameter:
        vector<vector<int>> &A: Matriz minuendo.
        vector<vector<int>> &B: Matriz sustraendo.
        vector<vector<int>> &C: Matriz de referencia donde se almacenará el resultado de A−B.
        int size: Dimensión de las matrices.
    #### Return:
        [None]
    ----------
    #### Function:
        void Strassen_algorithm: Implementa el núcleo recursivo de Strassen, dividiendo matrices 
        en submatrices y calculando los 7 productos intermedios (P1 a P7).
    #### Parameter:
        vector<vector<int>> &A: Submatriz izquierda de la recursión actual.
        vector<vector<int>> &B: Submatriz derecha de la recursión actual.
        vector<vector<int>> &C: Matriz donde se combinan los resultados de los 7 productos para formar 
        el bloque actual.
        int size: Tamaño actual de la partición (debe ser potencia de 2).
    #### Return:
        [None]
    ---------
    #### Function:
        void ConvertToSquareMat: Actúa como "wrapper" o envoltorio; se encarga de aplicar padding (relleno 
        de ceros) para convertir matrices de cualquier tamaño en cuadradas de potencia 2, llama a Strassen
        y extrae el resultado final.
    #### Parameter:
        vector<vector<int>> &A: Matriz original A.
        vector<vector<int>> &B: Matriz original B.
        int r1: Cantidad de filas de la matriz A.
        int c1: Cantidad de columnas de la matriz A.
        int r2: Cantidad de filas de la matriz B.
        int c2: Cantidad de columnas de la matriz B.
    #### Return:
        [None]

### Consideraciones:
- Tanto el algoritmo Naive como Strassen fueron obtenidos de la pagina www.geeksforgeeks.org
- En el interior de los algoritmo, se puede apreciar la definición de "vii" para señalar vector<vector<int>>
- El codigo original de Strassen pose unos cuantos "unsigned int" que arrojan warning al crear el make file,
y como el contexto lo permite, para ahorranos esos warning fueron trasnforamdos en "int".
-----------------------------------------------------------------------------------------------------------

## [Programa_principal]

-----------------------------------------------------------------------------------------------------------
### Algorimtos:
- **matrix_multiplication.cpp**: Este programa es el encargado de ejecutar los experimentos de multiplicación
de matrices. Recibe como argumentos el algoritmo a utilizar (naive o strassen), las rutas de las dos matrices 
de entrada, el archivo de salida para el resultado y el archivo CSV para registrar las métricas de tiempo y 
memoria. Esta especificamente diseñado para un trabajo directo con los datos de una sola ejecución.
-**Makefile**: En esta situación el make file tiene una funcion importante a la hora de aplicar los 
algoritmos, ya que ademas de conectar con todo los documentos para su correcto funcionamiento, tambien se 
encarga de realizar la iteracion de llamados al codigo 'matrix_multiplication.cpp' para mejorar en eficiencia
todo el sistema y permitir que este ultimo se centre a trabajos puntuales. 

### Consideraciones:
- Antes de correr los algoritmos se recomienda generar los archivos con el codigo /scripts/matriz_generator.py
- En el interior del algoritmo, se puede apreciar la definición de "vii" para señalar vector<vector<int>>
-----------------------------------------------------------------------------------------------------------

## [Scripts]

-----------------------------------------------------------------------------------------------------------
- **`scripts/matrix_generator.py`**: Genera pares de matrices cuadradas aleatorias de dimensiones $2^4$ a $2^{10}$ con diferentes tipos (densas, diagonales, dispersas) y dominios de valores.
- **`scripts/plot_generator.py`**: Procesa los resultados de las mediciones y genera gráficos comparativos para el análisis de complejidad experimental.
-----------------------------------------------------------------------------------------------------------

## [Ordenamiento_de_arreglo_unidimensional]

-----------------------------------------------------------------------------------------------------------
### Algoritmos: 
- **MergeSort**:
    #### Function:
        void merge: Es la función encargada de la "conquista". Toma dos subarreglos adyacentes que ya están
        ordenados internamente y los combina en un único segmento ordenado dentro del arreglo original, 
        utilizando vectores temporales para la comparación.
    #### Parameter:
        vector<int>& arr: El arreglo principal que contiene los elementos a ordenar (se modifica por 
        referencia).
        int left: Índice que marca el inicio del primer subarreglo.
        int mid: Índice que marca el final del primer subarreglo y el punto de división.
        int right: Índice que marca el final del segundo subarreglo.
    #### Return:
        [None]
    ----------
    #### Function:
        void mergeSort: Es la función principal de "división". Utiliza recursión para partir el arreglo en
        mitades cada vez más pequeñas hasta llegar a elementos individuales, para luego invocar a merge y 
        reconstruir el orden.
    #### Parameter:
        vector<int>& arr: El vector de enteros que se desea ordenar.
        int left: El índice del extremo izquierdo del segmento actual a procesar.
        int right: El índice del extremo derecho del segmento actual a procesar.
    ##### Return:
        [None]
- **QuickSort**:
    ##### Function:
        int partition: Es el motor del algoritmo. Selecciona el último elemento como "pivote" y reorganiza
        el vector de modo que todos los elementos menores o iguales al pivote queden a su izquierda, y los 
        mayores a su derecha.
    #### Parameter:
        vector<int> &vec: El vector de enteros que se está procesando (pasado por referencia para modificarlo
        in-place).
        int low: El índice inicial del segmento que se va a particionar.
        int high: El índice final del segmento, que en esta implementación también se usa como la posición 
        del pivote.
    #### Return:
        int: El índice de la posición final donde quedó ubicado el pivote después de la reorganización.
    -----------
    #### Function:
        void quickSort: La función recursiva principal. Utiliza el índice obtenido por partition para dividir 
        el problema en dos sub-problemas más pequeños, llamándose a sí misma para ordenar los elementos a la 
        izquierda y a la derecha del pivote.
    #### Parameter:
        vector<int> &vec: El vector de enteros que se desea ordenar.
        int low: El límite inferior del rango actual de ordenamiento.
        int high: El límite superior del rango actual de ordenamiento.
    #### Return:
        [None]
- **std::sort**:
    #### Function:
        vector<int> sortArray: este llama al sort base de stl "Introsort" y este se encarga basicamente de 
        evitar el peor caso de O(n²) al cambiar de algoritmo segun como va llendo la situacion, empezando
        con un "Quick sort" y usa heapSort o Insertion sort dependiendo de que se va necesitando.
    #### Parameter:
        vector<int>& arr: es el arreglo que se busca ordenar
    #### Return:
        vector<int>:  retorna el arreglo ordenado.

### Consideraciones:
- Tanto el algoritmo MargeSort como QuickSort fueron obtenidos de la pagina www.geeksforgeeks.org
-----------------------------------------------------------------------------------------------------------

## [Programa_principal]

-----------------------------------------------------------------------------------------------------------
- **`code/sorting/sorting.cpp`**: Este programa ejecuta los experimentos de ordenamiento de arreglos. Permite seleccionar entre mergesort, quicksort y std::sort. Mide el tiempo de ejecución y el uso de memoria RAM (RSS) para arreglos de hasta $10^7$ elementos.
-----------------------------------------------------------------------------------------------------------

## [Scripts]

-----------------------------------------------------------------------------------------------------------
- **`scripts/array_generator.py`**: Script en Python que genera los casos de prueba (arreglos ascendentes, descendentes y aleatorios) con tamaños de $10^1$ a $10^7$.
- **`scripts/plot_generator.py`**: Encargado de la visualización de los datos recolectados durante las mediciones de ordenamiento.
-----------------------------------------------------------------------------------------------------------

## [Consideraciones_generales]

-----------------------------------------------------------------------------------------------------------
- Se ha utilizado la función `getrusage` de la cabecera `<sys/resource.h>` para obtener el uso máximo de memoria residente (Resident Set Size), lo cual proporciona una medida precisa del impacto de cada algoritmo en el sistema.
- Los archivos de salida (*_out.txt) contienen los resultados finales para validar la corrección de las implementaciones.
- Los tiempos se miden utilizando `std::chrono::high_resolution_clock` para garantizar precisión de microsegundos.
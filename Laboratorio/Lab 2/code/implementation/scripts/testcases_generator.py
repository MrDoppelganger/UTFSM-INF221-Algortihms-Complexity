#----------------------------------Librerias------------------------------
import os
import random
import time

#----------------------------------Funciones------------------------------
'''
    ------------Funcion-----------------
    escribirCasoPrueba: 
        Funcion encargada de escribir los datos de la instancia
        simulada dentro de un documento .txt, siguiendo el formato
        descrito en el enunciado de la tarea.
    ------------Parametros----------------
    str ruta_archivo: Ruta al documento .txt
    int n: Numero de animes.
    int M: Tiempo maximo disponible.
    int E: Energia maxima disponible.
    list animes: Lista de diccionarios, cada uno con los datos de un anime.
    --------------Return------------------
    void: No retorna nada.
    ----------------------------------
'''
def escribirCasoPrueba(ruta_archivo, n, M, E, animes):
    with open(ruta_archivo, 'w') as documento:
        documento.write(f"{n} {M} {E}\n")
        
        for anime in animes:
            documento.write(f"{anime['nombre']} {anime['q']} {anime['b']}\n")
            for capitulo in anime['capitulos']:
                documento.write(f"{capitulo['t']} {capitulo['c']} {capitulo['v']}\n")

'''
    ------------Funcion-----------------
    generarInstancia: Funcion encargada de crear aleatoriamente los datos 
    de una sola instancia del problema AniMarathon y luego escribirla
    en el documento instanciado usando "escribirCasoPrueba".
    ------------Parametros----------------
    str tipo: tipo de rango de generacion de instancias 'Chica', 'Mediana' 
        o 'Grande'.
    int num: Identificador de la instancia.
    str carpeta_objetivo: Carpeta donde se guardara.
    --------------Return------------------
    void: No retorna nada.
    ----------------------------------
'''
def generarInstancia(tipo, num, carpeta_objetivo):
    #--------------------------Generacion de parametros base---------------------------
    if tipo == 'Chica':     
        n = random.randint(3, 8)
        max_capitulos = 5
    elif tipo == 'Mediana':
        n = random.randint(20, 80)
        max_capitulos = 8
    else: # Grande
        n = random.randint(100, 200)
        max_capitulos = 12

    #---------------------------Generacion de animes----------------------------
    animes = []
    tiempo_total_estimado = 0
    energia_total_estimada = 0

    for i in range(1, n + 1):
        anime_data = {}
        anime_data['nombre'] = f"anime_{tipo.lower()}_{i}"
        
        q = random.randint(1, max_capitulos)
        anime_data['q'] = q
        anime_data['b'] = random.randint(10, 200) # Bono por completar
        
        capitulos = []
        for j in range(1, q + 1):
            t = random.randint(1, 10) # Duracion del capitulo
            c = random.randint(1, 10)  # Costo de energia
            v = random.randint(10, 100) # Satisfaccion
            
            capitulos.append({'t': t, 'c': c, 'v': v})
            
            tiempo_total_estimado += t
            energia_total_estimada += c
            
        anime_data['capitulos'] = capitulos
        animes.append(anime_data)

    # Restringimos M y E para que no sea trivial (el usuario no puede ver todo)
    # y para que los algoritmos tengan que elegir
    M = int(tiempo_total_estimado * random.uniform(0.4, 0.6))
    E = int(energia_total_estimada * random.uniform(0.4, 0.6))

    # Asegurar que al menos M y E sean minimos para ver algo
    M = max(M, 10)
    E = max(E, 10)

    # ----------------------------------Guardado---------------------------------------
    nombre_archivo = f"testcases_{n}_{num}.txt"
    ruta_completa = os.path.join(carpeta_objetivo, nombre_archivo)
    
    escribirCasoPrueba(ruta_completa, n, M, E, animes)

def main():
    #------------------Inicializacion---------------------------
    # Forzamos una nueva semilla aleatoria basándonos en el tiempo exacto de ejecución
    random.seed(time.time()) 
    
    # Obtiene la ruta absoluta de la carpeta 'scripts' y luego sube un nivel hacia 'data/inputs'
    script_dir = os.path.dirname(os.path.abspath(__file__))
    carpeta_objetivo_destino = os.path.join(script_dir, "..", "data", "inputs")
    
    # Crea la carpeta automáticamente si es que no existe en el directorio
    os.makedirs(carpeta_objetivo_destino, exist_ok=True)
    
    # Definimos los tipos de instancias requeridos
    tipos_instancias = ['Chica', 'Mediana', 'Grande']

    #------------------Procesamiento---------------------------
    print("Generando las instancias...")
    
    total_generadas = 0
    for tipo in tipos_instancias:
        # Se solicitan multiples instancias por cada dimensionalidad
        # Por ejemplo, 5 de cada una
        for i in range(1, 6):
            generarInstancia(tipo, i, carpeta_objetivo_destino)
            total_generadas += 1
            
    print(f"Proceso finalizado. Se generaron {total_generadas} instancias en la carpeta '{carpeta_objetivo_destino}'.")

if __name__ == "__main__":
    main()
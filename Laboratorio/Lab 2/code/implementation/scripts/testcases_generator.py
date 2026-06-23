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
    generarInstancia: 
        Funcion encargada de crear aleatoriamente los datos 
        de una sola instancia del problema y luego escribirla
        en el documento llamando a "escribirCasoPrueba".
    ------------Parametros----------------
    str tipo: tipo de rango de generacion de instancias "Chica", "Mediana" o "Grande".
    int num: Identificador de la instancia.
    str carpeta_objetivo: Carpeta donde se guardara.
    --------------Return------------------
    void: No retorna nada.
    ----------------------------------
'''
def generarInstancia(tipo, num, carpeta_objetivo):
    # Generacion de parametros base
    if tipo == 'Chica':     
        n = random.randint(3, 8)
        max_capitulos = 5
    elif tipo == 'Mediana':
        n = random.randint(20, 80)
        max_capitulos = 8
    else:
        n = random.randint(100, 200)
        max_capitulos = 12

    #---------------------------Generacion de animes----------------------------
    animes = []
    tiempo_total_estimado = 0
    energia_total_estimada = 0
    capitulos_totales = 0 # Agregamos un contador para Q

    for i in range(1, n + 1):
        anime_data = {}
        anime_data['nombre'] = f"anime_{tipo.lower()}_{i}"
        
        q = random.randint(1, max_capitulos)
        
        # Evitamos pasarnos del limite Q = 700
        if capitulos_totales + q > 700:
            q = max(0, 700 - capitulos_totales)
            if q == 0:
                continue # Ya no agregamos mas animes si llegamos a 700
        
        capitulos_totales += q
        
        anime_data['q'] = q
        # Aumentamos el rango de los bonos
        anime_data['b'] = random.randint(0, 100000000) 
        
        capitulos = []
        for j in range(1, q + 1):
            # Aprovechamos mejor los limites del enunciado
            tiempo = random.randint(1, 300)              
            costo = random.randint(1, 100)               
            satisfaccion = random.randint(1, 100000000)      
            
            capitulos.append({'t': tiempo, 'c': costo, 'v': satisfaccion})
            
            tiempo_total_estimado += tiempo
            energia_total_estimada += costo
            
        anime_data['capitulos'] = capitulos
        animes.append(anime_data)

    # Restringimos M y E con el calculo original, pero lo "capeamos" al limite maximo exigido
    M = int(tiempo_total_estimado * random.uniform(0.4, 0.6))
    E = int(energia_total_estimada * random.uniform(0.4, 0.6))

    #establecemos los rangos de cada uno
    M = min(max(M, 10), 3000) 
    E = min(max(E, 10), 500) 

    # Arreglamos el formato del nombre del archivo testcases_{n}_{i}.txt
    nombre_archivo = f"testcases_{n}_{num}.txt"
    ruta_completa = os.path.join(carpeta_objetivo, nombre_archivo)
    
    # Actualizamos el 'n' por si se descartaron animes al superar los 700 caps
    n_real = len(animes)
    escribirCasoPrueba(ruta_completa, n_real, M, E, animes)
    escribirCasoPrueba(ruta_completa, n, M, E, animes)

def main():
    #------------------Inicializacion---------------------------
    # Creamos una semilla para esta instancia especifica
    random.seed(time.time()) 
    # Establecemos la direccion de los test
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
        # Generamos 5 instancias para tener casos de pruebas.
        for i in range(1, 6):
            generarInstancia(tipo, i, carpeta_objetivo_destino)
            total_generadas += 1
            
    print(f"Proceso finalizado. Se generaron {total_generadas} instancias en la carpeta '{carpeta_objetivo_destino}'.")

if __name__ == "__main__":
    main()
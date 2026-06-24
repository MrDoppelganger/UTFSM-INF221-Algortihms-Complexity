import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

def generar_graficos():
    #-------------------------------Inicializacion-----------------------------------
    # Establecemos la direccion de los graficos
    script_dir = os.path.dirname(os.path.abspath(__file__))
    csv_path = os.path.join(script_dir, "..", "data", "measurements", "measurements.csv")
    plots_dir = os.path.join(script_dir, "..", "data", "plots")
    # Nos aseguramos de que exista la carpeta de llegada
    os.makedirs(plots_dir, exist_ok=True)

    # Leemos el archivo CSV
    if not os.path.exists(csv_path):
        print(f"Error: No se encontró el archivo CSV en {csv_path}")
        return
    df = pd.read_csv(csv_path)

    # Ordenar por N para que los gráficos de línea se vean bien
    df = df.sort_values(by="N")

    # Obtener lista de algoritmos
    algoritmos = df['Algoritmo'].unique()
    
    # Configuración de estilo
    sns.set_theme(style="whitegrid")
    
    colores = {
        'BruteForce': '#d62728', # Rojo
        'DP': '#1f77b4',         # Azul
        'Greedy(v)': '#2ca02c',  # Verde
        'Greedy(v/t)': '#ff7f0e' # Naranja
    }

    #-----------------------------Graficos--------------------------------------------
    
    # Gráficos Individuales de Tiempo vs N
    for algo in algoritmos:
        plt.figure(figsize=(10, 6))
        data_algo = df[df['Algoritmo'] == algo]
        sns.lineplot(data=data_algo, x='N', y='Tiempo_ms', marker='o', color=colores.get(algo, 'black'))
        plt.title(f'Tiempo de Ejecución vs Tamaño de Entrada (N) - {algo}')
        plt.xlabel('Número de Animes (N)')
        plt.ylabel('Tiempo de Ejecución (ms)')
        plt.tight_layout()
        nombre_seguro = algo.lower().replace('/', '_')
        plt.savefig(os.path.join(plots_dir, f'tiempo_{nombre_seguro}.png'))
        plt.close()

    # Gráficos Individuales de Memoria vs N
    for algo in algoritmos:
        plt.figure(figsize=(10, 6))
        data_algo = df[df['Algoritmo'] == algo]
        sns.lineplot(data=data_algo, x='N', y='Memoria_KB', marker='s', color=colores.get(algo, 'black'))
        plt.title(f'Uso de Memoria vs Tamaño de Entrada (N) - {algo}')
        plt.xlabel('Número de Animes (N)')
        plt.ylabel('Uso de Memoria (KB)')
        plt.tight_layout()
        nombre_seguro = algo.lower().replace('/', '-div-')
        plt.savefig(os.path.join(plots_dir, f'memoria_{nombre_seguro}.png'))
        plt.close()

    # Gráfico Comparativo de Tiempos
    plt.figure(figsize=(12, 7))
    sns.lineplot(data=df, x='N', y='Tiempo_ms', hue='Algoritmo', style='Algoritmo', markers=True, dashes=False, palette=colores)
    plt.title('Comparación de Tiempo de Ejecución entre Enfoques')
    plt.xlabel('Número de Animes (N)')
    plt.ylabel('Tiempo de Ejecución (ms) [Log Scale]')
    plt.yscale('log')
    plt.tight_layout()
    plt.savefig(os.path.join(plots_dir, 'comparativa_tiempos.png'))
    plt.close()

    # Gráfico Comparativo de Memoria
    plt.figure(figsize=(12, 7))
    sns.lineplot(data=df, x='N', y='Memoria_KB', hue='Algoritmo', style='Algoritmo', markers=True, dashes=False, palette=colores)
    plt.title('Comparación de Uso de Memoria entre Enfoques')
    plt.xlabel('Número de Animes (N)')
    plt.ylabel('Uso de Memoria (KB) [Log Scale]')
    plt.yscale('log')
    plt.tight_layout()
    plt.savefig(os.path.join(plots_dir, 'comparativa_memoria.png'))
    plt.close()

    # Gráfico Comparativo de Satisfacción (% del Óptimo)
    plt.figure(figsize=(12, 7))
    
    # Extraemos el 100% (La solución óptima dada por la Programación Dinámica)
    if 'DP' in algoritmos:
        df_optimos = df[df['Algoritmo'] == 'DP'][['Instancia', 'Satisfaccion']].rename(columns={'Satisfaccion': 'Sat_Optima'})
        df_merged = pd.merge(df, df_optimos, on='Instancia')
        
        # Calculamos el porcentaje
        df_merged['Calidad_%'] = (df_merged['Satisfaccion'] / df_merged['Sat_Optima']) * 100
        
        # Graficamos solo las heurísticas Greedy para ver qué tan cerca llegaron del 100%
        df_greedy = df_merged[df_merged['Algoritmo'].isin(['Greedy(v)', 'Greedy(v/t)'])]
        
        if not df_greedy.empty:
            sns.lineplot(data=df_greedy, x='N', y='Calidad_%', hue='Algoritmo', style='Algoritmo', markers=True, dashes=False, palette=colores)
            plt.axhline(100, color='red', linestyle='--', label='Óptimo (100%)', alpha=0.5) # Línea de referencia del óptimo
            plt.title('Calidad de la Solución de Heurísticas Greedy (% respecto al Óptimo)')
            plt.xlabel('Número de Animes (N)')
            plt.ylabel('% de Satisfacción Óptima')
            plt.ylim(0, 110) # Para dar un poco de margen superior
            plt.legend()
            plt.tight_layout()
            plt.savefig(os.path.join(plots_dir, 'comparativa_calidad_porcentaje.png'))
    plt.close()

    # Gráfico Scatter: Tiempo vs Capítulos (Q)
    if 'Q' in df.columns:
        plt.figure(figsize=(12, 7))
        sns.scatterplot(data=df, x='Q', y='Tiempo_ms', hue='Algoritmo', style='Algoritmo', palette=colores, s=80, alpha=0.7)
        plt.title('Impacto de la Cantidad de Capítulos (Q) en el Tiempo de Ejecución')
        plt.xlabel('Cantidad Total de Capítulos (Q)')
        plt.ylabel('Tiempo de Ejecución (ms) [Escala logarítmica]')
        plt.yscale('log')
        plt.tight_layout()
        plt.savefig(os.path.join(plots_dir, 'Dispersión_tiempo_vs_Cantidad_total_de_capitulos.png'))
        plt.close()
    else:
        print("Aviso: No se encontró la columna 'Q' en el CSV. Omita graficar Tiempo vs Capítulos.")

    # Gráfico Scatter: Memoria vs Minutos Disponibles (M)
    plt.figure(figsize=(12, 7))
    sns.scatterplot(data=df, x='M', y='Memoria_KB', hue='Algoritmo', style='Algoritmo', palette=colores, s=80, alpha=0.7)
    plt.title('Impacto de los Minutos Disponibles (M) en el Uso de Memoria')
    plt.xlabel('Minutos Máximos (M)')
    plt.ylabel('Uso de Memoria (KB) [Escala logarítmica]')
    plt.yscale('log')
    plt.tight_layout()
    plt.savefig(os.path.join(plots_dir, 'Dispersión_memoria_vs_Minutos_disponibles.png'))
    plt.close()

    # Gráfico Scatter: Memoria vs Energía Disponible (E)
    plt.figure(figsize=(12, 7))
    sns.scatterplot(data=df, x='E', y='Memoria_KB', hue='Algoritmo', style='Algoritmo', palette=colores, s=80, alpha=0.7)
    plt.title('Impacto de la Energía Disponible (E) en el Uso de Memoria')
    plt.xlabel('Energía Máxima (E)')
    plt.ylabel('Uso de Memoria (KB) [Escala logarítmica]')
    plt.yscale('log')
    plt.tight_layout()
    plt.savefig(os.path.join(plots_dir, 'Dispersión_memoria_vs_Energia_disponible.png'))
    plt.close()

    print(f"¡Se han generado todos los gráficos exitosamente en la carpeta: {plots_dir}!")

if __name__ == '__main__':
    generar_graficos()
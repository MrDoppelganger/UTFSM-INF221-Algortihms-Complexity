import pandas as pd
import matplotlib.pyplot as plt
import os

# Configuración de rutas
script_dir = os.path.dirname(os.path.abspath(__file__))
results_path = os.path.join(script_dir, "..", "data", "measurements", "results.csv")
plots_dir = os.path.join(script_dir, "..", "data", "plots")

# Asegurar que el directorio de plots existe
os.makedirs(plots_dir, exist_ok=True)

def generate_plots():
    if not os.path.exists(results_path):
        print(f"Error: No se encontró el archivo de resultados en {results_path}")
        return

    # Cargar datos
    df = pd.read_csv(results_path)
    
    # Agrupar por algoritmo y tamaño, calculando el promedio
    df_grouped = df.groupby(['algorithm', 'n']).mean().reset_index()
    
    # Separar datos por algoritmo
    mergesort_data = df_grouped[df_grouped['algorithm'] == 'mergesort']
    quicksort_data = df_grouped[df_grouped['algorithm'] == 'quicksort']
    stdsort_data = df_grouped[df_grouped['algorithm'] == 'stdsort']

    # Estilo de los gráficos
    plt.style.use('bmh')
    colors = {
        'mergesort': '#2ecc71', # Verde
        'quicksort': '#f1c40f', # Amarillo
        'stdsort': '#9b59b6'   # Púrpura
    }

    # 1. Gráfico de Tiempo de Ejecución
    plt.figure(figsize=(10, 6))
    plt.plot(mergesort_data['n'], mergesort_data['time_seconds'], marker='o', label='MergeSort', color=colors['mergesort'], linewidth=2)
    plt.plot(quicksort_data['n'], quicksort_data['time_seconds'], marker='s', label='QuickSort', color=colors['quicksort'], linewidth=2)
    plt.plot(stdsort_data['n'], stdsort_data['time_seconds'], marker='^', label='std::sort', color=colors['stdsort'], linewidth=2)
    
    plt.title('Comparación de Tiempo de Ejecución: Algoritmos de Ordenamiento', fontsize=14, fontweight='bold', pad=15)
    plt.xlabel('Tamaño del Arreglo (n)', fontsize=12)
    plt.ylabel('Tiempo (segundos)', fontsize=12)
    plt.xscale('log')
    plt.yscale('log')
    plt.grid(True, which="both", ls="-", alpha=0.5)
    plt.legend(fontsize=11)
    
    time_plot_path = os.path.join(plots_dir, "sorting_time_comparison.png")
    plt.tight_layout()
    plt.savefig(time_plot_path, dpi=300)
    print(f"Gráfico de tiempo guardado en: {time_plot_path}")
    plt.close()

    # 2. Gráfico de Uso de Memoria
    plt.figure(figsize=(10, 6))
    plt.plot(mergesort_data['n'], mergesort_data['memory_kb'] / 1024, marker='o', label='MergeSort', color=colors['mergesort'], linewidth=2)
    plt.plot(quicksort_data['n'], quicksort_data['memory_kb'] / 1024, marker='s', label='QuickSort', color=colors['quicksort'], linewidth=2)
    plt.plot(stdsort_data['n'], stdsort_data['memory_kb'] / 1024, marker='^', label='std::sort', color=colors['stdsort'], linewidth=2)
    
    plt.title('Comparación de Uso de Memoria: Algoritmos de Ordenamiento', fontsize=14, fontweight='bold', pad=15)
    plt.xlabel('Tamaño del Arreglo (n)', fontsize=12)
    plt.ylabel('Memoria (MB)', fontsize=12)
    plt.xscale('log')
    plt.grid(True, which="both", ls="-", alpha=0.5)
    plt.legend(fontsize=11)
    
    memory_plot_path = os.path.join(plots_dir, "sorting_memory_comparison.png")
    plt.tight_layout()
    plt.savefig(memory_plot_path, dpi=300)
    print(f"Gráfico de memoria guardado en: {memory_plot_path}")
    plt.close()

if __name__ == "__main__":
    generate_plots()

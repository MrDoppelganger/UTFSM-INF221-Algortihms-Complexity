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
    naive_data = df_grouped[df_grouped['algorithm'] == 'naive']
    strassen_data = df_grouped[df_grouped['algorithm'] == 'strassen']

    # Estilo de los gráficos
    plt.style.use('bmh') # Estilo limpio y profesional
    # Colores personalizados (usando HSL-like para un look premium)
    naive_color = '#3498db'  # Azul suave
    strassen_color = '#e74c3c' # Rojo suave

    # 1. Gráfico de Tiempo de Ejecución
    plt.figure(figsize=(10, 6))
    plt.plot(naive_data['n'], naive_data['time_seconds'], marker='o', linestyle='-', color=naive_color, label='Naive', linewidth=2, markersize=8)
    plt.plot(strassen_data['n'], strassen_data['time_seconds'], marker='s', linestyle='-', color=strassen_color, label='Strassen', linewidth=2, markersize=8)
    
    plt.title('Comparación de Tiempo de Ejecución: Naive vs Strassen', fontsize=14, fontweight='bold', pad=15)
    plt.xlabel('Tamaño de la Matriz (n x n)', fontsize=12)
    plt.ylabel('Tiempo (segundos)', fontsize=12)
    plt.xscale('log', base=2)
    plt.yscale('log') # Escala logarítmica para ver mejor la diferencia de crecimientos
    plt.grid(True, which="both", ls="-", alpha=0.5)
    plt.legend(fontsize=11)
    
    time_plot_path = os.path.join(plots_dir, "time_comparison.png")
    plt.tight_layout()
    plt.savefig(time_plot_path, dpi=300)
    print(f"Gráfico de tiempo guardado en: {time_plot_path}")
    plt.close()

    # 2. Gráfico de Uso de Memoria
    plt.figure(figsize=(10, 6))
    plt.plot(naive_data['n'], naive_data['memory_kb'] / 1024, marker='o', linestyle='--', color=naive_color, label='Naive', linewidth=2, markersize=8)
    plt.plot(strassen_data['n'], strassen_data['memory_kb'] / 1024, marker='s', linestyle='--', color=strassen_color, label='Strassen', linewidth=2, markersize=8)
    
    plt.title('Comparación de Uso de Memoria: Naive vs Strassen', fontsize=14, fontweight='bold', pad=15)
    plt.xlabel('Tamaño de la Matriz (n x n)', fontsize=12)
    plt.ylabel('Memoria (MB)', fontsize=12)
    plt.xscale('log', base=2)
    # plt.yscale('log') # Memoria suele ser más lineal en este rango, dejamos escala normal para contrastar mejor
    plt.grid(True, which="both", ls="-", alpha=0.5)
    plt.legend(fontsize=11)
    
    memory_plot_path = os.path.join(plots_dir, "memory_comparison.png")
    plt.tight_layout()
    plt.savefig(memory_plot_path, dpi=300)
    print(f"Gráfico de memoria guardado en: {memory_plot_path}")
    plt.close()

if __name__ == "__main__":
    generate_plots()

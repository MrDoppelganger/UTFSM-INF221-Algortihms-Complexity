# Tarea 2: AniMarathon - Optimización de visualización de Anime

> **Universidad:** Universidad Técnica Federico Santa María (UTFSM)  
> **Curso:** Algoritmos y Complejidad (INF221) — 1° Semestre/2026  
> **Estudiante:**
> * Vicente Rodríguez Rogers
>
> **Fecha:** Junio, 2026

---

Este es el README principal del repositorio para la Tarea 2 del ramo Algoritmos y Complejidad. Aquí 
se encuentra toda la documentación general, el código fuente y las instrucciones necesarias para 
levantar las pruebas y el entorno completo del proyecto.

## Estructura del Repositorio

```bash
├── assignment_statement/                   # Enunciado y fuente LaTeX original.
├── code/                                   # Código fuente de las implementaciones.
│   ├── implementation/
│   │   ├── algorithms/                     # Códigos de los 4 algoritmos (Brute Force, DP, Greedys).
│   │   ├── data/                           # Datos generados (measurements, outputs, plots).
│   │   └── scripts/                        # Scripts Python (Generador de casos, gráficos).
│   └── README.md                           # Documentación específica de la implementación.
├── Docs/                                   # Documentos extras e ideas del proyecto.
├── report/                                 # Informe final y código LaTeX.
└── README.md                               # Este documento.
```
---
## Herramientas Utilizadas

* **Control de Versiones:** Github
* **Editor:** Visual Studio Code, Overleaf

## Ambientes de Ejecución

* **Sistemas Operativos:** 
    * Ubuntu 22.04.5 LTS (WSL2 o Nativo)

## Instrucciones de ejecución:
*   Abrir una terminal dentro del entorno `../Lab2/code/implementation/`
*   Ejecutar el comando `make clean_all` para limpiar el espacio de ejecuciones previas
*   Ejecutar el comando `make` Para crear el ejecutable.
*   Ejecutar el comando `make generate_data` para crear los inputs de prueba
*   Ejecutar el comando `make run_tests` para correr los algoritmos
*   **(Opcional)** Ejecutar el comando `make generate_plots` para crear las graficas de los resultados

## Consideraciones

*   **Archivos de compilación (Makefiles):** Se implementó en el Makefile que todos los archivos 
generados se  guardaran en una carpeta designada  ***build/*** (A excepcion del ejecutable principal) 
para de mantener la limpieza del repositorio y no ensuciar la raíz del proyecto ni la de los códigos.
Ademas se posee distintos comandos en el Makefile para realizar limpiezas especificas por si se llega a
requerir.

*   **Header comun (`common.h`):** Para mantener un proyecto profesional y modular, se creó un archivo 
`common.h` de este modo nos aseguramos de evitar la redundancia de código y reutilizar componentes esenciales
a lo largo de los cuatro algoritmos, como la estructura de los capítulos y los animes, además de estandarizar
la entrada y salida de datos (lectura de `.txt` y escritura a archivos `.csv`).

*   **Medición aislada con `fork()`:** Se integró en **general.cpp** el uso de ***fork***, ya que nos permite
 ejecutar la medición de memoria de cada algoritmo de manera completamente aislada en procesos hijos, evitando
que el consumo de memoria dinámico generado por ejecuciones previas (o por la propia lectura del caso de prueba)
afecte a las demás, obteniendo así métricas de memoria mas precisas para el análisis.

# -*- coding: utf-8 -*-
"""
Gestor de notas por clase (CSV) con gráficos.
- Crea CSV por clase con las materias que elija el profesor.
- Carga/actualiza notas de alumnos y guarda en CSV (pandas).
- Visualiza:
    * Boxplot de los promedios generales por alumno.
    * Barras del promedio general por alumno (incluye línea del promedio de la clase).
Requisitos: pandas, matplotlib, seaborn
"""

import os
import sys
import re

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

CARPETA_CLASES = "clases"
ENCODING_CSV = "utf-8" 
MIN_NOTA = 0.0
MAX_NOTA = 10.0


sns.set(style="whitegrid", palette="deep", font_scale=1.1)


def asegurar_carpeta_clases():
    if not os.path.exists(CARPETA_CLASES): #revisa si la ruta existe
        os.makedirs(CARPETA_CLASES) #si no existe la ruta la crea


def listar_csv_clases():
    asegurar_carpeta_clases()
    archivos = [f for f in os.listdir(CARPETA_CLASES) if f.lower().endswith(".csv")]
    archivos.sort()
    return archivos


def ruta_clase(nombre_archivo):
    return os.path.join(CARPETA_CLASES, nombre_archivo)#retorna la ruta completa y pone las separaciones dependiendo del sistema operativo


def crear_csv_clase():
    print("\n🟢🟢🟢Crear nueva clase (CSV)🟢🟢🟢")
    while(nombre == None):
        nombre = input("Nombre de la clase: ").strip()
        if  re.search(r'[^A-Za-z0-9_]', nombre):
            print("⚠️⚠️⚠️Nombre de clase inválido⚠️⚠️⚠️.")
            print("Use solo letras, números y guiones bajos (_).")
            print("ingrese otro nombre.")
            nombre = None

    nombre_archivo = nombre + ".csv"
    archivo = ruta_clase(nombre_archivo)

    if os.path.exists(archivo):
        print(f"⚠️⚠️⚠️Ya existe un CSV para esa clase: {archivo}⚠️⚠️⚠️")
        return None

    while(cant == None):
        cant = int(input("¿Cuántas materias tiene la clase?: ").strip())
        if cant <= 0:
            print("⚠️⚠️⚠️La cantidad debe ser mayor a 0.⚠️⚠️⚠️")
            print("ingrese otra cantidad.")
            cant = None

    materias = []
    for i in range(cant):
        while(nombre_materia == None):
            nombre_materia = input(f"Nombre de la materia #{i+1}: ").strip()
            if re.search(r'[^A-Za-z0-9_]', nombre_materia):
                print("⚠️⚠️⚠️Nombre de materia inválido.⚠️⚠️⚠️")
                nombre_materia = None
        materias.append(nombre_materia)

    columnas = ["Alumno ID", "Alumno"] + materias
    df = pd.DataFrame(columns=columnas)
    df.to_csv(archivo, index=False, encoding=ENCODING_CSV)
    print(f"✅✅✅ Clase creada: {archivo}✅✅✅")



#///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

def cargar_df_clase(archivo):
    ruta_clase(archivo)
    try:
        df = pd.read_csv(archivo, encoding=ENCODING_CSV)
    except FileNotFoundError:
        print(f"⚠️⚠️⚠️No se encontro el archivo: {archivo}⚠️⚠️⚠️")
        return None

    if "Alumno" not in df.columns:
        raise ValueError("El CSV no tiene columna Alumno.") #lanza una excepción al detectar que falta la columna alumno
    if "Alumno ID" not in df.columns:
        raise ValueError("El CSV no tiene columna Alumno ID.") # lanza una exepción al detectar que falta la columna alumno ID

    return df


def guardar_df_clase(df, archivo):
    ruta = ruta_clase(archivo)
    df.to_csv(ruta, index=False, encoding=ENCODING_CSV)


# ========= Entrada y validación de notas =========
def pedir_float_o_vacio(prompt, minimo, maximo):
    """
    Devuelve:
        - float dentro del rango [minimo, maximo]
        - None si el usuario deja en blanco
    """
    while True:
        s = input(prompt).strip().replace(",", ".")
        if s == "":
            return None
        try:
            v = float(s)
            if v < minimo or v > maximo:
                print(f"   ⚠️  Debe estar entre {minimo} y {maximo}.")
                continue
            return v
        except ValueError:
            print("   ⚠️  Ingrese un número válido o deje en blanco.")


# ========= Gestión de alumnos y notas =========
def seleccionar_clase():
    archivos = listar_csv_clases()
    if not archivos:
        print("⚠️  No hay clases aún. Cree una con 'Crear nueva clase'.")
        return None
    print("\n=== Clases disponibles ===")
    for i, f in enumerate(archivos, start=1):
        print(f"{i}. {f}")
    try:
        idx = int(input("Seleccione una clase por número: ").strip())
        if 1 <= idx <= len(archivos):
            return archivos[idx - 1]
    except ValueError:
        pass
    print("⚠️  Selección inválida.")
    return None


def materias_de_df(df):
    # Materias = todas las columnas excepto 'Alumno ID' y 'Alumno'
    return [c for c in df.columns if c not in ("Alumno ID", "Alumno")]


def agregar_o_actualizar_notas():
    print("\n=== Cargar/actualizar notas de una clase ===")
    archivo = seleccionar_clase()
    if not archivo:
        return

    df = cargar_df_clase(archivo)
    materias = materias_de_df(df)
    if not materias:
        print("⚠️  No hay materias en este CSV. Cree la clase de nuevo con materias.")
        return

    print("\nInstrucciones:")
    print("- Puede agregar un alumno nuevo o actualizar uno existente.")
    print("- Deje en blanco una nota para conservar el valor actual o para no cargarla aún.")
    print(f"- Rango de notas permitido: {MIN_NOTA} a {MAX_NOTA}.")

    while True:
        print("\n--- Alumno ---")
        alumno_id = input("Alumno ID (opcional, puede dejar en blanco): ").strip()
        alumno = input("Nombre y apellido del alumno: ").strip()
        if not alumno:
            print("⚠️  El nombre es obligatorio.")
            continue

        # Buscar si ya existe por Alumno o Alumno ID
        idx_exist = None
        if alumno_id:
            coincide = df.index[(df["Alumno ID"].astype(str) == alumno_id)]
            if len(coincide) > 0:
                idx_exist = coincide[0]
        if idx_exist is None:
            coincide = df.index[(df["Alumno"].astype(str).str.lower() == alumno.lower())]
            if len(coincide) > 0:
                idx_exist = coincide[0]

        if idx_exist is None:
            # Crear nueva fila
            nueva = {c: pd.NA for c in df.columns}
            nueva["Alumno ID"] = alumno_id if alumno_id else pd.NA
            nueva["Alumno"] = alumno
            for m in materias:
                nueva[m] = pd.NA
            df = pd.concat([df, pd.DataFrame([nueva])], ignore_index=True)
            idx = df.index[-1]
            print(f"➕ Alumno agregado: {alumno}")
        else:
            idx = idx_exist
            print(f"✏️  Actualizando alumno existente: {df.at[idx, 'Alumno']}")

        # Cargar/actualizar materias
        for m in materias:
            actual = df.at[idx, m]
            muestra = f" (actual: {actual})" if pd.notna(actual) else ""
            val = pedir_float_o_vacio(f"   Nota en '{m}'{muestra}: ", MIN_NOTA, MAX_NOTA)
            if val is not None:
                df.at[idx, m] = val

        # Guardar cambios
        guardar_df_clase(df, archivo)
        print("💾 Cambios guardados.")

        otra = input("¿Desea cargar/actualizar otro alumno? (s/n): ").strip().lower()
        if otra != "s":
            break


# ========= Promedios y gráficos =========
def promedios_por_alumno(df):
    materias = materias_de_df(df)
    if not materias:
        raise ValueError("No hay materias para calcular promedios.")

    # Convertir materias a numérico (forzar errores a NaN), por si hay celdas con texto
    df_num = df.copy()
    for m in materias:
        df_num[m] = pd.to_numeric(df_num[m], errors="coerce")

    # Promedio por alumno (ignorando NaN)
    promedios = df_num[materias].mean(axis=1, skipna=True)
    out = df_num[["Alumno ID", "Alumno"]].copy()
    out["Promedio General"] = promedios
    # Filtrar alumnos sin ninguna nota (promedio NaN)
    out = out[pd.notna(out["Promedio General"])]
    return out


def graficar_boxplot_promedios(df_promedios, nombre_clase):
    plt.figure(figsize=(8, 5))
    # Boxplot de los promedios generales (1 dimensión)
    sns.boxplot(x=df_promedios["Promedio General"], color="#4C72B0")
    # Agregar puntos individuales
    sns.stripplot(x=df_promedios["Promedio General"], color="#DD8452", alpha=0.7)

    plt.title(f"Distribución de promedios generales - {nombre_clase}")
    plt.xlabel("Promedio general (todas las materias)")
    plt.tight_layout()

    # Guardar imagen
    asegurar_carpeta_clases()
    salida = os.path.join(CARPETA_CLASES, f"{os.path.splitext(nombre_clase)[0]}_boxplot_promedios.png")
    plt.savefig(salida, dpi=150)
    print(f"🖼️  Gráfico guardado en: {salida}")
    plt.show()


def graficar_barras_promedios(df_promedios, nombre_clase):
    df_plot = df_promedios.sort_values("Promedio General", ascending=False)
    plt.figure(figsize=(10, 6))
    sns.barplot(data=df_plot, x="Alumno", y="Promedio General")

    # Línea del promedio de la clase (del promedio de promedios)
    promedio_clase = df_plot["Promedio General"].mean()
    plt.axhline(promedio_clase, color="red", linestyle="--", alpha=0.7, label=f"Promedio de la clase: {promedio_clase:.2f}")

    plt.title(f"Promedio general por alumno - {nombre_clase}")
    plt.xlabel("Alumno")
    plt.ylabel("Promedio general (todas las materias)")
    plt.xticks(rotation=45, ha="right")
    plt.legend()
    plt.tight_layout()

    # Guardar imagen
    asegurar_carpeta_clases()
    salida = os.path.join(CARPETA_CLASES, f"{os.path.splitext(nombre_clase)[0]}_barras_promedios.png")
    plt.savefig(salida, dpi=150)
    print(f"🖼️  Gráfico guardado en: {salida}")
    plt.show()


def ver_graficos_clase():
    print("\n=== Ver gráficos de una clase ===")
    archivo = seleccionar_clase()
    if not archivo:
        return

    df = cargar_df_clase(archivo)
    try:
        df_prom = promedios_por_alumno(df)
    except ValueError as e:
        print(f"⚠️  {e}")
        return

    if df_prom.empty:
        print("⚠️  No hay promedios para graficar (cargue algunas notas).")
        return

    print("Opciones de gráfico:")
    print("1) Boxplot de promedios generales (distribución)")
    print("2) Barras del promedio general por alumno")
    op = input("Elija una opción (1/2): ").strip()

    if op == "1":
        graficar_boxplot_promedios(df_prom, archivo)
    elif op == "2":
        graficar_barras_promedios(df_prom, archivo)
    else:
        print("⚠️  Opción inválida.")


# ========= Menú principal =========
def listar_clases():
    archivos = listar_csv_clases()
    if not archivos:
        print("ℹ️  No hay clases aún.")
        return
    print("\n=== Clases (archivos CSV) ===")
    for f in archivos:
        print(f"- {f}")


def menu():
    asegurar_carpeta_clases()
    while True:
        print("\n================= MENÚ =================")
        print("1) Crear nueva clase (CSV) con materias")
        print("2) Listar clases existentes")
        print("3) Cargar/actualizar notas de una clase")
        print("4) Ver gráficos de una clase (boxplot o barras)")
        print("0) Salir")
        opcion = input("Seleccione una opción: ").strip()
        if opcion == "1":
            crear_csv_clase()
        elif opcion == "2":
            listar_clases()
        elif opcion == "3":
            agregar_o_actualizar_notas()
        elif opcion == "4":
            ver_graficos_clase()
        elif opcion == "0":
            print("¡Hasta luego!")
            break
        else:
            print("⚠️  Opción inválida. Intente nuevamente.")


if __name__ == "__main__":
    try:
        menu()
    except KeyboardInterrupt:
        print("\nInterrumpido por el usuario. Saliendo…")
        sys.exit(0)
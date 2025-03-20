import pandas as pd
from datetime import date
import sys
from pathlib import Path
import openpyxl

sys.path.append("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python")

from MODULOS_BAUMARO.Usos_Comunes import bienvenida

def df_exel():

    df = pd.read_csv("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\archivo.csv")

    df.to_excel("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\archivo.xlsx", index = False, engine='openpyxl')

def crear_dataframe():

    datos = {
        "Nombre": ["Bautista","Thiago","Santiago","Vicente"],
        "Apellido": ["Otero","Fornarini","Besze","Rodriguez"],
        "Dni": [48790829, 4868923, 4782394, 48932902],
        "Fecha-de-nacimiento": [date(2008,6,11),date(2008,2,14),date(2007,8,21),date(2007,11,22)] 
    }

    df = pd.DataFrame(datos)

    df.to_csv("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\archivo.csv", encoding = "UTF-8", index = False)

    return datos

def añadir_fila():

    df = pd.read_csv("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\archivo.csv")

    numero_columnas = df.shape[1]

    cant_filas = int(input("ingrese la cantidad de filas que desea añadir: "))
    

    for i in range(cant_filas):

        df.loc[len(df)] = [input("ingrese el nombre: "), input("ingrese el apellido: "), int(input("ingrese el dni: ")),date(int(input("ingrese el año: ")),int(input("ingrese el mes: ")),int(input("ingrese el dia: ")))] + [input(f"Datos de columnas agregada {j+1}: ") for j in range( numero_columnas - 4)]  


    df.to_csv("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\archivo.csv", index = False, encoding = "UTF-8")

    print(f"se an añadido {cant_filas} filas:")
    

def añadir_columna():

    df = pd.read_csv("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\archivo.csv")

    numero_filas = df.shape[0]

    for j in range(int(input("ingrese la cantidad de columnas que quiere añadir: "))):

        df[input("ingrese el nombre de la nueva columna: ").capitalize().strip()] = [input(f"ingrese el valor de la fila {i}: ") for i in range(numero_filas)]

    df.to_csv("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\archivo.csv", index = False, encoding = "UTF-8")


def Cambiar_tipo_columna():

    df = pd.read_csv("C:\\Users\\bauti\\OneDrive\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\archivo.csv", encoding="UTF-8" )

    Columna_cambiar = input("ingrese la columna que quiere cambiar de tipo: ").capitalize().strip()

    df[Columna_cambiar] = df[Columna_cambiar].astype(int)

    df.to_csv("C:\\Users\\bauti\\OneDrive\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\archivo.csv", index = False, encoding="UTF-8")

def Cambiar_un_dato():

    df = pd.read_csv("C:\\Users\\bauti\\OneDrive\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\archivo.csv", encoding="UTF-8" )

    columna_dato = input("ingresa la columna del dato del df que quiere cambiar: ").capitalize().strip()

    dato_cambiar = input("ingresa el dato del df que quiere cambiar: ").capitalize().strip()
    
    if isinstance(df.loc[1,columna_dato], str):

        df[columna_dato] = df[columna_dato].replace(dato_cambiar ,input("ingrese el dato que desea ingresar: ").capitalize().strip())

    elif isinstance(df.loc[1,columna_dato], int):

        df[columna_dato] = df[columna_dato].replace(dato_cambiar ,int(input("ingrese el dato que desea ingresar: ")))

    elif isinstance(df.loc[1,columna_dato],float) :

        df[columna_dato] = df[columna_dato].replace(dato_cambiar ,float(input("ingrese el dato que desea ingresar: ")))

    elif isinstance(df.loc[1,columna_dato], bool):

        df[columna_dato] = df[columna_dato].replace(dato_cambiar ,bool(input("ingrese el dato que desea ingresar: ")))
    
    df.to_csv("C:\\Users\\bauti\\OneDrive\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\archivo.csv", index = False, encoding= "UTF-8")

def main():

    ruta_archivo = Path("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\archivo.csv")

    if not ruta_archivo.exists():
        crear_dataframe()

    bienvenida()

    print("este es el programa de adminitracion de dateframes")

    print("(1) - añadir fila")
    print("(2) - añadir columna")
    print("(3) - cambiar tipo de la columna")
    print("(4) - remplazar un valor por otro en el dataframe")
    print("(5 - imprimir dataframe)")

    opcion = int(input("ingrese la opcion que desea: "))

    if opcion == 1:

        añadir_fila()

    elif opcion == 2:

        añadir_columna()

    elif opcion == 3:

        Cambiar_tipo_columna()

    elif opcion == 4:

        Cambiar_un_dato()

    elif opcion == 5:

        df = pd.read_csv("C:\\Users\\bauti\\OneDrive\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\archivo.csv", encoding="UTF-8" )

        print(df)

    else:

        print("no ingresaste una opcion valida")

    if input("desea convertir el archivo en un exel si/no: ").capitalize().strip() == "Si":

        df_exel()

    print("apagando ...")
    



if __name__ == "__main__":
    main()
import sys

sys.path.append("C:\\Users\\botero\\Desktop\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python")

import MODULOS_BAUMARO.Usos_Comunes as uc
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from datetime import date
from pathlib import Path




def crear_df():
    ruta = Path("C:\\Users\\botero\\Desktop\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\problemas_graficos\\archivo-horas.xlsx")
    if not ruta.exists():
        dicc = {
            "Fecha": [],
            "Horas": []    
        }

        df = pd.DataFrame(dicc)

        df.to_excel("C:\\Users\\botero\\Desktop\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\problemas_graficos\\archivo-horas.xlsx", index = False , engine = "openpyxl")

def ingresar_datos_diario():

    
    
    df = pd.read_excel("C:\\Users\\bauti\OneDrive\\Documentos\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\problemas_graficos\\archivo-horas.xlsx", engine = "openpyxl")

    for i in range(int(input("Ingrese la cantidad de fechas que desee ingresar: "))):

        print("Ingresa la fecha")

        Fecha_2 = date(int(input("ingrese el Año: ")),int(input("ingrese el Mes: ")),int(input("ingrese el Dia: ")))   

        Hora_2 = int(input("ingresa la cantidad de horas: "))

        Nueva_fila = pd.DataFrame({"Fecha":  [Fecha_2] , "Horas": [Hora_2]}) 

        df = pd.concat([df, Nueva_fila], ignore_index = True)

    df["Fecha"] = pd.to_datetime(df["Fecha"])
    
    df.sort_values(by="Fecha", ascending = True)

    
    df.to_excel("C:\\Users\\botero\\Desktop\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\problemas_graficos\\archivo-horas.xlsx", index = False , engine = "openpyxl")

def crear_grafico():

    df = pd.read_excel("C:\\Users\\botero\\Desktop\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\problemas_graficos\\archivo-horas.xlsx", engine = "openpyxl")
    
    grafico = input("Ingresa el tipo de grafico que desea (dispercion/lieal/barras): ").capitalize().strip()

    if grafico == "Lineal":

        sns.lineplot(x = "Fecha", y = "Horas", data = df)
        
        plt.show()

    elif grafico == "Dispercion":

        sns.scatterplot(x = "Fecha", y = "Horas", data = df)

        plt.show()

    elif grafico == "Barras":

        sns.barplot(x = "Fecha", y = "Horas", data = df)

        plt.show()
    
def main():
    
    uc.bienvenida()

    crear_df()

    df = pd.read_excel("C:\\Users\\botero\\Desktop\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\problemas_graficos\\archivo-horas.xlsx")


    if input("desea ingresar una fila nueva (si/no): ").capitalize().strip() == "Si":
        
        ingresar_datos_diario()

    print(df)
    
    if input("desea crear un grafico sobre el df (Si/No): ").capitalize().strip() == "Si": 

        crear_grafico()





if __name__ == "__main__":

    main()



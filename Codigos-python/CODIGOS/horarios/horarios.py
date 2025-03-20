from pathlib import Path
from datetime import datetime,timedelta,time
import pandas as pd



def crear_df():

    dictt = {
        "Hora" : [],
        "Lunes" : [],
        "Martes" : [],
        "Miercoles" : [],
        "Jueves" : [],
        "Viernes" : [],
        "Sabado" : [],
        "Domingo" : [],
    }
    ruta = Path("C:\\Users\\botero\\Desktop\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\horarios\\horarios.xlsx")

    if not ruta.exists():

        df = pd.DataFrame(dictt)

        df.to_excel("C:\\Users\\botero\\Desktop\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\horarios\\horarios.xlsx" ,index = False, engine = "openpyxl")


def def_horas():

    sep_horas = timedelta(minutes=int(input("ingrese la separacion de las horas: ")))

    time_min = datetime(2000,1,1,int(input("ingrese hora minima: ")))

    time_max = datetime(2000,1,1,int(input("ingrese hora maxima: ")))

    df = pd.read_excel("C:\\Users\\botero\\Desktop\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\horarios\\horarios.xlsx", engine = "openpyxl")

    df.loc[1,"Hora"] = time_min  

    i = 0

    while  time_min < time_max:

        i += 1

        time_min += sep_horas

        dato_guardar = time_min.time().strftime("%H:%M")

        df.loc[i, "Hora"] = dato_guardar

    df.to_excel("C:\\Users\\botero\\Desktop\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\horarios\\horarios.xlsx", engine = "openpyxl")

def ingre_actividad():

    pd.read_excel()


def main():

    crear_df()

    def_horas()






if "__main__" == __name__:
    main()
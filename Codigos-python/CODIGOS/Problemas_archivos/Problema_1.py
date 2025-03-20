# dos listas con nombre y apellido tenemos que escribir las listas en un archivo txt de
# forma optima con un for
from pathlib import Path 

import sys

sys.path.append("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python")

import MODULOS_BAUMARO.Usos_Comunes as uc 

#-----------------------------------------------------------------------------------------------------------------------------------------------------------------

def Generar_listas():

    Lista_nombres = list()
    Lista_apellidos = list()

    cant_pers = int(input("ingrese la cantidad de personas de la lista: "))

    for i in range(cant_pers):

        Lista_nombres.append(input(f"ingrese el nombre de la persona {i}: "))
        Lista_apellidos.append(input(f"ingrese el apellido de la persona {i}: "))

    return Lista_nombres, Lista_apellidos, i

#-----------------------------------------------------------------------------------------------------------------------------------------------------------------

def Pasar_Listas_txt(Lista_nombres, Lista_apellidos, cant_pers):

    with open("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\Archivo.txt","a", encoding= "UTF-8") as Archivo:

        for i in range(cant_pers + 1):

            Archivo.writelines(f"Nombre: {Lista_nombres[i]}, Apellido: {Lista_apellidos[i]}\n")

        print("Se a transferido con exito la informacion")
    
    return None

#-----------------------------------------------------------------------------------------------------------------------------------------------------------------
    
def Crear_txt():

    Ruta_Archivo = Path("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\Archivo.txt")

    if Ruta_Archivo.exists():

        print("el archivo existe")

    else:

        with open("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Problemas_archivos\\Archivo.txt","w", encoding= "UTF-8") as Archivo:

            Archivo.write("")

        print("el archivo fue creado con exito")
    
    return None

#-----------------------------------------------------------------------------------------------------------------------------------------------------------------

def main():

    apagar = False

    uc.bienvenida
    print("este es el programa de almacenamiento de nombres y apellidos")

    while apagar == False:

        Lista_nombres, Lista_apellidos, cant_pers = Generar_listas()

        # Crear_txt()

        Pasar_Listas_txt(Lista_nombres, Lista_apellidos, cant_pers)

        apagar = uc.apagar_

#-----------------------------------------------------------------------------------------------------------------------------------------------------------------

if __name__ == "__main__":
    main()



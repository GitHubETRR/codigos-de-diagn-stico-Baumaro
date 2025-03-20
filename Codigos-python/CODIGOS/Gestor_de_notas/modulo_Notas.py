

from datetime import datetime



def Aniadir_Nota(Lista_Notas):

    with open("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Gestor_de_notas\\Notas.txt","a", encoding = "UTF-8") as Notas:

        for i in range(int(input("Ingrese el numero de notas que quiere escribir: "))):

            Notas.writelines(f"Nota: {input(f"Escribe la Nota numero {i} que desea ingresar: ")} Fecha: {datetime.today().strftime("%Y-%m-%d %H:%M:%S")}\n")

    with open("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Gestor_de_notas\\Notas.txt","r", encoding = "UTF-8") as Notas:

        Lista_Notas = Notas.readlines() 

    return Lista_Notas



def Ver_Notas(Lista_Notas):

    for indice,Nota in enumerate(Lista_Notas):

        print(f"[{indice}] - Nota: {Nota} ")

    return None


def Eliminar_Nota(Lista_Notas):

    for E_Nota in range(int(input("Ingrese el numero de notas que quiere eliminar: "))):

        Ver_Notas(Lista_Notas)

        Lista_Notas.pop(int(input(f"Ingrese el numero de indice de la nota numero {E_Nota} que quiere borrar: ")))

    with open("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Gestor_de_notas\\Notas.txt","w", encoding = "UTF-8") as Notas:

        Notas.writelines(Lista_Notas)

    return Lista_Notas


def Limpiar_Notas(Lista_Notas):

    with open("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Gestor_de_notas\\Notas.txt","w", encoding = "UTF-8") as Notas:

        Lista_Notas = Notas.write("")

    return Lista_Notas

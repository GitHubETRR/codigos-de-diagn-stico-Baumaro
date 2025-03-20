import sys 

sys.path.append("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python")

from MODULOS_BAUMARO.Usos_Comunes import bienvenida,apagar_

import modulo_Notas as modulo




def main():

    apagar = False
    

    with open("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\Gestor_de_notas\\Notas.txt","r", encoding = "UTF-8") as Notas:

        Lista_Notas = Notas.readlines()

    bienvenida()

    print("este es el programa de gestor de notas")

    while apagar == False:

        Variable_verdadera = False

        while Variable_verdadera == False:

            print("PANEL DE OPCIONES")
            print("(1) - Añadir una nota")
            print("(2) - Ver Notas")
            print("(3) - Eliminar una nota")        
            print("(4) - Limpiar Notas")

            Varible_eleccion = int(input("Ingrese la operacion que desea realizar: "))

            if Varible_eleccion == 1:

                Lista_Notas = modulo.Aniadir_Nota(Lista_Notas)

                Variable_verdadera = True
        
            elif Varible_eleccion == 2:

                Lista_Notas = modulo.Ver_Notas(Lista_Notas)

                Variable_verdadera = True

            elif Varible_eleccion == 3:

                Lista_Notas = modulo.Eliminar_Nota(Lista_Notas)

                Variable_verdadera = True

            elif Varible_eleccion == 4:

                Lista_Notas = modulo.Limpiar_Notas(Lista_Notas)

                Variable_verdadera = True

            else:

                print("No ingresaste ningun valor valido, vuelve a ingresarlo")

                Variable_verdadera = False

        apagar = apagar_()

        print(apagar)


if __name__ == "__main__":
    main()
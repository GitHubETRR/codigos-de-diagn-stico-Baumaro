import os
import sys


def main():

    lista = []
    lista_usuarios = []
    variable_bucle_temporal = True
    print("bienvenido al programa del manipulacion de vectores")

    while variable_bucle_temporal:

        print("(1) - registrar un usuario")
        print("(2) - iniciar sesion")

        variable_seleccion = int(input())

        if variable_seleccion == 1: #REGISTRAR

            Usuarios.registrar(lista_usuarios)

            print("ahora debe iniciar sesion")

        elif variable_seleccion == 2: #INICIAR SECION

            if Usuarios.Iniciar_sesion(lista_usuarios, input("Nombre de usuario: "), input("Contraseña: ")) == True:
                
                variable_bucle_temporal = False

        else:

            print("no ingresaste una opcion valida, por favor ingrese una opcion valida")

    MAX_RANGE = int(input("ingrese la cantidad de numeros que quiere ingresar en la lista: "))

    ingresar_numeros(lista, MAX_RANGE)

    print(" OPERACIONES ")
    print("(1) - calcular suma")
    print("(2) - buscar valores")
    print("(3) - calcular numero minimo")
    print("(4) - calcular promedio")
    print("(5) - calcular numeros mayor al promedio ")
    print("(6) - calcular los multiplos del ultimo numero")

    entrada_valida = True

    while entrada_valida:

        Variable_eleccion = int(input())

        if Variable_eleccion == 1:


            calcular_suma(lista, MAX_RANGE)

            entrada_valida = False

        elif Variable_eleccion == 2:

            buscar_valor(lista, MAX_RANGE)

            entrada_valida = False

        elif Variable_eleccion == 3:

            calcular_min(lista)

            entrada_valida = False

        elif Variable_eleccion == 4:

            calcular_prom(lista, MAX_RANGE)

            entrada_valida = False

        elif Variable_eleccion == 5:

            promedio = calcular_prom(lista, MAX_RANGE)

            may_prom(promedio, MAX_RANGE)

            entrada_valida = False

        elif Variable_eleccion == 6:

            multi_ult_num(lista, MAX_RANGE)

            entrada_valida = False

        else:
            print("no ingresaste una entrada valida vuelve a ingresar")


def ingresar_numeros(lista, MAX_RANGE):

    for i in range(MAX_RANGE):

        lista.append(int(input(f"ingrese el numero de la posicion {i}: ")))

    return lista


def calcular_suma(*lista):

    suma_lista = sum(lista) 

    print(f"la sumatoria de todos los valores de la lista es: {suma_lista}")

    return suma_lista


def buscar_valor(lista, MAX_RANGE):

    numero_buscado = int(input("ingresa el numero que deseas buscar en las lista: "))

    if lista in numero_buscado:

        for posicion in range(MAX_RANGE):

            if numero_buscado == lista[posicion]:
                print(
                    f"el numero {numero_buscado} que ingresaste esta en la posicion {posicion}"
                )
    else:
        print(f"el numero {numero_buscado} no esta en la lista")

    return posicion


def calcular_min(lista):

    valor_min = min(lista)

    print(f"el numero mas chico de la lista es: {valor_min}")

    return valor_min


def calcular_prom(lista, MAX_RANGE):
    promedio = 0
    for i in range(MAX_RANGE):
        promedio += lista[i]

    promedio /= MAX_RANGE
    print(f"el promedio del vector es: {promedio}")

    return promedio


def may_prom(promedio, MAX_RANGE):
    num_may_prom = []
    for i in range(MAX_RANGE):

        if i > promedio:

            num_may_prom.append(i)

    print(f"los numeros mayores al promedio {promedio} son {num_may_prom}")

    return num_may_prom


def multi_ult_num(lista, MAX_RANGE):

    multiplos = []

    for i in range(lista[MAX_RANGE]):
        if (lista[MAX_RANGE] % i) == 0:
            multiplos.append(i)

    print(f"los multiplos del ultimo numero son {multiplos}")

    return multiplos


class Usuarios:
    def __init__(self, n_usuario, nombre, apellido, contraseC1a):

        self.n_usuario = n_usuario
        self.nombre = nombre
        self.apellido = apellido
        self.contraseC1a = contraseC1a

    @staticmethod
    def registrar(lista_usuarios):

        lista_usuarios.append(
            Usuarios(
                input("ingrese un nombre de usuario: "),
                input("ingrese su nombre: "),
                input("ingrese su apellido: "),
                input("ingrese una contraseC1a: "),
            )
        )

        return lista_usuarios

    @staticmethod
    def Iniciar_sesion(lista_usuarios, U_ingresado, C_ingresada):

        U_valido = False

        for usuario in lista_usuarios:

            if usuario.n_usuario == U_ingresado and usuario.contraseC1a == C_ingresada:

                U_valido = True
                print("se a iniciado sesion correctamente")
                break

        else:
            print("tu nombre de usuario o tu contraseC1a estan mal")

        return U_valido


if __name__ == "__main__":
    main()


   
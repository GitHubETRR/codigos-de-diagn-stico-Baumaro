import MODULOS_BAUMARO.Usos_Comunes as MB
import pandas as pd
from pathlib import Path


class Producto():

    def __init__(self, Nombre, Precio, Categoria, Codigo):

        self.Nombre = Nombre
        self.Precio = Precio
        self.Categoria = Categoria
        self.Codigo = Codigo


    def Comprar(self):

        print(f"Has comprado el producto {self.Nombre} Codigo: {self.Codigo}")

    def Devolucion(self):

        print(f"Has devuelto el producto {self.Nombre} Codigo: {self.Codigo}")

class Disp_electronico(Producto):

    def __init__(self,Nombre, Precio, Categoria, Consumo, Tamaño):

        super().__init__(self,Nombre, Precio, Categoria)
        self.Consumo = Consumo
        self.Tamaño = Tamaño

    def Turn_ON(self):

        print(f"El Dispositivo {self.Nombre} se ha encendido")

    def Turn_OFF(self):

        print(f"El Dispositivo {self.Nombre} se ha apagado")

class Moda(Producto):

    def __init__(self, Nombre, Precio, Categoria, Talle, Tela):

        super().__init__(Nombre, Precio, Categoria)
        self.Talle = Talle
        self.Tela = Tela

class Consumibles(Producto):

    def __init__(self, Nombre, Precio, Categoria, Codigo, Fecha_de_vencimiento, Tipo, Fecha_de_enbasado, Tac, Sin_Lactosa):
        super().__init__(Nombre, Precio, Categoria, Codigo)
        self.Fecha_de_vencimiento = Fecha_de_vencimiento
        self.Fecha_de_enbasado = Fecha_de_enbasado
        self.Tipo = Tipo
        self.Sin_Lactosa = Sin_Lactosa

class Marca():

    def __init__(self, Nombre_Marca, Linea, Año):

        self.Nombre_Marca = Nombre_Marca
        self.Linea = Linea
        self.Año = Año

class Producto_Electronico(Marca, Disp_electronico):

    def __init__(self, Nombre_Marca, Linea, Año, Nombre, Precio, Categoria, Consumo, Tamaño):

        Marca.__init__(Nombre_Marca, Linea, Año)
        Disp_electronico.__init__(Nombre, Precio, Categoria, Consumo, Tamaño)

class Producto_Moda(Moda, Marca):

    def __init__(self, Nombre, Precio, Categoria, Talle, Tela, Nombre_Marca, Linea, Año):

        Moda.__init__(Nombre, Precio, Categoria, Talle, Tela)
        Marca.__init__(self, Nombre_Marca, Linea, Año)

def Crear_Archivo():

    ruta = Path("C:\\Users\\botero\\Desktop\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python\\CODIGOS\\POO\\archivo.csv")

    dicc = { 

        "Electronicos"
        "Consumibles"
        "Moda"


    }

    if not ruta.exists():

        .to_csv()


def main():

    apagar = False

    MB.bienvenida()

    while apagar == False:




if __name__ == "__main__":
    main()


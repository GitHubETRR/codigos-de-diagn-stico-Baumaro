# CREAR UN MODULO 

from datetime import date

class Prendas:

    def __init__(self,Tipo,Marca,Modelo,Talle,Color,Fecha):

        self.Tipo = Tipo
        self.Marca = Marca
        self.Modelo = Modelo
        self.Talle = Talle
        self.Color = Color
        self.Fecha = Fecha
    


def Aniadir_Ropa():

    Ropa_Nueva = Prendas(
                        input("Ingrese el tipo de la prenda: "),
                        input("Ingrese la marca de la prenda: "),
                        input("Ingrese el modelo de la prenda: "),
                        input("Ingrese el talle de la prenda: "),
                        input("Ingrese el/los colores de la prenda: "),
                        date.today().strftime('%d,%m,%Y'))
    
    return Ropa_Nueva


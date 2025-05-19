import pandas as pd
from clases import charakter
import re
import sys

sys.path.append("C:\\Users\\bauti\\OneDrive\\Escritorio\\codigos-de-diagn-stico-Baumaro\\Codigos-python\\MODULOS_BAUMARO")

from MODULOS_BAUMARO.Usos_Comunes import bienvenida 




class humano(charakter):
    def __init__(self, name, wandel, schandel, raza):
        super().__init__(name, wandel, schandel, raza)

    def __add__(self, neuer_charakter): 

        raza_1 = re.search(r"[a-zA-Z]{2}", self.name)
        if raza_1:
            self.name = raza_1.group()
        else:
            self.name = "deconocida"

        raza_2 = re.search(r"[a-zA-Z]{2}$", neuer_charakter.name)
        if raza_2:
            neuer_charakter.name = raza_2.group()
        else:
            neuer_charakter.name = "deconocida"

        if not(self.raza == neuer_charakter.raza):
            self.raza = "hibrido"

        print(f"{self.name} se fuciono con {neuer_charakter.name}")
        return charakter((self.name + neuer_charakter.name), (self.wandel + neuer_charakter.wandel) * 1.1 , (self.schandel + neuer_charakter.schandel), self.name)


    def schlanganfall(self, texto):
        print(f"humano {self.name}: {texto}")
        self.wandel

class namekiano(charakter):
    def __init__(self, name, wandel, schandel, raza, regeneration):
        super().__init__(name, wandel, schandel, raza)
        self.___regeneration = regeneration

    @property
    def regeneration(self):
        return self.regeneration

    def schlanganfall(self, texto):
        print(f"namekiano {self.name}: {texto}")

    def __add__(self, neuer_charakter):

        name_1 = re.search(r"[a-zA-Z]{2}", self.name)
        if name_1:
            self.name = name_1.group()

        name_2 = re.search(r"[a-zA-Z]{2}$", neuer_charakter.name)
        if name_2:
            neuer_charakter.name = name_2.group()

        if not(self.raza == neuer_charakter.raza):
            self.raza = "hibrido"

        if self.regeneration < neuer_charakter.regeneration:
            self.regeneration = neuer_charakter.regeneration

        print(f"{self.name} se fuciono con {neuer_charakter.name}")
        return charakter((self.name + neuer_charakter.name), (self.wandel + neuer_charakter.wandel) * 1.1 , (self.schandel + neuer_charakter.schandel), self.raza, self.regeneration)


class mago(namekiano):
    def __init__(self, name, wandel, schandel, raza, regeneration ,magische_Kraft):
        super().__init__(name, wandel, schandel, raza, regeneration)
        self.__magische_Kraft = magische_Kraft

    @property
    def magische_Kraft(self):
        return self.__magische_Kraft
    
    def fucionar(metodo):
        def rellenar(self, neuer_charakter):
            objeto = super().__add__(self, neuer_charakter)
            return mago(objeto.name, objeto.wandel, objeto.schandel, objeto.raza, objeto.regeneration, self.magische_Kraft)
        return rellenar


    def Heilung(self,jetz_gesundheitspunkte, name):
        print(f"{self.name} esta curando a {name}")
        cura = jetz_gesundheitspunkte + self.regeneration

    def platzen(self,jetz_gesundheitspunkte,satz):
        print(f"{self.name} exploto {satz}")
        danio = jetz_gesundheitspunkte - self.magische_Kraft
        return danio 
    

def ersteBenutzermenü():

    bienvenida()
    print("este es el progra de fusion de personajes")
    print("desea crear un personaje(si/no)")

def erstellen_charakter():

    tipo = input("ingrese uno de los siguentes tipos para poder crear el personaje\nnamekiano\nhumano").capitalize().strip()

    if tipo == "namekiano":
        
        namekiano()

def stezen_information(tipo):

    if tipo == "namekiano":
        print("ingrese los siguientes parametros en el siguiente orden")
        print("(1) - name")
        print("(2) - wandel")
        print("(3) - schandel")
        print("(4) - ")
        info = [input(f"{i}:").capitalize().strip() for i in range(5)]



def main():

    ersteBenutzermenü()
    if input().capitalize().strip() == "Si":





if __name__ == "__name__":
    main()




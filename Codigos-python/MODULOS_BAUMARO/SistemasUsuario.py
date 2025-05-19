from abc import ABC, abstractmethod

class Usuario(ABC):
    @abstractmethod
    def __init__(self,nombre,contrasena,tag):
        self.__nombre = nombre
        self.__contrasena = contrasena

    @abstractmethod
    def iniciar_sesion():
        pass

    @property
    def Usuario(self):
        return self.__nombre
    
    @Usuario.setter
    def Usuario(self, newUsuario):
        self.__nombre = newUsuario

    @Usuario.deleter
    def Usuario(self):
        del self

    

    









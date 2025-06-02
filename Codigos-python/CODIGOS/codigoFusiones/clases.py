from abc import ABC, abstractmethod
import re

class charakter(ABC):

    def __init__(self, name, wandel, schandel, raza):

        self.name = name
        self.__wandel = wandel
        self.__schandel = schandel
        self.raza = raza

    @property
    def wandel(self):
        return self.__wandel
    
    @property
    def schandel(self):
        return self.__schandel

    @abstractmethod
    def schlanganfall(self):
        pass




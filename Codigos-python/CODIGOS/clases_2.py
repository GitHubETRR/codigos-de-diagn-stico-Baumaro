""" CONSIGNA: en una clase de la escuela falto el profesor. el alumno a cargo va a ser el mayor de la clase
    y el asistente el menor. 

REQUISITOS

    la cantidad de alumnos presentes 
    su estado individual (presente / ausente)
    edad de cada alumno
    fecha de nacimiento
    nombre y apellido
    crear una lista que contenga a cada alumno 
    pedir la fecha actual       """

#///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
import getpass

from datetime import date

DIA = 0
MES = 1
AÑO = 2

#///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

def main():

    apagar = False

    clase = list()

    bienvenida()

    cant_alumnos = int(input("porfavor ingrese la cantidad de alumnos de la clase: "))

    clase = asignar_datos(cant_alumnos, clase)

    presentes = alms_presentes(clase)

    responsable, sub_responsable  = alms_responsables(presentes)

    for alumno in presentes:

        alumno.definir_responsable(presentes,responsable,sub_responsable,alumno)

    while apagar == False:

        if input("Desea ver la informacion de un alumno (si/no): ").capitalize().strip() == "Si":

            if input("desea buscar al alumno por nombre? (si/no): ").capitalize().strip() == "Si":

                nom_alm = input("Ingrese el nombre del alumno que esta buscando: ").capitalize().strip()

                for alumnos in clase:
                    
                    if type(alumno) == str:
                        continue

                    alumno_buscado = alumnos.buscar_alm_nom(alumnos, nom_alm)

            
            elif input("desea buscar al alumno por apellido? (si/no): ").capitalize().strip() == "Si":

                ape_alm = input("Ingrese el apellido del alumno que esta buscando: ").capitalize().strip()

                for alumnos in clase:
                    
                    if type(alumno) == str:
                        continue

                    alumno_buscado = alumnos.buscar_alm_ape(alumnos, ape_alm)    

        apagar = apagar_()

#///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        
def apagar_():

    if input("si desea apagar el programa ingresa  \"Si\"").capitalize().strip() == "Si": 
        print("apagando...")
        return True  

    return False            

    
#///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

def bienvenida():
    name = getpass.getuser()
    print(f"Hola bienvenido {name}")

#///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

def asignar_datos(cant_alumnos,clase):

    for alumno in range(1, cant_alumnos + 1):

        clase.append(Alumno(
            input(f"ingrese el nombre del alumno {alumno}: ").capitalize().strip(),
            input(f"ingrese el apellido del alumno {alumno}: ").capitalize().strip(),
            input(f"ingrese la edad del alumno {alumno}: "),
            fecha_nacimiento = date(
                int(input(f"ingrese el año de nacimiento del alumno {alumno}: ")),
                int(input(f"ingrese el mes de nacimiento del alumno {alumno}: ")),
                int(input(f"ingrese el dia de nacimiento del alumno {alumno}: "))
            ),
            estado = input("ingrese - Presente - o - Ausente: ").capitalize().strip() == "Presente",
            responsable = None,
            sub_responsable = None
        ))

    clase.append(f"FECHA: {date.today().strftime('%d,%m,%Y')}") #asigna la fecha de cuando fue guardados los datos al final de la lista
    

    return clase

#///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

def alms_presentes(clase):


    presentes = list()

    for alumno in clase:

        if type(alumno) == str:
            continue

        if alumno.estado == True:
            presentes.append(alumno)

    if presentes == []:
        print("no hay alumnos presentes")
        return None

    return presentes

#///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

def alms_responsables(presentes):  
    
    mayor = max(presentes, key=lambda x: x.edad)
    menor = min(presentes, key=lambda x: x.edad)
    
    responsable = mayor.nombre
    sub_responsable = menor.nombre        

    return responsable, sub_responsable

#///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Alumno:

    def __init__(self,nombre,apellido,edad,fecha_nacimiento,estado,responsable,sub_responsable):        

        self.responsable = responsable               # <--   definiendo los parametros de la clase Alumno  
        self.sub_responsable = sub_responsable
        self.nombre = nombre
        self.apellido = apellido
        self.edad = edad 
        self.fecha_nacimiento = fecha_nacimiento
        self.estado = estado

#///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    def definir_responsable(self, presentes, responsable, sub_responsable, alumno): # este metodo se utiliza para poder redefinir el responsable posterior a calcular la edad del alumno edad max y min 

        alumno.responsable = responsable
        alumno.sub_responsable = sub_responsable

        return presentes

        


#///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    @staticmethod
    def buscar_alm_nom(alumno,nom_alm):

        if alumno.nombre == nom_alm:

            vars(alumno)

            return alumno
        
        return None

    @staticmethod
    def buscar_alm_ape(alumno,ape_alm):

        if alumno.apellido == ape_alm:

            vars(alumno)

            return alumno
        
        return None
        
        

if __name__ == "__main__":
    main()
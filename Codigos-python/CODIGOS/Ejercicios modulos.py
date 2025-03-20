import sys

sys.path.append("C:\\Users\\bauti\\OneDrive\\Documentos\\GitHub\\codigo-prueba-Baumaro\\Lenguajes-electronicos\\Codigos-python")

# existen dos formas de importar un modulo desde una carpeta que no esta en la ruta
#    mediante un paquete o importando la direccion y pasarla a sys.path


from MODULOS_BAUMARO.MODULOS import Aniadir_Ropa #(esta trabaja con sys.path)

 # import MODULO_AFUERA.MODULOS as modulo (esta es la que trabaja con paquete)

from MODULOS_BAUMARO.Usos_Comunes import bienvenida,apagar_



def main():

    Armario = []

    bienvenida()
    
    print("Este el programa \"ARMARIO\" en el cual puedes tener un registro de tus prendas de ropa")

    apagar = False

    while  apagar == False:
    
        variable_valida = False #se usa para que se ingrese un valor valido al bucle 

        while variable_valida == False: #crea un bucle que si no se ingresa una variable valida repita la introduccion de la variable

            Variable_seleccion = input("Desea ingresar una prenda nueva al armario? Si/No ").capitalize().strip() 

            if Variable_seleccion == "Si":
            
                Cant_Ropa = int(input("ingrese la cantidad de ropa que quiere añadir: "))

                for i in range(Cant_Ropa): # crea un bucle que permite ingresar multiples prendas al armario

                    Armario.append(Aniadir_Ropa()) # aniadir ropa tambien puede ser modulo.Aniadir_Ropa() si utilizamos la importacion por paquete

            elif Variable_seleccion == "No": 
            
                Variable_seleccion = input("Desea ver las prendas del armario? Si/No ").capitalize().strip()

                if Variable_seleccion == "Si":

                    Ver_Armario(Armario)


                elif Variable_seleccion == "No":

                    Variable_seleccion = input("Desea eliminar una prenda? Si ").capitalize().strip()

                    if Variable_seleccion == "Si":

                        Ver_Armario(Armario)

                        Armario.pop(int(input("Ingrese el lugar del armario en el que esta la prenda: ")))

                else:
                    print("no ingresaste ningun valor valido, vuelve a ingresarlo")

            else:
                print("no ingresaste ningun valor valido, vuelve a ingresarlo") 

        apagar = apagar_()

def Ver_Armario(Armario):

    for  indicador , prenda in enumerate(Armario):
        
        print(f"[{indicador}] - {vars(prenda)}")
    
    return None



if __name__ == "__main__":
    main()


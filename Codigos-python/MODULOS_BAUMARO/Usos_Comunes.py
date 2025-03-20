import getpass

def bienvenida():
    name = getpass.getuser()
    print(f"Hola bienvenido {name}")

def apagar_():

    if input("si desea apagar el programa ingresa  \"Si\": ").capitalize().strip() == "Si": 
        print("apagando...")
        return True  

    return False            

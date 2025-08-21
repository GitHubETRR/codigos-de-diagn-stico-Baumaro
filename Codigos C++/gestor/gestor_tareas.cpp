
#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std; 

class Tarea{
    private: 
        int ID;
        string Descripcion;
        bool Estado
        
    public:
        
        string getDescripcion(){
            cout << "Descripcion: " << Descripcion << endl;
            return Descripcion;
        }
        void setDescripcion(string descripcion){
            Descripcion = descripcion;
        }
        void setEstado(bool estado){
            Estado = estado;
        }
        bool getEstado(){
            return Estado;
        }
};

class Usuario{
    private:
        string Nombre;
        string Apellido;
        string Usuario;
        string Contrasena;
        int Rango;
    public:

        Usuario(string nombre ,string apellido ,string usuario ,string contrasena ,int rango){
            Nombre = nombre;
            Apellido = apellido;
            Usuario = usuario; 
            Contrasena = contrasena;
            Rango = rango; 
        }
        void getUserName(){
            return Usuario;
        }
        void getContrasenia(){
            return Contrasenia; 
        }
        void setNombre(string nombre){
            Nombre = nombre;
        }
        void setApellido(string apellido){
            Apellido = apellido;
        }
        void setRango(int rango){
            Rango = rango;
        }
};

bool Login(){
    cin >> new(NombreUsuario);
    cin >> new(Contrasena); 
    ifstream archivoUsuarios("archivoUsuarios.csv"); //crea un objeto de tipo ifstream 
    if (!archivo) {
        cout << "No se pudo abrir el archivo" << endl;
        return false;
    }

    string* linea = new string

    while(getline("archivoUsuarios.csv", linea, ','))
    {
        cout <<
    }
    
    
}

void  Bienvenida(){
    cout << "bienvenido a la aplicacion de gestion de tareas" << endl;
}




int main(){
    Bienvenida(); 

}

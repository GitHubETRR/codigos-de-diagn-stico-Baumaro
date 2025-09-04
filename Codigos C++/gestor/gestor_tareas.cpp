
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <fstream>
using namespace std; 

class Tarea{
    private: 
        int ID;
        string Descripcion;
        bool Estado;
        
    public:
        Tarea(int id, string descripcion, bool estado){
            ID = id; 
            Descripcion = descripcion;
            Estado = estado; 
        }
        
        string getDescripcion(){
            cout << "Descripcion: " << Descripcion << endl;
        }

        void setDescripcion(string descripcion){
            Descripcion = descripcion;
        }
        void setEstado(bool estado){
            Estado = estado;
        }
        bool getEstado(){
            cout << "Estado: " << Estado << endl;
        }
};

class Usuario{
    private:
        string Nombre;
        string Apellido;
        string NombreUsuario;
        string Contrasena;
        int Rango;
        string repocitorioTareas;
    public:

        // contructor de la calse usuario
        Usuario(string nombre ,string apellido ,string usuario ,string contrasena ){
            Nombre = nombre;
            Apellido = apellido;
            NombreUsuario = usuario; 
            Contrasena = contrasena;
            Rango = 0; 
            repocitorioTareas = "//repositorio//" + NombreUsuario + "//tareas.csv";
        }

        Usuario(string nombre ,string apellido ,string usuario ,string contrasena, string rango){
            Nombre = nombre;
            Apellido = apellido;
            NombreUsuario = usuario; 
            Contrasena = contrasena;
            if (rango == "admin")
            {
                Rango = 1; 
            }
            else{
                Rango = 0; 
            }
        }

        string getUserName(){
            return NombreUsuario;
        }
        string getContrasenia(){
            return Contrasena; 
        }
        void setRango(int rango){
            Rango = rango;
        }

        void setNombre(string nombre){
            Nombre = nombre;
        }
        void setApellido(string apellido){
            Apellido = apellido;
        }
};

void  Bienvenida();
vector<string> Login();

int main(){
    Bienvenida(); 
}

void  Bienvenida(){
    cout << "bienvenido a la aplicacion de gestion de tareas" << endl;
}


vector<string> Login(){
    string* NombreUsuario = new string();
    string* Contrasenia = new string();
    cin >> *NombreUsuario;
    cin >> *Contrasenia;

    ifstream archivoUsuarios("archivoUsuarios.csv"); //crea un objeto de tipo ifstream para abrir el archivo en modo lectura
    if (!archivoUsuarios){
        cout << "No se pudo abrir el archivo" << endl;
        exit(-1);
    }

    string* linea = new string;
    string* dato = new string();

    while(getline(archivoUsuarios , *linea)){
        stringstream ss(*linea);
        vector<string> informacionUsuario;
        while (getline(ss, *dato, ',')) {
            informacionUsuario.push_back(*dato);
        }
        if (informacionUsuario[2] == *NombreUsuario && informacionUsuario[3] == *Contrasenia)
        {
            return informacionUsuario;
        }
    }

    cout << "No se encontraron coincidencias con el usuario y contrasenia" << endl;

    archivoUsuarios.close();
    delete NombreUsuario;
    delete Contrasenia;
    delete linea;
    delete dato;
}





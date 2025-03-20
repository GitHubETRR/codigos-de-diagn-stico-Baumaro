#include <stdio.h>

union flag{

    struct flags{
        unsigned int Bit0:1;
        unsigned int Bit1:1;
        unsigned int Bit2:1;
        unsigned int Bit3:1;
        unsigned int Bit4:1;
        unsigned int Bit5:1;
        unsigned int Bit6:1;
        unsigned int Bit7:1;
    };

    char VarElec;
};
typedef struct{

    char Nombre_Usuario[10];
    char Contraseña[10];
    int Rango;

}Usuario_t;

typedef struct{

    char Nombre[10];
    float Precio;
    int Codigo;

}Producto_t;

void Crear_Archivo(void);

void Crear_Usuario(void);


int main()
{

    flag

    printf("Bienvenido a Super Baumaro\n");



    printf("Desea acceder al sistema de admin? \n(1) - Si \n(0) - no");
    scanf("%d", );



    printf("Desea ver el catalogo de productos? \n(1) - Si \n(0) - no");
    scanf("%d", &Var_Elec);

    if (Var_Elec == 1)
    {
        
    }
    



}

void Crear_Ar

void Crear_Usuarios(){

    Usuario_t Nuevo_Usuario;

    scanf("Ingrese el nombre de usuario de la cuenta: %s", Nuevo_Usuario.Nombre_Usuario);
    scanf("Ingrese la contraseña de la cuenta: %s", Nuevo_Usuario.Contraseña);
    scanf("Ingrese el rango que quiere asignarle a la cuenta: %d", Nuevo_Usuario.Rango);

    fopen("Base_de_usuarios");



}

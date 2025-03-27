#include <stdio.h>
#include <string.h>
#define MAX_LINEA 21

union flag
{

    struct bits
    {
        unsigned int Bit0 : 1;
        unsigned int Bit1 : 1;
        unsigned int Bit2 : 1;
        unsigned int Bit3 : 1;
        unsigned int Bit4 : 1;
        unsigned int Bit5 : 1;
        unsigned int Bit6 : 1;
        unsigned int Bit7 : 1;
    };

    char Var;
};

typedef struct
{

    char Nombre_Usuario[10];
    char Contraseña[10];
    int Rango;

} Usuario_t;

typedef struct
{

    char Nombre[10];
    float Precio;
    int Codigo;

} Producto_t;

void Crear_Usuario(void);

void Iniciar_sesion(union flag flag_elec);

int main()
{

    union flag flag_elec;
    flag_elec.Var = 0;

    printf("Bienvenido a Super Baumaro\n");

    printf("Desea acceder al sistema de admin? \n(1) - Si \n(0) - no");
    scanf("%d", &flag_elec.bits.bitELEC);

    printf("\nDesea ver el catalogo de productos? \n(1) - Si \n(0) - no");
    scanf("%d", &flag_elec.bits.bit0);
}

void Crear_Usuarios()
{

    Usuario_t Nuevo_Usuario;

    printf("\nIngrese el nombre de usuario de la cuenta: ");
    scanf("%s", Nuevo_Usuario.Nombre_Usuario);

    printf("\nIngrese la contraseña de la cuenta: ");
    scanf("%s", Nuevo_Usuario.Contraseña);

    printf("\nIngrese el rango que quiere asignarle a la cuenta: ");
    scanf("%d", &Nuevo_Usuario.Rango);

    FILE *fp = fopen("Base_de_usuarios.csv", "a");

    fprintf(fp, "Nombre Usuario,Contraseña,Rango\n");

    fprintf(fp, "%s,%s,%d\n", Nuevo_Usuario.Nombre_Usuario, Nuevo_Usuario.Contraseña, Nuevo_Usuario.Rango);

    fclose(fp);
}

void Iniciar_sesion(union flag flags_elec)
{

    Usuario_t Usuario_inicio;

    char Linea[MAX_LINEA];

    printf("\nIngrese el nombre de usuario de la cuenta que quiere iniciar sesion: ");
    scanf("%s", Usuario_inicio.Nombre_Usuario);

    printf("\nIngrese la contraseña de la cuenta que quiere iniciar sesion: ");
    scanf("%s", Usuario_inicio.Contraseña);

    printf("\nIngrese el rango que quiere asignarle a la cuenta: ");
    scanf("%d", Usuario_inicio.Rango);

    FILE *fp = fopen("Base_de_usuarios.csv", "r");

    while (fgets(Linea, 10, fp))
    {

        char *NU = strtok(Linea, ",");
        char *CS = strtok(NULL, ",");
        char *RG = strtok(NULL, ",");

        if (strcmp((NU, Usuario_inicio.Nombre_Usuario) == 0))
        {

            if (strcmp((CS, Usuario_inicio.Contraseña) == 0))
            {

                printf("se ha iniciado sesion con exito");
            }
            else
            {

                printf("la contraseña que ha ingresado esta mal");
            }
        }
    }
}

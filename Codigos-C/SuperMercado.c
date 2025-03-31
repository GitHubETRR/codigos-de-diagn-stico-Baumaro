#include <stdio.h>
#include <string.h>
#define MAX_LINEA 151

union flag
{
    struct
    {
        unsigned int Bit0 : 1;
        unsigned int Bit1 : 1;
        unsigned int Bit2 : 1;
        unsigned int Bit3 : 1;
        unsigned int Bit4 : 1;
        unsigned int Bit5 : 1;
        unsigned int Bit6 : 1;
        unsigned int Bit7 : 1;
    } bits;

    char Var;
};

typedef struct
{

    char Nombre_Usuario[50];
    char Contraseña[50];
    int Rango;

} Usuario_t;

typedef struct
{

    char Nombre[10];
    float Precio;
    int Codigo;

} Producto_t;

void Crear_Usuario(void);

Usuario_t Iniciar_sesion(void);

int main()
{
    FILE *fp = fopen("Base_de_usuarios.csv", "a");

    fprintf(fp, "Nombre Usuario,Contraseña,Rango\n");

    fclose(fp);

    int Var_elec;

    printf("Bienvenido a Super Baumaro\n");

    printf("Desea acceder al sistema de admin? \n(1) - Si \n(0) - no");
    scanf("%d", &Var_elec);

    if (Var_elec == 1)
    {
        Usuario_t Usuario_iniciado = Iniciar_sesion();
    }

    Var_elec = 0;

    printf("\nDesea ver el catalogo de productos? \n(1) - Si \n(0) - no");
    scanf("%d", &Var_elec);
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

    fprintf(fp, "%s,%s,%d\n", Nuevo_Usuario.Nombre_Usuario, Nuevo_Usuario.Contraseña, Nuevo_Usuario.Rango);

    fclose(fp);
}
Usuario_t Iniciar_sesion()
{

    Usuario_t Usuario_inicio;

    char Linea[MAX_LINEA];

    printf("\nIngrese el nombre de usuario de la cuenta que quiere iniciar sesion: ");
    scanf("%s", Usuario_inicio.Nombre_Usuario);

    printf("\nIngrese la contraseña de la cuenta que quiere iniciar sesion: ");
    scanf("%s", Usuario_inicio.Contraseña);

    FILE *fp = fopen("Base_de_usuarios.csv", "r");

    while (fgets(Linea, MAX_LINEA, fp))
    {
        Usuario_t *UA = (Usuario_t *)malloc(sizeof(Usuario_t));
        *UA->Nombre_Usuario = strtok(Linea, ",");
        *UA->Contraseña = strtok(NULL, ",");
        UA->Rango = strtok(NULL, ",");

        if (strcmp(UA->Nombre_Usuario, Usuario_inicio.Nombre_Usuario) == 0)
        {

            if (strcmp(UA->Contraseña, Usuario_inicio.Contraseña) == 0)
            {

                Usuario_inicio.Rango = UA->Rango;
                printf("se ha iniciado sesion con exito");

                return Usuario_inicio;
            }
            else
            {
                printf("la contraseña que ha ingresado no coinside con el nombre de usuario");
                strcpy(Usuario_inicio.Nombre_Usuario, "error");
            }
        }
        else
        {

            printf("El nombre de usuario no existe");
            strcpy(Usuario_inicio.Nombre_Usuario, "error");
        }
    }
}
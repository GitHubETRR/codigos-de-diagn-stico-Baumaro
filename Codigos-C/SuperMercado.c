#include <stdio.h>
#include <string.h>
#define MAX_LINEA 151
#define MAX_CHAR 50
#define TRUE 1
#define FALSE 0

typedef struct
{
    unsigned int disponible : 1;
    unsigned int oferta : 1;
    unsigned int agotado : 1;
    unsigned int reservado : 1;
    unsigned int perecedero : 1;
    unsigned int fragil : 1;
    unsigned int importado : 1;
    unsigned int exclusivo : 1;
} campo_bits;

typedef union
{

    campo_bits flag;
    unsigned char estado;

} ProductoFlag;

typedef struct
{

    char Nombre_Usuario[MAX_CHAR];
    char Contraseña[MAX_CHAR];
    int Rango;

} Usuario_t;

typedef struct
{

    char Nombre[MAX_CHAR];
    float Precio;
    campo_bits Codigo;
    int cantidad;
    ProductoFlag info;

} Producto_t;

void Agregar_Producto(void);

void Crear_Usuario(void);

Usuario_t Iniciar_sesion(void);

int main()
{
    Usuario_t Usuario_iniciado;

    printf("Bienvenido a Super Baumaro\n");

    do
    {

        Usuario_iniciado = Iniciar_sesion();

    } while (strcmp(Usuario_iniciado.Nombre_Usuario, "error") == 0);

    printf("Desea acceder al sistema de admin? \n(1) - Si \n(0) - no");
    int *VE = (int *)malloc(sizeof(int));
    scanf("%d", &VE);

    if (*VE == Usuario_iniciado.Rango)
    {
    }
    else if (Usuario_iniciado.Rango == FALSE)
    {

        printf("tu usuario no tiene acceso a este panel\n");
    }

    free(VE);

    printf("\nDesea ver el catalogo de productos? \n(1) - Si \n(0) - no");
    int *VE = (int *)malloc(sizeof(int));
    scanf("%d", &VE);

    if (*VE == TRUE)
    {
        /* code */
    }
    free(VE);
}

void Crear_Usuarios()
{

    Usuario_t *Nuevo_Usuario = (Usuario_t *)malloc(sizeof(Usuario_t));

    printf("\nIngrese el nombre de usuario de la cuenta: ");
    scanf("%s", Nuevo_Usuario->Nombre_Usuario);

    printf("\nIngrese la contraseña de la cuenta: ");
    scanf("%s", Nuevo_Usuario->Contraseña);

    printf("\nIngrese el rango que quiere asignarle a la cuenta: ");
    scanf("%d", &Nuevo_Usuario->Rango);

    FILE *fp = fopen("Base_de_usuarios.csv", "a");

    fprintf(fp, "%s,%s,%d\n", Nuevo_Usuario->Nombre_Usuario, Nuevo_Usuario->Contraseña, Nuevo_Usuario->Rango);

    fclose(fp);
    free(Nuevo_Usuario);
}

Usuario_t Iniciar_sesion()
{

    Usuario_t Usuario_inicio;

    char *Linea = (char *)malloc(MAX_LINEA * sizeof(char));

    printf("\nIngrese el nombre de usuario de la cuenta que quiere iniciar sesion, en caso de no tener pedir a un admin que cree una para usted: ");
    scanf("%s", Usuario_inicio.Nombre_Usuario);

    printf("\nIngrese la contraseña de la cuenta que quiere iniciar sesion: ");
    scanf("%s", Usuario_inicio.Contraseña);

    FILE *fp = fopen("Base_de_usuarios.csv", "r");

    while (fgets(Linea, MAX_LINEA, fp))
    {
        Usuario_t *UA = (Usuario_t *)malloc(sizeof(Usuario_t));
        strcpy(UA->Nombre_Usuario, strtok(*Linea, ","));
        strcpy(UA->Contraseña, strtok(NULL, ","));
        UA->Rango = atoi(strtok(NULL, ","));

        if (strcmp(UA->Nombre_Usuario, Usuario_inicio.Nombre_Usuario) == 0)
        {

            if (strcmp(UA->Contraseña, Usuario_inicio.Contraseña) == 0)
            {

                Usuario_inicio.Rango = UA->Rango;
                printf("se ha iniciado sesion con exito");

                free(UA);
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

            free(UA);
        }
    }
}

void Agregar_Producto(void)
{

    Producto_t Nuevo_Producto;

    printf("ingrese el nombre del producto que quiere agregar\n");
    scanf("%s", Nuevo_Producto.Nombre);

    printf("ingrese el precio del producto\n");
    scanf("%i", Nuevo_Producto.Precio);

    printf("ingrese la cantidad de producto del objeto\n");
    scanf("%i", &Nuevo_Producto.cantidad);

    printf("ingrese (1) - TRUE o (0) - FALSE para los siguientes 8 valores\n");
    printf("(1) - disponibilidad \n");
    printf("(2) - oferta \n");
    printf("(3) - agotado \n");
    printf("(4) - reservado \n");
    printf("(5) - perecedero \n");
    printf("(6) - fragil \n");
    printf("(7) - importado \n");
    printf("(8) - exclusivo \n");

    int *disponible = (int *)malloc(sizeof(int));
    int *oferta = (int *)malloc(sizeof(int));
    int *agotado = (int *)malloc(sizeof(int));
    int *reservado = (int *)malloc(sizeof(int));
    int *perecedero = (int *)malloc(sizeof(int));
    int *fragil = (int *)malloc(sizeof(int));
    int *importado = (int *)malloc(sizeof(int));
    int *exclusivo = (int *)malloc(sizeof(int));

    scanf("%i", &disponible);
    scanf("%i", &oferta);
    scanf("%i", &agotado);
    scanf("%i", &reservado);
    scanf("%i", &perecedero);
    scanf("%i", &fragil);
    scanf("%i", &importado);
    scanf("%i", &exclusivo);

    Nuevo_Producto.info.flag.disponible = *disponible;
    Nuevo_Producto.info.flag.oferta = *oferta;
    Nuevo_Producto.info.flag.agotado = *agotado;
    Nuevo_Producto.info.flag.reservado = *reservado;
    Nuevo_Producto.info.flag.perecedero = *perecedero;
    Nuevo_Producto.info.flag.fragil = *fragil;
    Nuevo_Producto.info.flag.importado = *importado;
    Nuevo_Producto.info.flag.exclusivo = *exclusivo;

    free(disponible);
    free(oferta);
    free(agotado);
    free(reservado);
    free(perecedero);
    free(fragil);
    free(importado);
    free(exclusivo);

    FILE *fp = fopen("Base_objetos.csv", "a");

    fprintf(fp, "%s");
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    int Codigo;
    int cantidad;
    ProductoFlag info;

} Producto_t;

int Contar_Lineas_Csv(FILE *fp);

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

    printf("desea ingresar un producto\n");

    int *VE = (int *)malloc(sizeof(int));
    scanf("%i", VE);

    if (*VE == 1)
    {
        Agregar_Producto();
    }
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

    if (Linea == NULL)
    {
        printf("\nNo hay sufieciente memoria disponible");
        exit(-1);
    }

    printf("\nIngrese el nombre de usuario de la cuenta que quiere iniciar sesion, en caso de no tener pedir a un admin que cree una para usted: ");
    scanf("%s", Usuario_inicio.Nombre_Usuario);

    printf("\nIngrese la contraseña de la cuenta que quiere iniciar sesion: ");
    scanf("%s", Usuario_inicio.Contraseña);

    FILE *fp = fopen("Base_de_usuarios.csv", "r");

    if (fp == NULL)
    {
        printf("\nError no se ha encontrado el archivo");
        exit(-1);
    }

    Usuario_t *UA = (Usuario_t *)malloc(sizeof(Usuario_t));

    if (UA == NULL)
    {
        printf("\nError no hay mas espacio");
        exit(-1);
    }

    while (fgets(Linea, MAX_LINEA, fp))
    {

        strcpy(UA->Nombre_Usuario, strtok(Linea, ","));
        strcpy(UA->Contraseña, strtok(NULL, ","));
        UA->Rango = atoi(strtok(NULL, ","));

        if (strcmp(UA->Nombre_Usuario, Usuario_inicio.Nombre_Usuario) == 0)
        {

            if (strcmp(UA->Contraseña, Usuario_inicio.Contraseña) == 0)
            {

                Usuario_inicio.Rango = UA->Rango;
                printf("\nse ha iniciado sesion con exito\n");

                free(UA);
                free(Linea);
                return Usuario_inicio;
            }
        }
    }

    free(UA);

    printf("\nEl nombre de usuario o contraseña son incorrectos, por favor vuelva a ingresarlos");
    strcpy(Usuario_inicio.Nombre_Usuario, "error");

    free(Linea);

    return Usuario_inicio;
}

void Agregar_Producto(void)
{

    Producto_t Nuevo_Producto;

    printf("\ningrese el nombre del producto que quiere agregar\n");
    scanf("%s", Nuevo_Producto.Nombre);

    printf("\ningrese el precio del producto\n");
    scanf("%i", Nuevo_Producto.Precio);

    printf("\ningrese la cantidad de producto del objeto\n");
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

    int *caracteristicas_ = (int *)malloc(8 * sizeof(int));

    if (caracteristicas_ == NULL)
    {
        printf("\nNo hay sufieciente memoria disponible");
        exit(-1);
    }

    scanf("%i", &caracteristicas_);
    scanf("%i", (&caracteristicas_ + 1));
    scanf("%i", (&caracteristicas_ + 2));
    scanf("%i", (&caracteristicas_ + 3));
    scanf("%i", (&caracteristicas_ + 4));
    scanf("%i", (&caracteristicas_ + 5));
    scanf("%i", (&caracteristicas_ + 6));
    scanf("%i", (&caracteristicas_ + 7));

    Nuevo_Producto.info.flag.disponible = *caracteristicas_;
    Nuevo_Producto.info.flag.oferta = *(caracteristicas_ + 1);
    Nuevo_Producto.info.flag.agotado = *(caracteristicas_ + 2);
    Nuevo_Producto.info.flag.reservado = *(caracteristicas_ + 3);
    Nuevo_Producto.info.flag.perecedero = *(caracteristicas_ + 4);
    Nuevo_Producto.info.flag.fragil = *(caracteristicas_ + 5);
    Nuevo_Producto.info.flag.importado = *(caracteristicas_ + 6);
    Nuevo_Producto.info.flag.exclusivo = *(caracteristicas_ + 7);

    free(caracteristicas_);

    FILE *fp = fopen("Base_objetos.csv", "a");

    if (fp == NULL)
    {
        printf("\nError no se ha encontrado el archivo");
        exit(-1);
    }

    Nuevo_Producto.Codigo = Contar_Lineas_Csv(fp);

    fprintf(fp, "%s,%i,%i,%u,%i", Nuevo_Producto.Nombre, Nuevo_Producto.Precio, Nuevo_Producto.cantidad, Nuevo_Producto.info.estado, Nuevo_Producto.Codigo);

    fclose(fp);
}

int Contar_Lineas_Csv(FILE *fp)
{

    int cant_obj = 0;

    char linea[MAX_LINEA];
    while (fgets(linea, MAX_LINEA, fp))
    {
        cant_obj++;
    }

    return cant_obj;
}

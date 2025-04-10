#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINEA 151
#define MAX_CHAR 50
#define TRUE 1
#define FALSE 0
#define VALOR_ERROR -1

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

void Imprimir_objetos(void);

void Imprimir_Usuario(void);

int Contar_Lineas_Csv(FILE *fp);

void Agregar_Producto(void);

void Agregar_Stock(void);

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
    if (Usuario_iniciado.Rango == 1)
    {

        printf("\ndesea ingresar al sistema de administracion?\n");

        char *VE = (char *)malloc(3 * sizeof(char));

        if (VE == NULL)
        {
            printf("\nError al reservar memoria\n");
            exit(VALOR_ERROR);
        }

        scanf("%3s", VE);

        if ((strcmp(VE, "si") == 0) || (strcmp(VE, "SI") == 0))
        {
            free(VE);

            printf("\nINGRESE UNA DE LAS SIGUIENTES OPCIONES\n");
            printf("(0) - SKIP\n");
            printf("(1) - CREAR USUARIO\n");
            printf("(2) - AGREGAR PRODUCTO\n");
            printf("(3) - AGREGAR STOCK\n");
            printf("(4) - Imprimir Objetos\n");

            int *VE = (int *)malloc(sizeof(int));

            scanf("%d", VE);

            switch (*VE)
            {
            case 1:
                Crear_Usuario();
                break;
            case 2:
                Agregar_Producto();
                break;
            case 3:
                Agregar_Stock();
                break;
            case 4:
                Imprimir_objetos();
                break;
            default:
                break;
            }
        }
        else
        {
            free(VE);
        }
    }
}

void Crear_Usuario(void)
{

    Usuario_t *Nuevo_Usuario = (Usuario_t *)malloc(sizeof(Usuario_t));

    if (Nuevo_Usuario == NULL)
    {
        printf("no se ha podido reservar la memoria");
        exit(VALOR_ERROR);
    }

    printf("\nIngrese el nombre de usuario de la cuenta: ");
    scanf("%s", Nuevo_Usuario->Nombre_Usuario);

    printf("\nIngrese la contraseña de la cuenta: ");
    scanf("%s", Nuevo_Usuario->Contraseña);

    printf("\nIngrese el rango que quiere asignarle a la cuenta: ");
    scanf("%d", &Nuevo_Usuario->Rango);

    FILE *fp = fopen("Base_de_usuarios.csv", "a");

    if (fp == NULL)
    {
        printf("no se puede abrir el archivo\n");
        exit(VALOR_ERROR);
    }

    fprintf(fp, "\n%s,%s,%d", Nuevo_Usuario->Nombre_Usuario, Nuevo_Usuario->Contraseña, Nuevo_Usuario->Rango);

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
        exit(VALOR_ERROR);
    }

    printf("\nIngrese el nombre de usuario de la cuenta que quiere iniciar sesion, en caso de no tener pedir a un admin que cree una para usted: ");
    scanf("%s", Usuario_inicio.Nombre_Usuario);

    printf("\nIngrese la contraseña de la cuenta que quiere iniciar sesion: ");
    scanf("%s", Usuario_inicio.Contraseña);

    FILE *fp = fopen("Base_de_usuarios.csv", "r");

    if (fp == NULL)
    {
        printf("\nError no se ha encontrado el archivo");
        exit(VALOR_ERROR);
    }

    Usuario_t *UA = (Usuario_t *)malloc(sizeof(Usuario_t));

    if (UA == NULL)
    {
        printf("\nError no hay mas espacio");
        exit(VALOR_ERROR);
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
    scanf("%f", &Nuevo_Producto.Precio);

    printf("\ningrese la cantidad de producto del objeto\n");
    scanf("%i", &Nuevo_Producto.cantidad);

    printf("\ningrese (1) - TRUE o (0) - FALSE para los siguientes 8 valores\n");
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
        printf("\nNo hay sufieciente memoria disponible\n");
        exit(VALOR_ERROR);
    }

    for (int i = 0; i < 8; i++)
    {
        if (scanf("%i", caracteristicas_ + i) != 1)
        {

            printf("\n Error al leer el dato");
            exit(VALOR_ERROR);
        }
    }

    Nuevo_Producto.info.flag.disponible = *caracteristicas_;
    Nuevo_Producto.info.flag.oferta = *(caracteristicas_ + 1);
    Nuevo_Producto.info.flag.agotado = *(caracteristicas_ + 2);
    Nuevo_Producto.info.flag.reservado = *(caracteristicas_ + 3);
    Nuevo_Producto.info.flag.perecedero = *(caracteristicas_ + 4);
    Nuevo_Producto.info.flag.fragil = *(caracteristicas_ + 5);
    Nuevo_Producto.info.flag.importado = *(caracteristicas_ + 6);
    Nuevo_Producto.info.flag.exclusivo = *(caracteristicas_ + 7);

    free(caracteristicas_);

    FILE *fp = fopen("Base_objetos.csv", "r");

    if (fp == NULL)
    {
        printf("\nError no se ha encontrado el archivo\n");
        exit(VALOR_ERROR);
    }

    Nuevo_Producto.Codigo = Contar_Lineas_Csv(fp);

    fclose(fp);

    fp = fopen("Base_objetos.csv", "a");

    fprintf(fp, "\n%s,%f,%i,%u,%i", Nuevo_Producto.Nombre, Nuevo_Producto.Precio, Nuevo_Producto.cantidad, Nuevo_Producto.info.estado, Nuevo_Producto.Codigo);

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

void Agregar_Stock()
{
    FILE *fp = fopen("Base_objetos.csv", "r");

    FILE *fp_aux = fopen("Archivo_temporal_obj.csv", "w");

    char *Linea = (char *)malloc(MAX_LINEA * sizeof(char));

    if (Linea == NULL)
    {
        printf("\nNo hay sufieciente memoria disponible");
        exit(VALOR_ERROR);
    }

    Producto_t *PI = (Producto_t *)malloc(sizeof(Producto_t));

    printf("\ningrese el nombre del objeto que quiero cambiar el stock\n");

    scanf("%49s", PI->Nombre);

    printf("\ningrese la cantidad que quiere aniadir\n");

    scanf("%i", &PI->cantidad);

    Producto_t *LP = (Producto_t *)malloc(sizeof(Producto_t));

    if (LP == NULL)
    {
        printf("\n Error memoria insuficiente");
        exit(VALOR_ERROR);
    }

    int *info_int = (int *)malloc(sizeof(int));

    if (info_int == NULL)
    {
        printf("\n Error memoria insuficiente");
        exit(VALOR_ERROR);
    }

    while (fgets(Linea, MAX_LINEA, fp))
    {

        strcpy(LP->Nombre, strtok(Linea, ","));

        if ((strcmp(LP->Nombre, PI->Nombre) == 0))
        {

            LP->Precio = atof(strtok(NULL, ","));
            LP->cantidad = atoi(strtok(NULL, ",")) + PI->cantidad;
            *info_int = atoi(strtok(NULL, ","));
            LP->Codigo = atoi(strtok(NULL, ","));

            fprintf(fp_aux, "\n%s,%f,%i,%i,%i", LP->Nombre, LP->Precio, LP->cantidad, *info_int, LP->Codigo);
        }
        else
        {
            fprintf(fp_aux, "\n%s", Linea);
        }
    }

    fclose(fp);
    fclose(fp_aux);

    free(LP);
    free(info_int);

    fp = fopen("Base_objetos.csv", "w");

    fp_aux = fopen("Archivo_temporal_obj.csv", "r");

    if (fp == NULL)
    {
        printf("no se encontro el archivo ");
        exit(VALOR_ERROR);
    }

    if (fp_aux == NULL)
    {
        printf("no se encontro el archivo ");
        exit(VALOR_ERROR);
    }

    while (fgets(Linea, MAX_LINEA, fp_aux))
    {
        fprintf(fp, "%s", Linea);
    }

    fclose(fp);
    fclose(fp_aux);
}

void Imprimir_objetos(void)
{
    FILE *fp = fopen("Base_objetos.csv", "r");

    if (fp == NULL)
    {
        printf("\n no se encontro el archivo");
        exit(VALOR_ERROR);
    }

    Producto_t *PA = (Producto_t *)malloc(sizeof(Producto_t));

    if (PA == NULL)
    {
        printf("\n Error no se pudo reservar la memoria ");
        exit(VALOR_ERROR);
    }

    char *linea = (char *)malloc(MAX_LINEA * sizeof(char));

    if (linea == NULL)
    {
        printf("\n Error no se pudo reservar la memoria \n");
        exit(VALOR_ERROR);
    }

    printf("\nINFO: \n");
    printf("(1) - disponibilidad \n");
    printf("(2) - oferta \n");
    printf("(3) - agotado \n");
    printf("(4) - reservado \n");
    printf("(5) - perecedero \n");
    printf("(6) - fragil \n");
    printf("(7) - importado \n");
    printf("(8) - exclusivo \n");

    int i = 0;
    while (fgets(linea, MAX_LINEA, fp))
    {
        if (i == 0)
        {
            printf("\n%s\n", linea);
        }
        else
        {

            strcpy(PA->Nombre, strtok(linea, ","));
            PA->Precio = atof(strtok(NULL, ","));
            PA->cantidad = atoi(strtok(NULL, ","));
            PA->info.estado = atoi(strtok(NULL, ","));
            PA->Codigo = atoi(strtok(NULL, ","));

            printf("\n%s| %2f| %d| %i %i %i %i %i %i %i %i| %i \n", PA->Nombre, PA->Precio, PA->cantidad, PA->info.flag.disponible, PA->info.flag.oferta, PA->info.flag.agotado, PA->info.flag.reservado, PA->info.flag.perecedero, PA->info.flag.fragil, PA->info.flag.importado, PA->info.flag.exclusivo, PA->Codigo);
        }
        i++;
    }

    free(linea);
    free(PA);
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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

} productoFlag;

typedef struct
{

    char nombre_usuario[MAX_CHAR];
    char contrasenia[MAX_CHAR];
    int rango;

} usuario_t;

typedef struct
{

    char nombre[MAX_CHAR];
    float precio;
    int Codigo;
    int cantidad;
    productoFlag info;

} producto_t;

typedef struct lineas_t
{

    char linea[MAX_LINEA];
    struct lineas_t *next;

} lineas_t;

// funciones de uso principal

void imprimir_objetos(void);

void Imprimir_Usuario(void);

void agregar_producto(void);

void agregar_Stock(void);

void crear_usuario(void);

int comprar(void);

usuario_t iniciar_sesion(void);

// funciones de encapsulamiento

void menu_usuario(void); // imprime el menu de usuarios

void menu_admin(void); // imprime el menu de admins

void menu_info_obj(void); // imprime la explicacion del valor info del objeto

char *crear_linea(void); // crear una variable dinamica de un string para almacenar una linea del archivo

int *contar_lineas_csv(FILE *fp); // cuenta la cantidad de lineas de un archivo

producto_t ingresar_info(producto_t); // pide la informacion en bits de la caracteristica info de la estructura del objeto

void seleccion_menu_admin(void); // logica de seleccion del menu de admin

int *VE_int(void); // crea la variable dinamica Variable Eleccion que se usa para logica de eleccion

char *VE_char(void); // crear una variable dinamica de si/no en un string para logica de seleccion

lineas_t *crear_lineas_enlazadas(); // crea una structura enlazada que contiene un string del tamanio maximo de una linea del archivo

int comprar(void);

producto_t *crear_malloc_producto(void); // crea una structura dinamica de un objeto para comparaciones y elecciones

void liberar_lista_enlazada(lineas_t *lista); // libera una lista enlazada

int main()
{

    usuario_t usuario_iniciado;

    printf("Bienvenido a Super Baumaro\n");

    do
    {

        usuario_iniciado = iniciar_sesion();

    } while (strcmp(usuario_iniciado.nombre_usuario, "error") == 0);

    int *apagar = VE_int();

    do
    {
        if (usuario_iniciado.rango == 1)
        {

            printf("\ndesea ingresar al sistema de administracion?\n\n");

            char *VE = VE_char();

            scanf("%3s", VE);

            if ((strcmp(VE, "si") == 0) || (strcmp(VE, "SI") == 0))
            {

                menu_admin();

                seleccion_menu_admin();
            }

            printf("\ndesea ingresar al sistema de usuario?\n\n");

            scanf("%3s", VE);

            if ((strcmp(VE, "si") == 0) || (strcmp(VE, "Si") == 0))
            {

                menu_usuario();

                int *VE = VE_int();

                scanf("%d", VE);

                switch (*VE)
                {
                case 0:
                    int resultado = comprar();

                    if (resultado == VALOR_ERROR)
                    {
                        printf("\nel nombre del objeto que ingresaste puede no existir\n");
                    }
                    break;
                case 1:
                    imprimir_objetos();
                    break;
                default:
                    break;
                }
            }
            free(VE);
        }

        printf("\nsi desea seguir operando ingrese un 1\n");

        scanf("%i", *apagar);

    } while (*apagar == 1);

    free(apagar);
}

void crear_usuario(void)
{

    usuario_t *nuevo_usuario = (usuario_t *)malloc(sizeof(usuario_t));

    if (nuevo_usuario == NULL)
    {
        printf("no se ha podido reservar la memoria");
        exit(VALOR_ERROR);
    }

    printf("\nIngrese el nombre de usuario de la cuenta: ");
    scanf("%s", nuevo_usuario->nombre_usuario);

    printf("\nIngrese la contrasenia de la cuenta: ");
    scanf("%s", nuevo_usuario->contrasenia);

    printf("\nIngrese el rango que quiere asignarle a la cuenta: ");
    scanf("%d", &nuevo_usuario->rango);

    FILE *fp = fopen("Base_de_usuarios.csv", "a");

    if (fp == NULL)
    {
        printf("no se puede abrir el archivo\n");
        exit(VALOR_ERROR);
    }

    fprintf(fp, "\n%s,%s,%d", nuevo_usuario->nombre_usuario, nuevo_usuario->contrasenia, nuevo_usuario->rango);

    fclose(fp);
    free(nuevo_usuario);
}

usuario_t iniciar_sesion()
{

    usuario_t usuario_inicio;

    char *linea = crear_linea();

    printf("\nIngrese el nombre de usuario de la cuenta que quiere iniciar sesion, en caso de no tener pedir a un admin que cree una para usted: ");
    scanf("%s", usuario_inicio.nombre_usuario);

    printf("\nIngrese la contrasenia de la cuenta que quiere iniciar sesion: ");
    scanf("%s", usuario_inicio.contrasenia);

    FILE *fp = fopen("Base_de_usuarios.csv", "r");

    if (fp == NULL)
    {
        printf("\nError no se ha encontrado el archivo");
        exit(VALOR_ERROR);
    }

    usuario_t *UA = (usuario_t *)malloc(sizeof(usuario_t));

    if (UA == NULL)
    {
        printf("\nError no hay mas espacio");
        exit(VALOR_ERROR);
    }

    while (fgets(linea, MAX_LINEA, fp))
    {

        strcpy(UA->nombre_usuario, strtok(linea, ","));
        strcpy(UA->contrasenia, strtok(NULL, ","));
        UA->rango = atoi(strtok(NULL, ","));

        if (strcmp(UA->nombre_usuario, usuario_inicio.nombre_usuario) == 0)
        {

            if (strcmp(UA->contrasenia, usuario_inicio.contrasenia) == 0)
            {

                usuario_inicio.rango = UA->rango;
                printf("\nse ha iniciado sesion con exito\n");

                free(UA);
                free(linea);
                return usuario_inicio;
            }
        }
    }

    free(UA);

    printf("\nEl nombre de usuario o contrasenia son incorrectos, por favor vuelva a ingresarlos");
    strcpy(usuario_inicio.nombre_usuario, "error");

    free(linea);

    return usuario_inicio;
}

void agregar_producto(void) // anda
{

    producto_t nuevo_producto;

    printf("\ningrese el nombre del producto que quiere agregar\n\n");
    scanf("%s", nuevo_producto.nombre);

    printf("\ningrese el precio del producto\n\n");
    scanf("%f", &nuevo_producto.precio);

    printf("\ningrese la cantidad de producto del objeto\n\n");
    scanf("%i", &nuevo_producto.cantidad);

    FILE *fp = fopen("Base_objetos.csv", "r");

    if (fp == NULL)
    {
        printf("\nError no se ha encontrado el archivo\n");
        exit(VALOR_ERROR);
    }
    nuevo_producto = ingresar_info(nuevo_producto);

    int *cant_obj = contar_lineas_csv(fp);

    nuevo_producto.Codigo = *cant_obj;

    free(cant_obj);

    fclose(fp);

    fp = fopen("Base_objetos.csv", "a");

    fprintf(fp, "\n%s,%f,%i,%u,%i", nuevo_producto.nombre, nuevo_producto.precio, nuevo_producto.cantidad, nuevo_producto.info.estado, nuevo_producto.Codigo);

    fclose(fp);
}

int *contar_lineas_csv(FILE *fp)
{

    int *cant_obj = (int *)malloc(sizeof(int));

    *cant_obj = 0;

    char linea[MAX_LINEA];

    while (fgets(linea, MAX_LINEA, fp))
    {
        (*cant_obj)++;
    }

    return cant_obj;
}

void agregar_Stock()
{
    FILE *fp = fopen("Base_objetos.csv", "r");

    FILE *fp_aux = fopen("Archivo_temporal_obj.csv", "w");

    char *linea = crear_linea();
    char *linea_aux = crear_linea();

    producto_t *PI = (producto_t *)malloc(sizeof(producto_t));

    printf("\ningrese el nombre del objeto que quiero cambiar el stock\n");

    scanf("%49s", PI->nombre);

    printf("\ningrese la cantidad que quiere aniadir\n");

    scanf("%i", &PI->cantidad);

    producto_t *LP = (producto_t *)malloc(sizeof(producto_t));

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

    while (fgets(linea_aux, MAX_LINEA, fp))
    {
        strcpy(linea, linea_aux);
        strcpy(LP->nombre, strtok(linea, ","));

        if ((strcmp(LP->nombre, PI->nombre) == 0))
        {

            LP->precio = atof(strtok(NULL, ","));
            LP->cantidad = atoi(strtok(NULL, ",")) + PI->cantidad;
            *info_int = atoi(strtok(NULL, ","));
            LP->Codigo = atoi(strtok(NULL, ","));

            fprintf(fp_aux, "%s,%f,%i,%i,%i\n", LP->nombre, LP->precio, LP->cantidad, *info_int, LP->Codigo);
        }
        else
        {
            fprintf(fp_aux, "%s", linea_aux);
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

    while (fgets(linea, MAX_LINEA, fp_aux))
    {
        fprintf(fp, "%s", linea);
    }

    fclose(fp);
    fclose(fp_aux);
}

int comprar()
{

    FILE *fp = fopen("Base_objetos.csv", "r");

    if (fp == NULL)
    {
        printf("\nError, no se ha encontrado el archivo\n");
        exit(VALOR_ERROR);
    }

    int *cant_obj = contar_lineas_csv(fp);

    printf("\ncant: %i\n", *cant_obj);

    fseek(fp, 0, SEEK_SET);

    lineas_t *lineas_aux = crear_lineas_enlazadas();

    lineas_t *lineas = crear_lineas_enlazadas();

    lineas_t *lineas_inicio = lineas;

    producto_t *producto_ingreso = crear_malloc_producto();
    producto_t *producto_fp = crear_malloc_producto();

    printf("\ningrese el nombre del producto:");
    scanf("%49s", producto_ingreso->nombre);

    printf("\ningrese la cantidad que quiere comprar: ");
    scanf("%i", &producto_ingreso->cantidad);

    while (fgets(lineas->linea, MAX_LINEA, fp))
    {

        strcpy(lineas_aux->linea, lineas->linea);
        strcpy(producto_fp->nombre, strtok(lineas_aux->linea, ","));

        if ((strcmp(producto_ingreso->nombre, producto_fp->nombre) == 0))
        {

            producto_fp->precio = atof(strtok(NULL, ","));
            producto_fp->cantidad = atoi(strtok(NULL, ","));
            producto_fp->info.estado = atoi(strtok(NULL, ","));
            producto_fp->Codigo = atoi(strtok(NULL, ","));

            if ((producto_fp->cantidad - producto_ingreso->cantidad) < 0)
            {
                printf("\n no hay stock suficiente\n");
                return -1;
            }

            producto_fp->cantidad = producto_fp->cantidad - producto_ingreso->cantidad;

            sprintf(lineas->linea, "%s,%f,%i,%i,%i\n", producto_fp->nombre, producto_fp->precio, producto_fp->cantidad, producto_fp->info.estado, producto_fp->Codigo);
        }

        lineas_t *linea_next = crear_lineas_enlazadas();
        lineas->next = linea_next;
        linea_next->next = NULL;
        lineas = linea_next;
    }

    fclose(fp);

    fp = fopen("Base_objetos.csv", "w");

    lineas = lineas_inicio;

    printf("\n%s\n", lineas_inicio->linea);

    for (int i = 0; i < *cant_obj; i++)
    {
        fprintf(fp, "%s", lineas->linea);

        lineas = lineas->next;
    }

    fclose(fp);

    free(cant_obj);

    free(producto_fp);
    free(producto_ingreso);
    free(lineas_aux);

    liberar_lista_enlazada(lineas);

    return 0;
}

void imprimir_objetos(void)
{

    FILE *fp = fopen("Base_objetos.csv", "r");

    if (fp == NULL)
    {
        printf("\n no se encontro el archivo");
        exit(VALOR_ERROR);
    }

    producto_t *PA = (producto_t *)malloc(sizeof(producto_t));

    if (PA == NULL)
    {
        printf("\n Error no se pudo reservar la memoria ");
        exit(VALOR_ERROR);
    }

    char *linea = crear_linea();

    printf("\nINFO: \n");
    menu_info_obj();

    int i = 0;
    while (fgets(linea, MAX_LINEA, fp))
    {
        if (i == 0)
        {
            printf("%s\n", linea);
        }
        else
        {

            strcpy(PA->nombre, strtok(linea, ","));
            PA->precio = atof(strtok(NULL, ","));
            PA->cantidad = atoi(strtok(NULL, ","));
            PA->info.estado = atoi(strtok(NULL, ","));
            PA->Codigo = atoi(strtok(NULL, ","));

            printf("\n%s| %2f| %d| %i %i %i %i %i %i %i %i| %i \n", PA->nombre, PA->precio, PA->cantidad, PA->info.flag.disponible, PA->info.flag.oferta, PA->info.flag.agotado, PA->info.flag.reservado, PA->info.flag.perecedero, PA->info.flag.fragil, PA->info.flag.importado, PA->info.flag.exclusivo, PA->Codigo);
        }
        i++;
    }

    free(linea);
    free(PA);
}

char *crear_linea(void)
{

    char *linea = (char *)malloc(MAX_LINEA * sizeof(char));

    if (linea == NULL)
    {
        printf("\nNo hay sufieciente memoria disponible");
        exit(VALOR_ERROR);
    }

    return linea;
}

lineas_t *crear_lineas_enlazadas()
{

    lineas_t *lista = (lineas_t *)malloc(sizeof(lineas_t));

    if (lista == NULL)
    {
        printf("Error, almacenamiento insuficiente");
        exit(VALOR_ERROR);
    }

    return lista;
}

void liberar_lista_enlazada(lineas_t *lista)
{

    bool *final_lista = (bool *)malloc(sizeof(bool));

    if (final_lista == NULL)
    {
        printf("\nError, espacio insuficiente\n");
        exit(VALOR_ERROR);
    }

    do
    {

        lineas_t *lista_aux = lista;
        lista = lista->next;

        free(lista_aux);

        if (lista == NULL)
        {
            *final_lista = FALSE;
        }

    } while (*final_lista);
}

producto_t ingresar_info(producto_t nuevo_producto)
{

    printf("\ningrese (1) - TRUE o (0) - FALSE para los siguientes 8 valores\n");
    menu_info_obj();

    int *caracteristicas_ = (int *)malloc(8 * sizeof(int));

    if (caracteristicas_ == NULL)
    {
        printf("\nNo hay sufieciente memoria disponible\n");
        exit(VALOR_ERROR);
    }

    for (int i = 0; i < 8; i++)
    {
        scanf("%i", (caracteristicas_ + i));

        if ((*(caracteristicas_ + i) > 1) || (*(caracteristicas_ + i) < 0))
        {
            printf("\n Error al leer el dato");
            exit(VALOR_ERROR);
        }
    }

    nuevo_producto.info.flag.disponible = *caracteristicas_;
    nuevo_producto.info.flag.oferta = *(caracteristicas_ + 1);
    nuevo_producto.info.flag.agotado = *(caracteristicas_ + 2);
    nuevo_producto.info.flag.reservado = *(caracteristicas_ + 3);
    nuevo_producto.info.flag.perecedero = *(caracteristicas_ + 4);
    nuevo_producto.info.flag.fragil = *(caracteristicas_ + 5);
    nuevo_producto.info.flag.importado = *(caracteristicas_ + 6);
    nuevo_producto.info.flag.exclusivo = *(caracteristicas_ + 7);

    free(caracteristicas_);

    return nuevo_producto;
}

void menu_admin()
{

    printf("\nINGRESE UNA DE LAS SIGUIENTES OPCIONES\n");
    printf("(0) - SKIP\n");
    printf("(1) - CREAR USUARIO\n");
    printf("(2) - AGREGAR PRODUCTO\n");
    printf("(3) - AGREGAR STOCK\n");
    printf("(4) - Imprimir Objetos\n\n");
}

void menu_usuario()
{

    printf("\nINGRESE UNA DE LAS SIGUIENTES OPCIONES\n");
    printf("(0) - COMPRAR\n");
    printf("(1) - Imprimir Objetos\n\n");
}

void menu_info_obj()
{

    printf("(1) - disponibilidad \n");
    printf("(2) - oferta \n");
    printf("(3) - agotado \n");
    printf("(4) - reservado \n");
    printf("(5) - perecedero \n");
    printf("(6) - fragil \n");
    printf("(7) - importado \n");
    printf("(8) - exclusivo \n");
}

void seleccion_menu_admin(void)
{

    int *VE = VE_int();

    scanf("%d", VE);

    switch (*VE)
    {
    case 1:
        crear_usuario();
        break;
    case 2:
        agregar_producto();
        break;
    case 3:
        agregar_Stock();
        break;
    case 4:
        imprimir_objetos();
        break;
    default:
        break;
    }

    free(VE);
}

int *VE_int()
{

    int *VE = (int *)malloc(sizeof(int));

    if (VE == NULL)
    {

        printf("\nERROR, espacio insuficiente\n");
        exit(VALOR_ERROR);
    }

    return VE;
}

char *VE_char()
{

    char *VE = (char *)malloc(3 * sizeof(char));

    if (VE == NULL)
    {
        printf("\nERROR, espacio insuficiente\n");
        exit(VALOR_ERROR);
    }

    return VE;
}

producto_t *crear_malloc_producto(void)
{

    producto_t *producto = (producto_t *)malloc(sizeof(producto_t));

    if (producto == NULL)
    {
        printf("\nERROR, espacio insuficiente\n");
        exit(VALOR_ERROR);
    }

    return producto;
}

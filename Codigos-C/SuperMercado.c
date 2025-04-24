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

// funciones de uso principal 

void imprimir_objetos(void);

void Imprimir_Usuario(void);

void agregar_producto(void);

void agregar_Stock(void);

void crear_usuario(void);

int comprar(void);

usuario_t iniciar_sesion(void);

// funciones de encapsulamiento 

void menu_usuario(void);

void menu_admin(void);

void menu_info_obj(void);

char* crear_linea(void);

int contar_lineas_csv(FILE *fp);

producto_t ingresar_info(producto_t);

void seleccion_menu_admin(void);

int* VE_int(void);

char* VE_char(void);

int comprar(void);

producto_t* crear_malloc_producto(void);



int main(){
    usuario_t usuario_iniciado;

    printf("Bienvenido a Super Baumaro\n");

    do
    {

        usuario_iniciado = iniciar_sesion();

    } while (strcmp(usuario_iniciado.nombre_usuario, "error") == 0);

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

        if ((strcmp(VE,"si") == 0) || (strcmp(VE,"Si") == 0))
        {

            menu_usuario();

            int *VE = VE_int();

            scanf("%d", VE);

            switch(*VE)
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

void agregar_producto(void) //anda
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

    nuevo_producto.Codigo = contar_lineas_csv(fp);

    fclose(fp);

    fp = fopen("Base_objetos.csv", "a");

    fprintf(fp, "\n%s,%f,%i,%u,%i", nuevo_producto.nombre, nuevo_producto.precio, nuevo_producto.cantidad, nuevo_producto.info.estado, nuevo_producto.Codigo);

    fclose(fp);
}

int contar_lineas_csv(FILE *fp)
{

    int cant_obj = 0;

    char linea[MAX_LINEA];
    while (fgets(linea, MAX_LINEA, fp))
    {
        cant_obj++;
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

            fprintf(fp_aux, "%s,%f,%i,%i,%i", LP->nombre, LP->precio, LP->cantidad, *info_int, LP->Codigo);
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

int comprar(){


    printf("\ningrese el nombre del producto que desea comprar: ");

    producto_t *producto_ingreso = crear_malloc_producto();

    scanf("%s", producto_ingreso->nombre);

    printf("\ningrese la cantidad que quiere comprar\n");

    scanf("%d", producto_ingreso->cantidad);

    printf("%d", producto_ingreso->cantidad);

    FILE *fp = fopen("Base_objetos.csv", "r");
    FILE *fp_aux = fopen ("Archivo_temporal_obj.csv", "w");

    if (fp == NULL)
    {
        printf("ERROR, no se ha encontrado el archivo");
        exit(VALOR_ERROR);
    }

    if (fp_aux == NULL)
    {
        printf("ERROR, no se ha encontrado el archivo");
        exit(VALOR_ERROR);
    }
    
    
    producto_t *producto_aux = crear_malloc_producto();

    char *linea = crear_linea();
    char *linea_aux = crear_linea();

    while (fgets(linea, MAX_LINEA, fp))
    {
        strcpy(linea_aux, linea);
        strcpy(producto_aux->nombre, strtok(linea, ","));

        if ((strcmp(producto_aux->nombre, producto_ingreso->nombre) == 0))
        {

            producto_aux->precio = atof(strtok(NULL,","));
            producto_aux->cantidad = atoi(strtok(NULL,","));
            producto_aux->info.estado = atoi(strtok(NULL,","));
            producto_aux->Codigo = atoi(strtok(NULL,","));

            printf("COSTE A PAGAR = %d", producto_aux->precio * producto_ingreso->cantidad);

            producto_aux->cantidad = producto_aux->cantidad - producto_ingreso->cantidad;
            printf("\n\n%d\n\n", producto_aux->cantidad);

            if (producto_aux->cantidad < 0)
            {
                printf("\nno hay mas stock de ese producto\n");
                return VALOR_ERROR;
            }

            fprintf(fp_aux, "%s,%f,%i,%i,%i\n", producto_aux->nombre, producto_aux->precio, producto_aux->cantidad, producto_aux->info.estado, producto_aux->Codigo);

        }else{
            fprintf(fp_aux, "%s\n", linea_aux);
        }
    }

    free(producto_aux);
    free(producto_ingreso);
    free(linea_aux);
    
    fp = fopen("Base_objetos.csv", "w");
    fp_aux = fopen ("Archivo_temporal_obj.csv", "r");

    if (fp == NULL)
    {
        printf("ERROR, no se ha encontrado el archivo");
        exit(VALOR_ERROR);
    }

    if (fp_aux == NULL)
    {
        printf("ERROR, no se ha encontrado el archivo");
        exit(VALOR_ERROR);
    }
    while (fgets(linea,MAX_LINEA, fp_aux))
    {
        printf("%s", linea);

        fprintf(fp, "%s", linea);
    }

    free(linea);
    fclose(fp);
    fclose(fp_aux);
    
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

    char* linea = crear_linea();

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

char* crear_linea(void){

    char *linea = (char *)malloc(MAX_LINEA * sizeof(char));

    if (linea == NULL)
    {
        printf("\nNo hay sufieciente memoria disponible");
        exit(VALOR_ERROR);
    }

    return linea;
}

producto_t ingresar_info(producto_t nuevo_producto){

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
        
        if ((*(caracteristicas_ + i) > 1)|| (*(caracteristicas_ + i) < 0))
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

void menu_admin(){

    printf("\nINGRESE UNA DE LAS SIGUIENTES OPCIONES\n");
    printf("(0) - SKIP\n");
    printf("(1) - CREAR USUARIO\n");
    printf("(2) - AGREGAR PRODUCTO\n");
    printf("(3) - AGREGAR STOCK\n");
    printf("(4) - Imprimir Objetos\n\n");

}

void menu_usuario(){

    printf("\nINGRESE UNA DE LAS SIGUIENTES OPCIONES\n");
    printf("(0) - COMPRAR\n");
    printf("(1) - Imprimir Objetos\n\n");

}

void menu_info_obj(){

    printf("(1) - disponibilidad \n");
    printf("(2) - oferta \n");
    printf("(3) - agotado \n");
    printf("(4) - reservado \n");
    printf("(5) - perecedero \n");
    printf("(6) - fragil \n");
    printf("(7) - importado \n");
    printf("(8) - exclusivo \n");

}

void seleccion_menu_admin(void){

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

int* VE_int(){

    int *VE = (int *)malloc(sizeof(int));

    if(VE == NULL){

        printf("\nERROR, espacio insuficiente\n");
        exit(VALOR_ERROR);
    }

    return VE;
}

char* VE_char(){

    char *VE = (char *)malloc(3 * sizeof(char));

    if (VE == NULL)
    {
        printf("\nERROR, espacio insuficiente\n");
        exit(VALOR_ERROR);
    }

    return VE;
}

producto_t* crear_malloc_producto(void){

    producto_t *producto = (producto_t*)malloc(sizeof(producto_t));

    if (producto == NULL)
    {
        printf("\nERROR, espacio insuficiente\n");
        exit(VALOR_ERROR);
    }
    
    return producto;
}


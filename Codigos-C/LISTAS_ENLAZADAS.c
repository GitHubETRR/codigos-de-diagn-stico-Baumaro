#include <stdio.h>
#define VALOR_ERROR -1

typedef struct
{

    int sueldo;
    trabajador_t *next;
    trabajador_t *before;
    char *nombre;
    char *apellido;
    char *rango;

} trabajador_t;

int *crear_VE(void);

void bienvenida(void);

char *agregar_trabajador(void);

void menu(void);

int main()
{

    bienvenida();

    menu();

    switch (*VE)
    {
    case 0:
        /* code */
        break;
    case 1:
        /* code */
        break;
    case 2:
        /* code */
        break;

    default:
        break;
    }
}

void bienvenida(void)
{
    printf("bienvenido al administrador de trabajadores");
}

void menu(void)
{

    printf("Ingrese una de las opciones \n");
    printf("(0) - agregar trabajador\n");
    printf("(1) - calcular gastos en sueldos\n");
    printf("(2) - imprimir lista de trabajadores\n");
}

nombre_t *agregar_trabajador()
{

    trabajador_t *lista_enlazada = (trabajador_t *)malloc(sizeof(trabajador_t));

    printf("ingrese los datos del sueldo del trabajador");
    scanf("%d", lista_enlazada->sueldo);

    lista_enlazada->next = NULL;
    lista_enlazada->before = NULL;

    return lista_enlazada;
}

void ingresar_nombre()
{

    printf("ingrese el nombre del trabajador");
}

int *crear_malloc_VE()
{

    int *VE = (int *)malloc(sizeof(int));

    if (VE == NULL)
    {
        printf("Error, espacio insuficiente");
        exit(VALOR_ERROR);
    }

    return VE;
}

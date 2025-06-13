#include <stdio.h>
#include <arduino.h>
#include <LiquidCrystal.h>

#define VALOR_ERROR -1

enum movimiento
{
    IZQUIERDA = -1,
    QUIETO,
    DERECHA
};

enum encoder
{
    ENCODER_1 = 6,
    ENCODER_2,
    ENCODER_OK
};

#define DISPLAY_RS 12
#define DISPLAY_ENABLE 11
int DISPLAY_RW = 0;

enum meses
{
    ENERO = 1,
    FEBRERO,
    MARZO,
    ABRIL,
    MAYO,
    JUNIO,
    JULIO,
    AGOSTO,
    SEPTIEMBRE,
    OCTUBRE,
    NOVIEMBRE,
    DICIEMBRE
}

enum display
{
    DISPLAY_D0 = 2,
    DISPLAY_D1,
    DISPLAY_D2,
    DISPLAY_D3,
    DISPLAY_D4,
    DISPLAY_D5,
    DISPLAY_D6,
    DISPLAY_D7
};

enum tiempo
{
    ANIOS = 1,
    MESES,
    DIAS,
    HORAS,
    MINUTOS,
    SEGUNDOS
};

enum estados
{
    ESTADO_A,
    ESTADO_B,
    ESTADO_C,
    ESTADO_D
};

#define COLUMNAS 16
#define FILAS 2

#define SEGUNDO 1000

// crea el objeto lcd de tipo LiquidCrystal para representar el display 16*2

LiquidCrystal lcd(DISPLAY_RS, DISPLAY_RW, DISPLAY_ENABLE, DISPLAY_D0, DISPLAY_D1, DISPLAY_D2, DISPLAY_D3, DISPLAY_D4, DISPLAY_D5, DISPLAY_D6, DISPLAY_D7);

void Actualizar_MaquinaEstado_MOVIMIENTO(int *);

void parpadear_texto(char texto[], int tiempo, int tiempo_parpadeo);

int tiempo(int tiempo[]);

bool definir_tiempo();

void setup()
{
    pinmode(DISPLAY_D0, OUTPUT); // activa los pines del 2 al 10 como salidas al lcd
    pinmode(DISPLAY_D1, OUTPUT);
    pinmode(DISPLAY_D2, OUTPUT);
    pinmode(DISPLAY_D3, OUTPUT);
    pinmode(DISPLAY_D4, OUTPUT);
    pinmode(DISPLAY_D5, OUTPUT);
    pinmode(DISPLAY_D6, OUTPUT);
    pinmode(DISPLAY_D7, OUTPUT);
    pinmode(DISPLAY_RS, OUTPUT);
    pinmode(DISPLAY_ENABLE, OUTPUT);
    pinmode(DISPLAY_RW, OUTPUT);

    pinmode(ENCODER_1, INPUT); // configura los pines de entrada del encoder
    pinmode(ENCODER_2, INPUT);
    pinmode(ENCODER_OK, INPUT);

    lcd.begin(COLUMNAS, FILAS);
}

void loop()
{
    static int tiempo[6] = {0, 0, 0, 0, 0, 0}; // vector de tiempo
    static int DisplayCursor[2] = {0, 0};      // filas y columnas del display
    static int cant_loops = 0;

    bool tiempo_seteado = false;

    if (cant_loops == 0)
    {

        DisplayCursor[1] = 0; // setear  el cursor del lcd en 0 0
        lcd.setcursor(DisplayCursor[0], DisplayCursor[1])

            while (!tiempo_seteado)
        {

            int *i_encoder = &(digitalread(ENCODER_1) || (digitalread(ENCODER_2) << 1)); // lee los datos del encoder

            int movimiento = Actualizar_MaquinaEstado_MOVIMIENTO(i_encoder); // actualiza el encoder

            tiempo_seteado = definir_hora(movimiento, DisplayCursor);
        }
    }
}

int[] tiempo(int tiempo[])
{
    tiempo[SEGUNDOS]++;
    if (tiempo[SEGUNDOS] > 60)
    {
        tiempo[SEGUNDOS] = 0;
        tiempo[MINUTOS]++;

        if (tiempo[MINUTOS] > 60)
        {

            tiempo[MINUTOS] = 0;
            tiempo[HORAS]++;

            if (tiempo[HORAS] > 24)
            {
                tiempo[HORAS] = 0;
                tiempo[DIAS]++;

                if (((tiempo[MESES] == FEBRERO) && (tiempo[DIAS] > 28)) || (((tiempo[MESES] == JUNIO) || (tiempo[MESES] == SEPTIEMBRE) || (tiempo[MESES] == ABRIL) || (tiempo[MESES] == NOVIEMBRE)) && (tiempo[DIAS] > 30)) || (tiempo[DIAS] > 31))
                {
                    tiempo[DIAS] = 0;
                    tiempo[MESES]++;

                    if (tiempo[MESES] > DICIEMBRE)
                    {
                        tiempo[ANIOS]++;
                    }
                }
            }
        }
    }
}

bool definir_hora(int movimiento, int DisplayCursor[])
{

    static int casilla;
    if (!((casilla == ANIOS) || (casilla == MESES) || (casilla == DIAS) || (casilla == HORAS) || (casilla == MINUTOS) || (casilla == SEGUNDOS)))
    {
        casilla = ANIOS;
    }

    DisplayCursor[1] = 0;
    lcd.setCursor(DisplayCursor[0], DisplayCursor[1]);
    lcd.print("FECHA: %d:%d:%d", tiempo[ANIOS], tiempo[MESES], tiempo[DIAS]); // imprime la fecha actual

    DisplayCursor[1] = 1;
    lcd.setCursor(DisplayCursor[0], DisplayCursor[1]);
    lcd.print("HORA: %d:%d:%d", tiempo[HORAS], tiempo[MINUTOS], tiempo[SEGUNDOS]); // imprime el tiempo actual

    if (1 == movimiento)
    {
        tiempo[casilla]++;
    }

    if (digitalread(ENCODER_OK) == 1)
    {
        casilla++;
    }

    return false
}

int Maquina_estado_encoderOK(int casilla)
{

    switch (casilla)
    {
    case ANIOS:
        if (digitalread(ENCODER_OK) == 1)
        {
            casilla = MESES;
        }

        break;

    case MESES:
        if (digitalread(ENCODER_OK) == 1)
        {
            casilla = DIAS;
        }

        break;
    default:
        break;
    }
}

int Actualizar_MaquinaEstado_MOVIMIENTO(int &i_encoder)
{

    int movimiento;

    switch (*i_encoder)
    case ESTADO_A:

        int Actualizacion_encoder = digitalread(ENCODER_1) || (digitalread(ENCODER_2) << 1);

    if (Actualizacion_encoder == 1)
    {
        movimiento = DERECHA;
    }
    else if (Actualizacion_encoder == 2)
    {

        *i_encoder = Actualizacion_encoder;
        movimiento = IZQUIERDA;
    }
    else if (Actualizacion_encoder == 0)
    {

        *i_encoder = Actualizacion_encoder;
        movimiento = QUIETO;
    }
    else
    {

        exit(VALOR_ERROR);
    }

    break;

case ESTADO_B:

    int Actualizacion_encoder = digitalread(ENCODER_1) || (digitalread(ENCODER_2) << 1);

    if (Actualizacion_encoder == 3)
    {

        movimiento = DERECHA;
    }
    else if (Actualizacion_encoder == 0)
    {

        *i_encoder = Actualizacion_encoder;
        movimiento = IZQUIERDA;
    }
    else if (Actualizacion_encoder == 1)
    {

        *i_encoder = Actualizacion_encoder;
        movimiento = QUIETO;
    }
    else
    {

        exit(VALOR_ERROR);
    }

    break;

case ESTADO_C:

    int Actualizacion_encoder = digitalread(ENCODER_1) || (digitalread(ENCODER_2) << 1);

    if (Actualizacion_encoder == 0)
    {

        movimiento = DERECHA;
    }
    else if (Actualizacion_encoder == 3)
    {

        *i_encoder = Actualizacion_encoder;
        movimiento = IZQUIERDA;
    }
    else if (Actualizacion_encoder == 2)
    {

        *i_encoder = Actualizacion_encoder;
        movimiento = QUIETO;
    }
    else
    {

        parpadear_texto("ERROR", "VALOR INVALIDO", 3000, 500);
        exit(VALOR_ERROR);
    }

    break;

case ESTADO_D:

    int Actualizacion_encoder = digitalread(ENCODER_1) || (digitalread(ENCODER_2) << 1);

    if (Actualizacion_encoder == 2)
    {

        movimiento = DERECHA;
    }
    else if (Actualizacion_encoder == 1)
    {

        *i_encoder = Actualizacion_encoder;
        movimiento = IZQUIERDA;
    }
    else if (Actualizacion_encoder == 3)
    {

        *i_encoder = Actualizacion_encoder;
        movimiento = QUIETO;
    }
    else
    {

        parpadear_texto("ERROR", "VALOR INVALIDO", 3000, 500);
        exit(VALOR_ERROR);
    }
    break;

    return movimiento;
}

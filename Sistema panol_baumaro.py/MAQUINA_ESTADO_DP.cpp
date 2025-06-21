#include <stdio.h>
#include <Arduino.h>
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
    ENCODER_OK = 14,
    ENCODER_DT,
    ENCODER_CLK,

};

#define DISPLAY_RS 12
#define DISPLAY_ENABLE 11
#define DISPLAY_RW 0

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
};

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
    ANIOS = 0,
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

// prototipos
int Actualizar_MaquinaEstado(int i_encoder);
int tiempo_(int tiempo[]);
bool definir_hora(int movimiento, int DisplayCursor[], int tiempo[]);
void imprimir_LCD(int DisplayCursor[], int tiempo[]);

void setup()
{
    pinMode(DISPLAY_D0, OUTPUT); // activa los pines del 2 al 10 como salidas al lcd
    pinMode(DISPLAY_D1, OUTPUT);
    pinMode(DISPLAY_D2, OUTPUT);
    pinMode(DISPLAY_D3, OUTPUT);
    pinMode(DISPLAY_D4, OUTPUT);
    pinMode(DISPLAY_D5, OUTPUT);
    pinMode(DISPLAY_D6, OUTPUT);
    pinMode(DISPLAY_D7, OUTPUT);
    pinMode(DISPLAY_RS, OUTPUT);
    pinMode(DISPLAY_ENABLE, OUTPUT);
    pinMode(DISPLAY_RW, OUTPUT);

    pinMode(ENCODER_CLK, INPUT); // configura los pines de entrada del encoder
    pinMode(ENCODER_DT, INPUT);
    pinMode(ENCODER_OK, INPUT);

    lcd.begin(COLUMNAS, FILAS);
}

void loop()
{
    static int tiempo[6] = {0, 0, 0, 0, 0, 0}; // vector de tiempo
    static int DisplayCursor[2] = {0, 0};      // filas y columnas del display
    static int cant_loops = 0;

    bool tiempo_seteado = false;

    DisplayCursor[1] = 0; // setear  el cursor del lcd en 0 0
    lcd.setCursor(DisplayCursor[0], DisplayCursor[1]);

    while (!tiempo_seteado)
    {

        int i_encoder = (digitalRead(ENCODER_CLK) || (digitalRead(ENCODER_DT) << 1)); // lee los datos del encoder
        int movimiento = Actualizar_MaquinaEstado(i_encoder);                         // actualiza el encoder

        tiempo_seteado = definir_hora(movimiento, DisplayCursor, tiempo);
    }

    while (tiempo_seteado)
    {
        tiempo_(tiempo);
        imprimir_LCD(DisplayCursor, tiempo);
        delay(SEGUNDO);
    }
}

int tiempo_(int tiempo[])
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

bool definir_hora(int movimiento, int DisplayCursor[], int tiempo[])
{

    // comprueba si casilla esta sin definir, en el caso de estar sin definir lo define
    static int casilla;
    if (!((casilla == ANIOS) || (casilla == MESES) || (casilla == DIAS) || (casilla == HORAS) || (casilla == MINUTOS) || (casilla == SEGUNDOS)))
    {
        casilla = ANIOS;
    }

    imprimir_LCD(DisplayCursor, tiempo);

    if (DERECHA == movimiento)
    {
        tiempo[casilla]++;
        // compruena que si la casilla actual se pasa del limite permitido
        switch (casilla)
        {
        case ANIOS:
            if (tiempo[casilla] > 12)
            {
                tiempo[casilla] = 0;
            }

            break;
        case MESES:
            if (tiempo[casilla] > 12)
            {
                tiempo[casilla] = 0;
            }
            break;

        case DIAS:
            if (((tiempo[MESES] == FEBRERO) && (tiempo[casilla] > 28)) || (((tiempo[MESES] == JUNIO) || (tiempo[MESES] == SEPTIEMBRE) || (tiempo[MESES] == ABRIL) || (tiempo[MESES] == NOVIEMBRE)) && (tiempo[casilla] > 30)) || (tiempo[casilla] > 31))
            {
                tiempo[casilla] = 0;
            }
            break;

        case HORAS:

            if (tiempo[casilla] > 12)
            {
                tiempo[casilla] = 0;
            }
            break;

        case MINUTOS:
            if (tiempo[casilla] > 60)
            {
                tiempo[casilla] = 0;
            }
            break;

        case SEGUNDOS:
            if (tiempo[casilla] > 60)
            {
                tiempo[casilla] = 0;
            }
            break;
        }
    }
    else if (IZQUIERDA == movimiento)
    {
        tiempo[casilla]--;

        switch (casilla)
        {
        case ANIOS:
            if (tiempo[casilla] < 0)
            {
                tiempo[casilla] = 12;
            }

            break;
        case MESES:
            if (tiempo[casilla] < 0)
            {
                tiempo[casilla] = 12;
            }
            break;

        case DIAS:
            if (tiempo[casilla] < 0)
            {
                if (tiempo[MESES] == FEBRERO)
                {
                    tiempo[casilla] = 28;
                }
                else if (tiempo[MESES] == ABRIL)
                {
                    tiempo[casilla] = 30;
                }
                else if (tiempo[MESES] == JUNIO)
                {
                    tiempo[casilla] = 30;
                }
                else if (tiempo[MESES] == SEPTIEMBRE)
                {
                    tiempo[casilla] = 30;
                }
                else if (tiempo[MESES] == NOVIEMBRE)
                {
                    tiempo[casilla] = 30;
                }
                else
                {
                    tiempo[casilla] = 31;
                }
            }

            break;

        case HORAS:

            if (tiempo[casilla] < 0)
            {
                tiempo[casilla] = 12;
            }
            break;

        case MINUTOS:
            if (tiempo[casilla] < 0)
            {
                tiempo[casilla] = 60;
            }
            break;

        case SEGUNDOS:
            if (tiempo[casilla] < 0)
            {
                tiempo[casilla] = 60;
            }
            break;
        }
    }

    if (digitalRead(ENCODER_OK) == 1)
    {
        casilla++;
    }

    if (casilla > 6)
    {
        return true;
    }

    return false;
}

int Actualizar_MaquinaEstado(int i_encoder)

{
    int movimiento;

    switch (i_encoder)
    {
    case ESTADO_A:

        int Actualizacion_encoder = digitalRead(ENCODER_CLK) || (digitalRead(ENCODER_DT) << 1);

        if (Actualizacion_encoder == 1)
        {
            movimiento = DERECHA;
        }
        else if (Actualizacion_encoder == 2)
        {

            i_encoder = Actualizacion_encoder;
            movimiento = IZQUIERDA;
        }
        else if (Actualizacion_encoder == 0)
        {
            i_encoder = Actualizacion_encoder;
            movimiento = QUIETO;
        }
        else
        {
            exit(VALOR_ERROR);
        }

        break;

    case ESTADO_B:

        int Actualizacion_encoder = (digitalRead(ENCODER_CLK) || (digitalRead(ENCODER_DT) << 1));

        if (Actualizacion_encoder == 3)
        {

            movimiento = DERECHA;
        }
        else if (Actualizacion_encoder == 0)
        {

            i_encoder = Actualizacion_encoder;
            movimiento = IZQUIERDA;
        }
        else if (Actualizacion_encoder == 1)
        {

            i_encoder = Actualizacion_encoder;
            movimiento = QUIETO;
        }
        else
        {

            exit(VALOR_ERROR);
        }

        break;

    case ESTADO_C:

        int Actualizacion_encoder = digitalRead(ENCODER_CLK) || (digitalRead(ENCODER_DT) << 1);

        if (Actualizacion_encoder == 0)
        {

            movimiento = DERECHA;
        }
        else if (Actualizacion_encoder == 3)
        {

            i_encoder = Actualizacion_encoder;
            movimiento = IZQUIERDA;
        }
        else if (Actualizacion_encoder == 2)
        {

            i_encoder = Actualizacion_encoder;
            movimiento = QUIETO;
        }
        else
        {

            parpadear_texto("ERROR", "VALOR INVALIDO", 3000, 500);
            exit(VALOR_ERROR);
        }

        break;

    case ESTADO_D:

        int Actualizacion_encoder = digitalRead(ENCODER_CLK) || (digitalRead(ENCODER_DT) << 1);

        if (Actualizacion_encoder == 2)
        {

            movimiento = DERECHA;
        }
        else if (Actualizacion_encoder == 1)
        {

            i_encoder = Actualizacion_encoder;
            movimiento = IZQUIERDA;
        }
        else if (Actualizacion_encoder == 3)
        {

            i_encoder = Actualizacion_encoder;
            movimiento = QUIETO;
        }
        else
        {

            parpadear_texto("ERROR", "VALOR INVALIDO", 3000, 500);
            exit(VALOR_ERROR);
        }
        break;
    }
    return movimiento;
}

void imprimir_LCD(int DisplayCursor[], int tiempo[])
{
    // setea el cursor en la posicion 0-0 e imprime
    DisplayCursor[1] = 0;
    lcd.setCursor(DisplayCursor[0], DisplayCursor[1]);
    lcd.print("FECHA: "); // imprime la fecha actual
    lcd.print(tiempo[ANIOS]);
    lcd.print("/");
    lcd.print(tiempo[MESES]);
    lcd.print("/");
    lcd.print(tiempo[DIAS]);

    DisplayCursor[1] = 1;
    lcd.setCursor(DisplayCursor[0], DisplayCursor[1]);
    lcd.print("HORA: "); // imprime el tiempo actual
    lcd.print(tiempo[HORAS]);
    lcd.print("/");
    lcd.print(tiempo[MINUTOS]);
    lcd.print("/");
    lcd.print(tiempo[SEGUNDOS]);
}
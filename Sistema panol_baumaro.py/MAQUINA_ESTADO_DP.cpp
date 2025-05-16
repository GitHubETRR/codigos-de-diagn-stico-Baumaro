#include <stdio.h>
#include <arduino.h>
#include <LiquidCrystal.h>

#define VALOR_ERROR -1

#define DERECHA 1
#define QUIETO 0
#define IZQUIERDA -1

#define ENCODER_1 2
#define ENCODER_2 3

#define DISPLAY_RS 12
#define DISPLAY_ENABLE 11
#define DISPLAY_D4 5
#define DISPLAY_D5 4
#define DISPLAY_D6 3
#define DISPLAY_D7 2

#define COLUMNAS 16
#define FILAS 2

// crea el objeto lcd de tipo LiquidCrystal para representar el display 16*2

LiquidCrystal lcd(DISPLAY_RS, DISPLAY_ENABLE, DISPLAY_D4, DISPLAY_D5, DISPLAY_D6, DISPLAY_D7);

void Actualizar_MaquinaEstado(int *);

void parpadear_texto(char texto[], int tiempo);

void setup()
{

    pinmode(DISPLAY, OUTPUT);
    pinmode(ENCODER_1, INPUT);
    pinmode(ENCONDER_2, INPUT);
    lcd.begin(COLUMNAS, FILAS);
}

void loop()
{

    int *i_encoder = digitalread(ENCODER_1) || (digitalread(ENCODER_2) << 1);

    Actualizar_MaquinaEstado(i_encoder);
}

void Actualizar_MaquinaEstado(int &i_encoder)
{

    int movimiento;

    switch (*i_encoder)
    case 0:

        int Actualizacion_encoder = digitalread(ENCODER_1) || (digitalread(ENCODER_2) << 1);

    if (Actualizacion_encoder == 1)
    {

        movimiento = DERECHA;
    }
    else if (Actualizacion_encoder == 3)
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

        lcd.print("ERROR");
        lcd.setCursor(0, 1);
        lcd.print("VALOR INVALIDO");

        exit(VALOR_ERROR);
    }

    break;
case 1:

    break;
case 2:

    break;

    return movimiento;
}

void parpadear_texto(char texto[], int tiempo)
{

    while ()
    {
        /* code */
    }

    delay(tiempo);
}

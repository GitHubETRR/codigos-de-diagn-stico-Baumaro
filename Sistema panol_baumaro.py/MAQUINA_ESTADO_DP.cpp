#include <stdio.h>
#include <arduino.h>
#include <LiquidCrystal.h>

#define VALOR_ERROR -1

#define DERECHA 1
#define QUIETO 0
#define IZQUIERDA -1

#define ENCODER_1 6
#define ENCODER_2 7
#define ENCODER_OK 8

#define DISPLAY_RS 12
#define DISPLAY_ENABLE 11
#define DISPLAY_D4 5
#define DISPLAY_D5 4
#define DISPLAY_D6 3
#define DISPLAY_D7 2

#define COLUMNAS 16
#define FILAS 2

#define SEGUNDOS 6
#define MINUTOS 5
#define HORAS 4
#define DIAS 3
#define MESES 2
#define ANIOS 1

// crea el objeto lcd de tipo LiquidCrystal para representar el display 16*2

LiquidCrystal lcd(DISPLAY_RS, DISPLAY_ENABLE, DISPLAY_D4, DISPLAY_D5, DISPLAY_D6, DISPLAY_D7);

char tiempo[6] = {0,0,0,0,0,0};

int DisplayCursor[2] = {0,0};

int *i_encoder;

int movimiento;

int cant_loops = 0;

bool tiempo_seteado = false;

void Actualizar_MaquinaEstado(int *);

void parpadear_texto(char texto[], int tiempo, int tiempo_parpadeo);



void setup()
{

    pinmode(DISPLAY, OUTPUT);
    pinmode(ENCODER_1, INPUT);
    pinmode(ENCONDER_2, INPUT);
    pinmode(ENCODER_OK, INPUT);
    lcd.begin(COLUMNAS, FILAS);

}

void loop()
{

    lcd.setCursor(DisplayCursor[0], DisplayCursor[1]);

    if (cant_loops == 0)
    {
        while (tiempo_seteado)
        {
            *i_encoder = digitalread(ENCODER_1) || (digitalread(ENCODER_2) << 1);

            movimiento = Actualizar_MaquinaEstado(i_encoder);

            tiempo_seteado = definir_hora(movimiento);
        }
    }

}

void definir_hora(int movimiento){

    lcd.setCursor(DisplayCursor[0],DisplayCursor[1]);
    lcd.print("FECHA: %d:%d:%d", tiempo[ANIOS],tiempo[MESES],tiempo[DIAS]);

    DisplayCursor[1] = 1;
    lcd.setCursor(DisplayCursor[0],DisplayCursor[1]);
    lcd.print("HORA: %d:%d:%d", tiempo[HORAS],tiempo[MINUTOS],tiempo[SEGUNDOS]);

    DisplayCursor[0] = 15;
    lcd.setCursor(DisplayCursor[0],DisplayCursor[1]);

    if(ENCODER_OK == 1){

        DisplayCursor[0]--;

        if ((DisplayCursor[0] == -1) && (DisplayCursor[1] == 1))
        {
            DisplayCursor[0] = 15;
            DisplayCursor[1] = 0;
        }else if ((DisplayCursor[0] == -1) && (DisplayCursor[1] == 0))
        {
            DisplayCursor[0]++;
            return true;
        }

        lcd.setCursor(DisplayCursor[0],DisplayCursor[1]);

    }
    return false;
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

            parpadear_texto("ERROR", "VALOR INVALIDO", 3000, 500);
            exit(VALOR_ERROR);

        }

        break;
    case 1:

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

            parpadear_texto("ERROR", "VALOR INVALIDO", 3000, 500);
            exit(VALOR_ERROR);

        }

        break;

    case 2:

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

    case 3:

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

void parpadear_texto(char texto_1[], char texto_2[], int tiempo, int tiempo_parpadeo)
{
    int tiempo_actual = millis();

    while ((tiempo - tiempo_actual) <= 0)
    {
        int i++;

        

        if ((i % 2) == 0)
        {

            lcd.print(texto_1);
            lcd.setCursor(0,1);
            lcd.print(texto_2);

        }else{

            lcd.clear();

        }
        delay(tiempo_parpadeo)
    }
    
}

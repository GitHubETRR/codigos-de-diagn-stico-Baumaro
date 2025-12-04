
#include <LiquidCrystal.h>

#define FILAS 4
#define COLUMNAS 4
#define F1 2 // pin fila 1
#define F2 3 // pin fila 2
#define F3 4 // pin fila 3
#define F4 5 // pin fila 4
#define C1 6 // pin columna 1
#define C2 7 // pin columna 2
#define C3 8 // pin columna 3
#define C4 9 // pin columna 4
#define BITS_NIBBLE 4
#define TECLA_MENOS 15

// Instrucciones
#define LDA 0 // carga la direccion en el acumulador A
#define ADD 1
#define SUB 2
#define STA 3
#define NOT 4
#define CLA 5
#define JMP 6
#define JAM 7
#define JAZ 8
#define AND 9
#define IOR 10
#define XOR 11
#define DEC_ 12
#define INP 13
#define OUT 14
#define HLT 15

#define RAM 16

#define ENCODER_CLK 10
#define ENCODER_DT 11
#define ENCODER_SW 12
int contador = 0;
int ultimoEstadoCLK;

#define LCD_RS A0
#define LCD_EN A1
#define LCD_D4 A2
#define LCD_D5 A3
#define LCD_D6 A4
#define LCD_D7 A5
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

typedef union {
  struct {
    unsigned int direccion   : BITS_NIBBLE; //primeros 4 bits del byte del dato q se carga desde el teclado, representan la instruccion 
    unsigned int instruccion : BITS_NIBBLE; //segundos 4 bits del byte del dato q se carga desde el teclado, representan la direccion 
  };
  int8_t numero;
} byte_t;

class teclado(){
  private:
    byte_t dato;
    bool datoDisponible;
    bool nibbleCargado;
    bool teclaPresionada;
    int digitosDecimales;
    
  public: 
    teclado(){
      bool datoDisponible = false;
      bool nibbleCargado = false;
      bool teclaPresionada = false;
      int digitosDecimales = 0;
    }

    bool setDato(bool dato){
      datoDisponible = dato;
    }

    bool setNibble(bool dato){
      
    }

    bool setTecla(bool dato){
        
    }
    bool setDigitosDecimales(int digitosDecimales){
      
    }
}


byte_t ram[RAM]; // crea un vector de 16 espacios de tipo byte para representar la ram
int8_t a; // crea el acumulador A
int8_t b; // crea el registro B
int8_t out; // crea la variable q almacena la salida
int pc; // crea el contador de programa
bool debug = true;


bool configurar();
void verificar_teclado();
int decodificar_teclado(int fila, int columna);
bool correr();
bool verificar_tecla(int fila, int columna);
void imprimir_datos(int direccion, bool corriendo);

void setup() {
  pinMode(F1, OUTPUT);
  pinMode(F2, OUTPUT);
  pinMode(F3, OUTPUT);
  pinMode(F4, OUTPUT);
  pinMode(C1, INPUT_PULLUP);
  pinMode(C2, INPUT_PULLUP);
  pinMode(C3, INPUT_PULLUP);
  pinMode(C4, INPUT_PULLUP);

  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_SW, INPUT_PULLUP);
  ultimoEstadoCLK = digitalRead(ENCODER_CLK);

  lcd.begin(20, 4);
  lcd.clear();
}

void loop() {
  static bool ejecutando = false;
  if (ejecutando)
    ejecutando = correr();
  else
    if (configurar())
      ejecutando = true;
}

bool configurar() {
  bool iniciar = false;


  int estadoCLK = digitalRead(ENCODER_CLK);
  if (estadoCLK != ultimoEstadoCLK) {
    if (digitalRead(ENCODER_DT) != estadoCLK) {
      contador++;
    } else {
      contador--;
    }
    if (contador < 0) contador = RAM - 1;
    if (contador >= RAM) contador = 0;
    imprimir_datos(contador, false);
  }
  ultimoEstadoCLK = estadoCLK;

  verificar_teclado(); //---------------
  if (teclado.datoDisponible) {
    ram[contador].numero = teclado.dato.numero;
    imprimir_datos(contador, false);
    teclado.datoDisponible = false;
  }

  if (digitalRead(ENCODER_SW) == LOW) {
    teclado.nibbleCargado = false;
    iniciar = true;
    pc = 0;
    delay(300); // Antirrebote
  }
  return iniciar;
}

void verificar_teclado() {
  bool teclaPresionada = false;

  // recorre la matriz 4x4 del teclado 
  for (int fila = F1; fila <= F4; fila++) {
    digitalWrite(fila, LOW);
    for (int columna = C1; columna <= C4; columna++) {
      if (!digitalRead(columna)) {
        if (!teclado.teclaPresionada) {
          if (teclado.nibbleCargado) {
            teclado.dato.direccion = decodificar_teclado(fila, columna);
            teclado.nibbleCargado = false;
            teclado.datoDisponible = true;
          } else {
            teclado.dato.instruccion = decodificar_teclado(fila, columna);
            teclado.nibbleCargado = true;
          }
        }
        teclado.teclaPresionada = true;
        teclaPresionada = true;
      }
    }
    digitalWrite(fila, HIGH);
  }
  if (!teclaPresionada)
    teclado.teclaPresionada = false;
}

int decodificar_teclado(int fila, int columna) {
  fila -= F1;
  columna -= C1;
  const int valoresTeclado[FILAS][COLUMNAS] = {
    {1, 2, 3, 10},
    {4, 5, 6, 11},
    {7, 8, 9, 12},
    {14, 0, 15, 13}
  };
  return valoresTeclado[fila][columna];
}

bool correr() {
  bool continuar = true;
  int direccion = pc;
  if (debug) {
    imprimir_datos(direccion, true);
    while (digitalRead(ENCODER_SW) == LOW) {}
  }
  byte_t instruccion = ram[pc];
  pc++;
  if (pc == RAM) pc = 0;

  switch (instruccion.instruccion) {
    case LDA: a = ram[instruccion.direccion & 0x0F].numero; break;
    case ADD: b = ram[instruccion.direccion & 0x0F].numero; a += b; break;
    case SUB: b = ram[instruccion.direccion & 0x0F].numero; a -= b; break;
    case STA: ram[instruccion.direccion & 0x0F].numero = a; break;
    case NOT: a = ~ram[instruccion.direccion & 0x0F].numero; break;
    case CLA: a = 0; break;
    case JMP: pc = instruccion.direccion; break;
    case JAM: if (a < 0) pc = instruccion.direccion; break;
    case JAZ: if (a == 0) pc = instruccion.direccion; break;
    case AND: b = ram[instruccion.direccion & 0x0F].numero; a &= b; break;
    case IOR: b = ram[instruccion.direccion & 0x0F].numero; a |= b; break;
    case XOR: b = ram[instruccion.direccion & 0x0F].numero; a ^= b; break;
    case DEC_: a--; break;
    case OUT: out = a; break;
    case HLT: continuar = false; break;
  }
  if (verificar_tecla(3, 3)) debug = !debug;
  if (debug) while (digitalRead(ENCODER_SW) == HIGH) {}
  imprimir_datos(direccion, true);
  return continuar;
}

bool verificar_tecla(int fila, int columna) {
  bool teclaPresionada;
  for (int f = F1; f <= F4; f++) {
    digitalWrite(f, (f - F1) == fila ? LOW : HIGH);
  }
  teclaPresionada = !digitalRead(columna + C1);
  digitalWrite(F1, HIGH);
  digitalWrite(F2, HIGH);
  digitalWrite(F3, HIGH);
  digitalWrite(F4, HIGH);
  return teclaPresionada;
}


void imprimir_datos(int direccion, bool corriendo) {
  byte_t dato = ram[direccion];
  const String nombresInstrucciones[] = {"LDA", "ADD", "SUB", "STA", "NOT", "CLA", "JMP", "JAM", "JAZ", "AND", "IOR", "XOR", "DEC", "INP", "OUT", "HLT"};
  const bool usanDireccion[] = {true, true, true, true, true, false, true, true, true, true, true, true, false, false, false, false};
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(direccion, HEX);
  lcd.print("h: ");
  lcd.print(nombresInstrucciones[dato.instruccion]);
  if (usanDireccion[dato.instruccion]) {
    lcd.setCursor(8, 0);
    lcd.print(dato.direccion, HEX);
    lcd.print("h");
  }
  lcd.setCursor(0, 1);
  lcd.print("A: ");
  lcd.print(a);
  lcd.setCursor(10, 1);
  lcd.print("B: ");
  lcd.print(b);
  lcd.setCursor(10, 4);
  lcd.print("OUT: ");
  lcd.print(out);
  if (corriendo) {
    lcd.setCursor(15, 0);
    lcd.print("|");
    for (int i = 0; i < teclado.digitosDecimales; i++) lcd.print(" ");
    lcd.print(".");
    lcd.setCursor(3, 0);
    lcd.print("PC: ");
    lcd.print(pc, HEX);
    lcd.setCursor(4, 0);
    lcd.print("IN: ");
    lcd.print(teclado.dato.numero);
  } else {
    lcd.setCursor(17, 0);
    lcd.print("|");
    lcd.print(teclado.nibbleCargado ? " ." : ". ");
    lcd.setCursor(4, 0);
    lcd.print("n: ");
    lcd.print(dato.numero);
  }
}

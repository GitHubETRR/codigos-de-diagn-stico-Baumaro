import pandas as pd
from machine import Pin, ADC, UART
from ili9341 import ILI9341, color565
from xglcd_font import XglcdFont
import time

class Teletrimetria:
    def __init__(self):
        self.raspberry_pico = RaspberryPiPico()
        self.DatosCinematica = pd.DataFrame(columns=['tiempo', 'distancia','velocidad'])
        self.DatosBateria = pd.DataFrame(columns=['corriente', 'voltaje', 'Porcentaje'])
        self.patalla = Pantalla(self, raspberry_pico)
        self.RadioFrecuencia = Modulo_RF()
        self.PerimetroRueda = 0.5 / 3.14 # donde 0.5m es el perimetro y 3.14 es pi 
    
    def calcularPorcentajeBateria(self, corriente, voltaje, PotenciaEfectivaMin):
        pass

    def convertirMagneticoDistancia(self, magnetico):
        if magnetico < 2.6 or magnetico > 2.4:
            distancia = self.PerimetroRuedaerimetro
        return distancia
        
    def CalcularVelocidad(self, distancia, tiempo):
        DeltaT = tiempo - (self.DatosCinematica.loc[-1]['tiempo'] if not self.DatosCinematica.empty else 0)
        DeltaX = distancia - (self.DatosCinematica.loc[-1]['distancia'] if not self.DatosCinematica.empty else 0)
        VelocidadProm = DeltaT / DeltaX if DeltaX != 0 else 0
        return VelocidadProm

    def ActualizarDatosCinematica(self):
        magnetico = self.raspberry_pico.leerMagnetico()
        distancia = self.convertirMagneticoDistancia(magnetico, "falta poner perimetro", self.Datos.loc[-1]['distancia'] if not self.Datos.empty else 0)
        tiempo = time.ticks_ms()
        VelocidadProm = self.CalcularVelocidad(distancia, tiempo)
        LineaDatosCinematica = [tiempo, distancia, VelocidadProm]
        return LineaDatosCinematica
    
    def ActualizarDatosBateria(self):
        corriente = self.raspberry_pico.leerCorriente()
        voltaje = self.raspberry_pico.leerVoltaje()
        LineaDatosBateria = [corriente, voltaje]
        return LineaDatosBateria
        
    def agregarDatos(self, lineaDatosCinematica, LineaDatosBateria):
        self.DatosCinematica.loc[len(self.DatosCinematica)] = lineaDatosCinematica
        self.DatosBateria.loc[len(self.DatosBateria)] = LineaDatosBateria

class RaspberryPiPico():
    def __init__(self):

        self.rst = Pin(6, Pin.OUT) # Reset pin for TFT
        self.dc = Pin(7, Pin.OUT)   # data/command pin for TFT
        self.cs = Pin(2, Pin.OUT)  # Chip Select

        self.sensorCorriente = ADC(Pin(31, Pin.IN)) #define el pin del sensor de corriente analogico 
        self.sensorVoltaje = ADC(Pin(32, Pin.IN)) #define el pin del sensor de voltaje
        self.sensorMagnetico = ADC(Pin(34, Pin.IN)) #define el pin del sensor magnetico
        self.tiempo = time.ticks_ms() #obtiene el tiempo actual en milisegundos
    
    def leerCorriente(self):
        valor = self.sensorCorriente.read_u16() # Lee el valor del ADC del sensor de corriente
        corriente = (valor * 20 / 65535) # Convierte el valor ADC en amperios, usando regla de tres simple 20A = 65535 valor ADC
        return corriente

    def leerVoltaje(self):
        valor = self.sensorVoltaje.read_u16() # Lee el valor del ADC del sensor de voltaje
        voltaje = (valor * 48 / 65535) # Convierte el valor ADC en voltios, usando regla de tres simple 48V = 65535 valor ADC
        return voltaje
    
    def leerMagnetico(self):
        valor = self.sensorMagnetico.read_u16() # Lee el valor del ADC del sensor magnetico
        magnetico = (valor * 2.5 / 32767) # Convierte el valor ADC en voltaje, usando regla de tres simple 2.5V = 32767 valor ADC. 2.5V es la salida cuando el sensor no detecta nada
        return magnetico

class Pantalla:
    def __init__(self, raspberry_pico):
        self.spi = SPI(
            0,                      # Número de bus SPI (0 o 1)
            baudrate=40000000,      # Velocidad de comunicación (opcional, por defecto suele ser 1 MHz)
            polarity=0,             # Polaridad del reloj (0 o 1)
            phase=0,                # Fase del reloj (0 o 1)
            sck=Pin(4),             # Pin del reloj SCK
            mosi=Pin(5),            # Pin de datos MOSI
        )
        self.font = XglcdFont(CADENA, ANCHO, ALTO) #fuente , ANCHO X ALTO
        self.display = ILI9341(
            self.spi, 
            dc=raspberry_pico.dc,
            cs=raspberry_pico.cs,
            rst=raspberry_pico.rst,
            rotation=0
        )
        
        def imprimirDatos(self, DatosBateria, DatosCinematica):

            self.display.text(10,10,f"VELOCIDAD: {DatosCinematica.loc[-1, 'velocidad']}", self.font,color565(0,0,0))
            self.display.text(f"CORRIENTE: {DatosBateria[-1, 'corriente']}   VOLTAJE: {DatosBateria[-1,'voltaje']}   PORCENTAJE: {DatosBateria[-1, 'porcentaje']}%")

class Modulo_RF():
    self.Comunicacion = UART(0, baudrate=9600, tx=Pin(29)) # ID, velocidad de transmicion, y pin de datos

    def transmitir(self, dato):
        self.Comunicacion.write(dato)

def main():

    Sistema = Teletrimetria() #crea el sistema de teletrimetria 
    Sistema.patalla.init() # inicializa la pantalla
    while()

if "__main__" == __name__:
    main()


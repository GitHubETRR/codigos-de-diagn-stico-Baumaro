#include <SPI.h>
#include <LoRa.h>

#define LORA_NSS 10 
#define LORA_RST 2
#define LORA_DIO0 9
#define BRAUDRATE 9600

void WriteDataToPC(string mensaje);

void setup(){
    Serial.begin(BRAUDRATE);
    LoRa.setPins(LORA_NSS, LORA_RST, LORA_DIO0); 
    LoRa.begin(915E6);
    
}

void loop() {
    int packetSize = LoRa.parsePacket(); //devuelve el tamanio del paquete recibido 

    if (packetSize > 0) //todo lo que hay en este if recibe el msg y lo reconstruye 
    {
        while (LoRa.available()) //hace un bucle de la cantidad de bytes que faltan leer del paquete 
        {
            string mensaje += LoRa.read(); // linea de datos
        }
        mensaje += \n;
        
        WriteDataToPC(mensaje); // escribe el mensaje en el buffer de la PC
    }
}

void WriteDataToPC(string mensaje){
    Serial.println(mensaje);
}
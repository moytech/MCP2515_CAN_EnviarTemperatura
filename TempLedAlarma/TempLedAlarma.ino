/*

Temperatura led alarma

Practicas CAN con módulo MCP2515  https://github.com/moytech

Este programa recibe la temperatura del sensor LM35. Se muestra en el Serial monitor.
Se recibe por el protocolo CAN bus con ayuda del módulo MCP2515 y se condiciona para 
encender un led simulando una alarma.

Autor: Moytech
github: https://github.com/moytech
Programa: Temperatura led alarma
Fecha: Julio 2024

*/

#include <SPI.h>
#include <mcp2515.h>

#define CS 10
int temprec;
int led= 2;                                       //led in pin 2
int tempmax= 30;                                  //temperatura máxima

struct can_frame datareceive;
MCP2515 mcp2515(CS);

void setup() 
{
  Serial.begin(9600);                             //iniciar serial monitor
  SPI.begin();                                    //iniciar SPI
  mcp2515.reset();                                //reset MCP2515
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);      //configuración CAN bus
  mcp2515.setNormalMode();                        //normal mode
  pinMode(led, OUTPUT);                           //led como salida
  digitalWrite(led, 0);                           //led en 0
}

void loop() 
{
  if(mcp2515.readMessage(&datareceive)== MCP2515::ERROR_OK)
  {
    Serial.println("Temperatura recibida: ");     //imprimir en serial monitor
    temprec= datareceive.data[0];                 //temperatura
    if(temprec> tempmax)                          //condición
    {
      digitalWrite(led, 1);                       //led en 1
      Serial.println(datareceive.data[0]);        //imprimir en serial monitor
      Serial.println("Led encendido");            //imprimir en serial monitor
    }
    else
    {
      digitalWrite(led, 0);                       //led en 0
      Serial.println(datareceive.data[0]);        //imprimir en serial monitor
      Serial.println("Led apagado");              //imprimir en serial monitor
    }
  }
}

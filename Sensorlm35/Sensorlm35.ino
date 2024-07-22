/*

Temperatura lm35

Practicas CAN con módulo MCP2515  https://github.com/moytech

Este programa envía la temperatura de un sensor LM35. Se muestra en el Serial monitor.
Se envía por el protocolo CAN bus con ayuda del módulo MCP2515 y otro 
módulo MCP2515 recibe la tempertura y se condiciona para encender un 
led simulando una alarma.

Autor: Moytech
github: https://github.com/moytech
Programa: Temperatura lm35
Fecha: Julio 2024

*/

#include <SPI.h>
#include <mcp2515.h>

#define CS 10
int sensor= A0;
int val= 0;
float temp;

struct can_frame datasend;
MCP2515 mcp2515(CS);                                  

void setup() 
{
  Serial.begin(9600);                                 //iniciar serial monitor
  SPI.begin();                                        //iniciar SPI
  mcp2515.reset();                                    //reset MCP2515
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);          //configuración CAN bus
  mcp2515.setNormalMode();                            //modo normal
}

void loop() 
{
  val= analogRead(sensor);                            //leer sensor
  temp= ((val* 5000.0)/ 1024.0);                      //conversión a mV
  temp= (temp/ 10.0);                                 //conversión a celsius
  datasend.can_id= 0x11;                              //CAN id
  datasend.can_dlc= 4;                                //4 bytes
  datasend.data[0]= (int) temp;                       //temperatura en byte[0]
  datasend.data[1]= 0x00;                             //byte[1]
  datasend.data[2]= 0x00;                             //byte[2]
  datasend.data[3]= 0x00;                             //byte[3]

  mcp2515.sendMessage(&datasend);                     //Enviar datos
  Serial.println("Temperatura enviada: ");            //imprimir en serial monitor
  Serial.println(datasend.data[0]);                   //imprimir en serial monitor
  delay(3000);                                        //esperar 3 seg.
}

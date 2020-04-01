#include <Arduino.h>

int RS = 12;  //pin del semaforo en rojo

int NS = 11;  //pin del semaforo en naranja

int VS = 10;   //pin del semaforo en verde

int RP = 4;  //pin del semaforo de PEATONES en rojo

int VP = 3;  //pin del semaforo de PEATONES en verde

int boton = 7;  //pin del botón de peatones

int conta = 0;  //Variable para guardar el conteo de los pulsos

int tiempoVS = 80000; //Variable para tiempo del VS encendido
unsigned long TiempoCambio = 0; //variable para guardar el tiempo de finalización
//de cada ciclo entre cada vez que se enciende el VS

void setup()
{

  pinMode(RS, OUTPUT); //se define como salida
  pinMode(NS, OUTPUT); //se define como salida
  pinMode(VS, OUTPUT); //se define como salida
  pinMode(RP, OUTPUT); //se define como salida
  pinMode(VP, OUTPUT); //se define como salida

  pinMode(boton, INPUT); //se define como entrada

  digitalWrite(VS, HIGH);  //condición inicial
  digitalWrite(RP, HIGH);  //condición inicial

}

void loop()
{
  digitalWrite(RS, LOW); //verde semaforo apagado fijo 80 segundos
  digitalWrite(VS, HIGH); //verde semaforo encendido fijo 80 segundos

  int milisRestantes = tiempoVS;//definir cuantos milisegundos quedan de la luz en verde del semaforo
  int valorBoton = 0;
  int estadoAnteriorBoton = 0;
  int pulsaciones = 0;//variable inicial de pulsaciones

  while (pulsaciones < 6 || millis() - TiempoCambio <= tiempoVS) { //Mientras no se haya presionado el boton 6 veces o mientras
                                                                   //no hayan pasado 80 segundos

    int valorBoton = digitalRead(boton); //Leemos el estado del boton

    if (valorBoton != estadoAnteriorBoton) { //Si el estado del boton es diferente al estado anterior del boton (este se presiono o se solto)
      if (valorBoton == 1) { //Si el valor del boton es 1 (si esta presionado)
        pulsaciones++;
      }
    }
    estadoAnteriorBoton = valorBoton; //Guardamos el estado actual del pulsador para la siguiente iteracion
    if (pulsaciones >= 6 || millis() - TiempoCambio >= tiempoVS) {
      break;
    }
  }

  for (int x = 0; x < 6; x++) { //verde semaforo encendido titilando on invalos de un segundo durante 10 segundos
    digitalWrite(VS, HIGH);
    delay(1000);
    digitalWrite(VS, LOW);
    delay(1000);
  }

  digitalWrite(VS, LOW); //se apaga el verde y pasa Naranja del semaforo encendido fijo 5 segundos
  digitalWrite(NS, HIGH);
  delay(5000);

  digitalWrite(NS, LOW); //Se apaga el naranja y se enciende el rojo del semaforo durante 15 segundos
  digitalWrite(RS, HIGH);
  digitalWrite(RP, LOW); //Se apaga el rojo peatonal y se enciende el verde peatonal durante 15 segundos
  digitalWrite(VP, HIGH);
  delay(15000);

  for (int x = 0; x < 6; x++) { //el verde del peatonal titila los últimos 5 segundos 5 veces antes de pasar a rojo
    digitalWrite(VP, HIGH);
    delay(500);
    digitalWrite(VP, LOW);
    delay(500);
  }

  digitalWrite(RP, HIGH);  //Se enciende el rojo peatonal
  digitalWrite(VP, LOW);   //Se apaga el verde peatonal
  delay(2000);

  TiempoCambio = millis(); //Guardar tiempo de cambio para aceptar pulsaion del boton

}
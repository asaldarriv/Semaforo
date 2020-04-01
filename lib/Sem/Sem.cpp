#include "Sem.h"
#include <Arduino.h>
uint8_t valorBoton = 0; //Valor del boton inicializado en 0
uint8_t estadoAnteriorBoton = 0; //Valor del estado anterior inicializado en 0
uint8_t contador = -1; //Contador de pulsaciones inicializado en -1
uint8_t wink_contador = 0; //Contador de cambios entre encendido/apagado de algun led

Sem::Sem(uint8_t v_rojo, uint8_t v_nja, uint8_t v_vde, uint8_t p_rojo, uint8_t p_vde, uint8_t boton)
{
  _boton = boton;

  //Se definen como salida los LEDs y como entrada el boton
  pinMode(v_rojo, OUTPUT);
  pinMode(v_nja, OUTPUT);
  pinMode(v_vde, OUTPUT);
  pinMode(p_rojo, OUTPUT);
  pinMode(p_vde, OUTPUT);

  pinMode(_boton, INPUT);

  //Condiciones iniciales (semaforo vehicular en verde y peatonal en rojo que corresponden a S1)
  digitalWrite(v_vde, 1);
  digitalWrite(p_rojo, 1);
  digitalWrite(v_nja, 0);
  digitalWrite(v_rojo, 0);
  digitalWrite(p_vde, 0);

}

uint8_t Sem::pulsaciones(uint8_t limite_pulsaciones)
{ //Contador de pulsaciones de un boton sin bloqueos
  if (contador  == limite_pulsaciones)
  { //Condicion para reiniciar el contador cuando este llega al limite de pulsaciones
    contador = 0;
  }
  uint8_t valorBoton = digitalRead(_boton); //Leemos el estado del boton

  if (valorBoton != estadoAnteriorBoton)
  { //Si el estado del boton es diferente al estado anterior del boton (este se presiono o se solto)
    if (valorBoton == 1)
    { //Si el valor del boton es 1 (si esta presionado)
      contador++;
    }
  }
  estadoAnteriorBoton = valorBoton; //Guardamos el estado actual del pulsador para la siguiente iteracion
  return contador; //Devolvemos la cantidad de pulsaciones

}

uint8_t Sem::contar_intermitencia(uint8_t pin, uint16_t tiempo_de_cambio, uint8_t intermitencias)
{ //Funcion para hacer que un led realice cambios entre encendido/apagado una cantidad "intermitencias" de veces
  //cada "tiempo_de_cambio" milisegundos
  if (wink_contador == intermitencias) {
    wink_contador = 0;
    static uint32_t wink_reloj = millis();
  }
  static uint32_t wink_reloj = 0;
  if (millis() - wink_reloj >= tiempo_de_cambio)
  { //Enciende y apaga el led cada segundo
    digitalWrite(pin, !digitalRead(pin));
    wink_reloj = millis();
    wink_contador++; //Cada que se encience o apaga, aumentamos el contador del destello

  }
  return wink_contador;

}

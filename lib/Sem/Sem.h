/*La siguiente libreria permite modificar el funcionamiento de un semaforo que contiene 1 pulsador
  y 5 leds: uno verde vehicular,uno naranja vehicular, uno rojo vehicular, uno verde peatonal y uno rojo
  peatonal. Estas modificaciones al semaforo son posibles gracias a 2 funciones implementadas en esta
  librería las cuales son: una para contar la cantidad de pulsaciones de un boton y la otra otra para hacer que un led
  especifico se encienda y apague intermitentenemte cada cierto tiempo (y que nos cuenta cuantas veces cambio
  de estado el led). De esta manera, usted solo tendra que definir cuales pines corresponden a cada uno de los 5
  leds y cual pin corresponde al boton. Tambien, debera crear las siguientes variables para hacer funcionar
  el codigo del semaforo: un contador de pulsaciones del boton, un tiempo relativo para poder espeficiar durante
  cuanto tiempo se permanece en un estado, un contador de cambios entre encendido/apagado para algun led que
  debe estar en un estado "titilando", un tiempo relativo para saber cada cuanto tiempo cambia el estado del led
  de encendido/apagado para un led que debe estar en un estado "titilando" y una variable que indique el estado
  en el que se encuentra el semaforo.*/

#ifndef Sem_h
#define Sem_h

#include "arduino.h"

class Sem
{
  private:
    uint8_t _v_rojo; //Led rojo vehiculos
    uint8_t _v_nja;  //Led naranja vehiculos
    uint8_t _v_vde;  //Led verde vehiculos

    uint8_t _p_rojo; //Led rojo peatoes
    uint8_t _p_vde;  //Led verde peatones

    uint8_t _boton; //Boton de peatones

    uint8_t _valorBoton;          //Estado del boton
    uint8_t _estadoAnteriorBoton; //Estado anterior del boton
    uint32_t _wink_reloj;         //Reloj relativo para el estado "led verde titilando"
  public:
    Sem(uint8_t v_rojo, uint8_t v_nja, uint8_t v_vde, uint8_t p_rojo, uint8_t p_vde, uint8_t boton); //Los parametros de entrada son (en orden):
    //led vehicular rojo, led vehicular naranja, led vehicular verde, led peatonal rojo, led peatonal verde y boton
    uint8_t pulsaciones(uint8_t limite_pulsaciones); //El parametro de entrada es la cantidad de pulsaciones que se deben
    //hacer para cambiar del estado S1 al estado S2
    uint8_t contar_intermitencia(uint8_t pin, uint16_t tiempo_de_cambio, uint8_t intermitencias); //Los parametros de entrada son (en orden):
    //el pin que se desea hacer titilar, el tiempo (en milisegundos) ente cada cambio de encendido/apagado y la 
    //cantidad de cambios entre encendido/apagado.
};

#endif

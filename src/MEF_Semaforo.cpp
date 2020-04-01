#include <Sem.h>
#include <Arduino.h>

//Definicion de pines
uint8_t v_rojo = 12; //Led rojo vehiculos
uint8_t v_nja = 11;  //Led naranja vehiculos
uint8_t v_vde = 10;  //Led verde vehiculos

uint8_t p_rojo = 4; //Led rojo peatoes
uint8_t p_vde = 3;  //Led verde peatones

uint8_t boton = 7; //Boton de peatones

Sem sem(v_rojo, v_nja, v_vde, p_rojo, p_vde, boton); //Llamamos a la libreria "sem" y le damos los correspondientes parametros de entrada

uint8_t cont = 0;            //Contador de pulsaciones del boton
static uint8_t estado = 0;        //Estado del diagrama en el que se encuentra el semaforo
static uint32_t reloj = 0;        //Reloj relativo para poder hacer diferencias de tiempo
static uint8_t contador_wink = 0; //Contador de cambios de estado entre encendido/apagado de un led determinado


void setup()
{

}

void loop()
{
  switch (estado)
  {

    case 0:          //Estado S1 (estado inicial): vehicular en verde y peatonal en rojo
      cont = sem.pulsaciones(6); //Llamamos constantemente a la funcion pulsaciones() para poder verificar la etiqueta n
      if (millis() - reloj >= 80000)
      { //Etiqueta b
        estado = 1;
      }
      if (cont >= 6)
      { //Etiqueta n
        estado = 1;
        reloj = millis() - 80000; //Ajuste para que millis()-reloj sea 80s justo cuando se entra en el estado S2
      }
      break;

    case 1: //Estado S2: led verde vehicular titilando
      contador_wink = sem.contar_intermitencia(v_vde, 1000, 11); //Los parametros 1000 y 11 indican 5 destellos en 10 segundos
      if (contador_wink >= 11)
      { //Si el led se enciende 5 veces, se pasa al estado S3 (esto se puede considerar como la etiqueta d)
        estado = 2;
        contador_wink = 0;
      }
      break;
    case 2:                   //Estado S3
      digitalWrite(v_vde, 0); //Acciones tomadas en la etiqueta d (encender
      digitalWrite(v_nja, 1); //el led naranja y apagar el verde del vehicular)
      if (millis() - reloj >= 95000)
      { //Etiqueta f
        estado = 3;
        reloj = millis();
      }
      break;
    case 3: //Estado S4
      digitalWrite(v_nja, 0);
      digitalWrite(v_rojo, 1);
      digitalWrite(p_vde, 1);
      digitalWrite(p_rojo, 0);
      if (millis() - reloj >= 15000)
      { //Etiqueta h
        estado = 4;
        reloj = millis();
      }
      break;
    case 4: //Estado S5: led verde peatonal titilando
      contador_wink = sem.contar_intermitencia(p_vde, 500, 11); //Los parametros 500 y 11 indican 5 destellos en 5 segundos
      if (contador_wink >= 11)
      { //Si el led se enciende 5 veces, se pasa al estado S6 (esto se puede considerar como la etiqueta j)
        estado = 5;
        contador_wink = 0;
        reloj = millis();
      }
      break;
    case 5: //Estado S6
      digitalWrite(p_vde, 0);
      digitalWrite(p_rojo, 1);
      if (millis() - reloj >= 2000)
      { //Etiqueta l (a continuacion se restablecen todas
        estado = 0;       //las variables para evitar errores
        reloj = millis(); //ya que se vuelve al estado inicial)
        digitalWrite(v_vde, 1);
        digitalWrite(v_rojo, 0);
        cont = 0;
        contador_wink = 0;
      }
      break;
  }
}

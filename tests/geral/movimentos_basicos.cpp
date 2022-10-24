#include "movimentos_basicos.h"
#include <Arduino.h>

// ESC1 = ESC da direita
// ESC2 = ESC da esquerda
// ESC = ESC qualquer

void Tera::movimento::inverter_motor(Servo & ESC)
{
  ESC.writeMicroseconds(aceleracao::re);
  delay(50);
  ESC.writeMicroseconds(aceleracao::nula);
  delay(50);
  ESC.writeMicroseconds(aceleracao::re);

  #ifdef _DEBUG_MOVIMENTOS_
  Serial.println("Invertendo motor");
  #endif
}

void Tera::movimento::recuar(Servo & ESC1, Servo & ESC2)
{
  ESC1.writeMicroseconds(aceleracao::re);
  ESC2.writeMicroseconds(aceleracao::re);
  delay(50);
  ESC1.writeMicroseconds(aceleracao::nula);
  ESC2.writeMicroseconds(aceleracao::nula);
  delay(50);
  ESC1.writeMicroseconds(aceleracao::re);
  ESC2.writeMicroseconds(aceleracao::re);

  #ifdef _DEBUG_MOVIMENTOS_
  Serial.println("Recuar");
  #endif
}

void Tera::movimento::avanco(Servo & ESC1, Servo & ESC2)
{
  ESC1.writeMicroseconds(aceleracao::maxima);
  ESC2.writeMicroseconds(aceleracao::maxima);

  #ifdef _DEBUG_MOVIMENTOS_
  Serial.println("Avanço");
  #endif
}

void Tera::movimento::parar(Servo & ESC1, Servo & ESC2)
{
  ESC1.writeMicroseconds(aceleracao::nula);
  ESC2.writeMicroseconds(aceleracao::nula);

  #ifdef _DEBUG_MOVIMENTOS_
  Serial.println("Parando");
  #endif
}

void Tera::movimento::girar_esquerda(Servo & ESC1, Servo & ESC2)
{
  ESC1.writeMicroseconds(aceleracao::maxima);
  inverter_motor(ESC2);

  #ifdef _DEBUG_MOVIMENTOS_
  Serial.println("Girando para esquerda");
  #endif
}

void Tera::movimento::girar_direita(Servo & ESC1, Servo & ESC2)
{
  inverter_motor(ESC1);
  ESC2.writeMicroseconds(aceleracao::maxima);
  
  #ifdef _DEBUG_MOVIMENTOS_
  Serial.println("Girando para direita");
  #endif
}

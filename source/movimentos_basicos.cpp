#include "movimentos_basicos.hpp"
#include <Arduino.h>
// #define _DEBUG_MOVIMENTOS_ // Enquanto essa linha não for um comentário, movimentos do robô serão mostrados no monitor serial

// ESC1 = ESC da esquerda
// ESC2 = ESC da direita
// ESC = ESC qualquer

extern const int tempo_intervalo; // ms
extern const int tempo_movimento; // ms

void Tera::movimento::inverter_motor(Servo &ESC)
{
  ESC.writeMicroseconds(aceleracao::re);
  delay(tempo_intervalo);
  ESC.writeMicroseconds(aceleracao::nula);
  delay(tempo_intervalo);
  ESC.writeMicroseconds(aceleracao::re);

#ifdef _DEBUG_MOVIMENTOS_
  Serial.println("Invertendo motor");
#endif
}

void Tera::movimento::recuar(Servo &ESC1, Servo &ESC2)
{
  ESC1.writeMicroseconds(aceleracao::re);
  ESC2.writeMicroseconds(aceleracao::re);
  delay(tempo_intervalo);
  ESC1.writeMicroseconds(aceleracao::nula);
  ESC2.writeMicroseconds(aceleracao::nula);
  delay(tempo_intervalo);
  ESC1.writeMicroseconds(aceleracao::re);
  ESC2.writeMicroseconds(aceleracao::re);

#ifdef _DEBUG_MOVIMENTOS_
  Serial.println("Recuar");
#endif
}

void Tera::movimento::avanco(Servo &ESC1, Servo &ESC2)
{
  ESC1.writeMicroseconds(aceleracao::maxima);
  ESC2.writeMicroseconds(aceleracao::maxima);

#ifdef _DEBUG_MOVIMENTOS_
  Serial.println("Avanço");
#endif
}

void Tera::movimento::parar(Servo &ESC1, Servo &ESC2)
{
  ESC1.writeMicroseconds(aceleracao::nula);
  ESC2.writeMicroseconds(aceleracao::nula);

#ifdef _DEBUG_MOVIMENTOS_
  Serial.println("Parando");
#endif
}

void Tera::movimento::girar_esquerda(Servo &ESC1, Servo &ESC2)
{
  ESC2.writeMicroseconds(aceleracao::maxima);
  inverter_motor(ESC1);

#ifdef _DEBUG_MOVIMENTOS_
  Serial.println("Girando para esquerda");
#endif
}

void Tera::movimento::girar_direita(Servo &ESC1, Servo &ESC2)
{
  inverter_motor(ESC2);
  ESC1.writeMicroseconds(aceleracao::maxima);

#ifdef _DEBUG_MOVIMENTOS_
  Serial.println("Girando para direita");
#endif
}

void Tera::movimento::especial(Servo &ESC1, Servo &ESC2)
{
  avanco(ESC1, ESC2);
  delay(tempo_intervalo);
  girar_direita(ESC1, ESC2);
  delay(tempo_intervalo);
  girar_direita(ESC1, ESC2);
  delay(tempo_intervalo);
  girar_esquerda(ESC1, ESC2);
  delay(tempo_intervalo);
  girar_esquerda(ESC1, ESC2);
  delay(tempo_intervalo);

#ifdef _DEBUG_MOVIMENTOS_
  Serial.println("Especial");
#endif
}

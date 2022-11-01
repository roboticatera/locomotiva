#include "movimentos_basicos.h"
using namespace Tera::movimento;


short pino_ESC_esquerdo{A1};
short pino_ESC_direito{A2};
Servo ESC_esquerdo;
Servo ESC_direito;


void setup()
{
    delay(1000);
    ESC_esquerdo.attach(pino_ESC_esquerdo);
    ESC_direito.attach(pino_ESC_direito);
    delay(3000);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN,LOW);
    //Serial.begin(9600);
    ESC_esquerdo.writeMicroseconds(aceleracao::nula);
    ESC_direito.writeMicroseconds(aceleracao::nula);
    //ESC_esquerdo.writeMicroseconds(aceleracao::maxima);
    //ESC_direito.writeMicroseconds(aceleracao::maxima);
}

void loop()
{
    //Serial.println("CL");
    ESC_esquerdo.writeMicroseconds(aceleracao::re);
    ESC_direito.writeMicroseconds(aceleracao::re);
    delay(1000);

    //versão inline da função recuar por que por algum motivo não ela não estava executando
    //ESC_esquerdo.writeMicroseconds(aceleracao::nula);
    //ESC_direito.writeMicroseconds(aceleracao::nula);
    //delay(100);
    //ESC_esquerdo.writeMicroseconds(aceleracao::re);
    //ESC_direito.writeMicroseconds(aceleracao::re);
    //delay(100);
    //ESC_esquerdo.writeMicroseconds(aceleracao::nula);
    //ESC_direito.writeMicroseconds(aceleracao::nula);
    //delay(100);
    //ESC_esquerdo.writeMicroseconds(aceleracao::re);
    //ESC_direito.writeMicroseconds(aceleracao::re);
    //delay(10000);
}

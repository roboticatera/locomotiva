#include <Servo.h>
#include "comandos_movimento.h"
#include <Ultrasonic.h>



short pino_ir_1{2};
short pino_ir_2{3};
short pino_ir_3{4};
short pino_ir_4{12};
short pino_ESC{11};

using namespace Tera::movimento;
Ultrasonic ultra_direita(5,6);//Ultrasonic ultra1(trig,echo);
Ultrasonic ultra_meio(7,8);
Ultrasonic ultra_esquerda(9,10);
Servo ESC;

void ataque()
{
    ESC.writeMicroseconds(aceleracao::maxima);//move com toda força pra frente
    Serial.println("Attack");
}

void parar()
{
    ESC.writeMicroseconds(aceleracao::nula);//para o movimento do motor
    Serial.println("Parar");
}


void setup()
{
    Serial.begin(115200);
    ESC.attach(11);
    pinMode(pino_ir_1, INPUT);
    pinMode(pino_ir_2, INPUT);
    pinMode(pino_ir_3, INPUT);
    pinMode(pino_ir_4, INPUT);
}

int dist_meio{};

void loop()
{
    dist_meio = ultra_meio.read();
    Serial.print("dist_meio = ");
    Serial.println(dist_meio);
    // delay(2000);
    if(dist_meio != 0 && dist_meio < 70)
    {
        attack();
    }
    else
    {
        parar();
        
    }


}

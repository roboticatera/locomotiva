#include <Servo.h>
#include "comandos_movimento.h"
#include <Ultrasonic.h>



short pino_iv_1{2};
short pino_iv_2{3};
short pino_iv_3{4};
short pino_iv_4{12};
short pino_ESC{11};

int dist_meio{};
int dist_esquerda{};
int dist_direita{};
bool na_linha{false};

using namespace Tera::movimento;
Ultrasonic ultra_direita(5,6);//Ultrasonic ultra1(trig,echo);
Ultrasonic ultra_meio(7,8);
Ultrasonic ultra_esquerda(9,10);
// Servo ESC;
//Servo ESC2; // ESC do motor 2

void ataque()
{
    // ESC.writeMicroseconds(aceleracao::maxima);//move com toda força pra frente
    // Serial.println("Attack");
    Serial.println("ataque: Motores indo pra frente");
}

void parar()
{
    // ESC.writeMicroseconds(aceleracao::nula);//para o movimento do motor
    // Serial.println("Parar");
    Serial.println("parar: motores parados");
}


bool esta_na_linha()
{
    // os pontos de exclamação são necessários por que a lógica do iv
    // é que quando ele não está lendo nada, o sinal é 1 e quando ele está lendo
    // alguma coisa o sinal é 0. o ponto de exclamação nega os valores, trocando o 0 -> 1 
    // e 1 -> 0.
    bool iv1 = !digitalRead(pino_iv_1);
    bool iv2 = !digitalRead(pino_iv_2);
    bool iv3 = !digitalRead(pino_iv_3);
    bool iv4 = !digitalRead(pino_iv_4);
    return (iv1 || iv2 || iv3 || iv4);
}

void girar_robo_esquerda()
{
    Serial.println("\tgirar_robo_esquerda: girando para a esquerda");
    delay(500);
    Serial.println("\tgirar_robo_esquerda: motores parados");
}

void girar_robo_direita()
{
    Serial.println("\tgirar_robo_direita: girando para a direita");
    delay(500);
    Serial.println("\tgirar_robo_direita: motores parados");
}

void mudar_orientacao()
{
    if (dist_direita != 0 && dist_direita < 70)
    {
        girar_robo_direita();
    }
    else if ( (dist_esquerda != 0) && (dist_esquerda < 70) )
    {
        girar_robo_esquerda();
    }
    else
    {
        girar_robo_esquerda(); // potencialmente substituir essa função
                               // por uma função que gira ele em 180°
    }
}


void setup()
{
    Serial.begin(115200);
    // ESC.attach(11);
    pinMode(pino_iv_1, INPUT);
    pinMode(pino_iv_2, INPUT);
    pinMode(pino_iv_3, INPUT);
    pinMode(pino_iv_4, INPUT);
}




void loop()
{
    Serial.println("\n");
    dist_meio = ultra_meio.read();
    dist_esquerda = ultra_esquerda.read();
    dist_direita = ultra_direita.read();
    Serial.print("dist_meio = ");
    Serial.println(dist_meio);
    Serial.print("dist_direita = ");
    Serial.println(dist_direita);
    Serial.print("dist_esquerda = ");
    Serial.println(dist_esquerda);
    delay(500);
    na_linha = esta_na_linha();
    /*
     * Atualmente ele simplesmente para quando encontra a linha, é necessário
     * implementar uma função que faça com que ele saia da linha uma vez que encontrou ela
     */
    
    if( (dist_meio != 0 && dist_meio < 70) && (!na_linha) )
    {
        ataque();
    }
    else
    {
        parar();
        mudar_orientacao();
    }


}



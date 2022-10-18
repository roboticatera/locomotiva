#include <Servo.h>
#include <Ultrasonic.h>
#include "C:\Users\enzo_\Desktop\testes-robo-locomotinfraVermelhoa\comandos_movimento.h"
using namespace Tera::movimento;

// Sensor Infravermelho
short pino_infraVermelho_tras_direita{3};
short pino_infraVermelho_frente_direita{6};
short pino_infraVermelho_frente_esquerda{9};
short pino_infraVermelho_tras_esquerda{12};

// Sensor Ultrassónico
Ultrasonic ultrassonico_direita(4 /*trig*/, 5 /*echo*/);
Ultrasonic ultrassonico_meio(7, 8);
Ultrasonic ultrassonico_esquerda(10, 11);

// ESC's
short pino_ESC_esquerdo{A1};
short pino_ESC_direito{A2};
Servo ESC_esquerdo;
Servo ESC_direito;

// Medições
int dist_meio{};
int dist_esquerda{};
int dist_direita{};
bool na_linha{false};

void ataque()
{
    // ESC.writeMicroseconds(aceleracao::maxima);//move com toda força pra frente
    Serial.println("Attack");
    Serial.println("ataque: Motores indo pra frente");
}

void parar()
{
    // ESC.writeMicroseconds(aceleracao::nula);//para o movimento do motor
    Serial.println("Parar");
    Serial.println("parar: motores parados");
}

bool esta_na_linha()
{
    // os pontos de exclamação são necessários por que a lógica do infraVermelho
    // é que quando ele não está lendo nada, o sinal é 1 e quando ele está lendo
    // alguma coisa o sinal é 0. o ponto de exclamação nega os valores, trocando o 0 -> 1
    // e 1 -> 0.
    bool infraVermelho_tras_direita = !digitalRead(pino_infraVermelho_tras_direita);
    bool infraVermelho_frente_direita = !digitalRead(pino_infraVermelho_frente_direita);
    bool infraVermelho_frente_esquerda = !digitalRead(pino_infraVermelho_frente_esquerda);
    bool infraVermelho_tras_esquerda = !digitalRead(pino_infraVermelho_tras_esquerda);
    return (infraVermelho_tras_direita || infraVermelho_frente_direita || infraVermelho_frente_esquerda || infraVermelho_tras_esquerda);
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
    else if ((dist_esquerda != 0) && (dist_esquerda < 70))
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

    ESC_esquerdo.attach(pino_ESC_esquerdo);
    ESC_direito.attach(pino_ESC_direito);

    pinMode(pino_infraVermelho_1, INPUT);
    pinMode(pino_infraVermelho_2, INPUT);
    pinMode(pino_infraVermelho_3, INPUT);
    pinMode(pino_infraVermelho_4, INPUT);
}

void loop()
{
    Serial.println("\n");

    dist_meio = ultrassonico_meio.read();
    dist_esquerda = ultrassonico_esquerda.read();
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

    if ((dist_meio != 0 && dist_meio < 70) && (!na_linha))
    {
        ataque();
    }
    else
    {
        parar();
        mudar_orientacao();
    }
}

// Debug's
#define _DEBUG_MOVIMENTOS_ // Enquanto essa linha não for um comentário, movimentos do robô serão mostrados no monitor serial

#define _DEBUG_SENSORES_ // Enquanto essa linha não for um comentário, sensores do robô serão mostrados no monitor serial

#include <Ultrasonic.h>
#include "movimentos_basicos.h"
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

bool infraVermelho_tras_direita{false};
bool infraVermelho_frente_direita{false};
bool infraVermelho_frente_esquerda{false};
bool infraVermelho_tras_esquerda{false};

void setup()
{
    Serial.begin(9600);

    ESC_esquerdo.attach(pino_ESC_esquerdo);
    ESC_direito.attach(pino_ESC_direito);

    pinMode(pino_infraVermelho_tras_direita, INPUT);
    pinMode(pino_infraVermelho_frente_direita, INPUT);
    pinMode(pino_infraVermelho_frente_esquerda, INPUT);
    pinMode(pino_infraVermelho_tras_esquerda, INPUT);
}

void loop()
{
    // Aquisição de dados
    dist_meio = ultrassonico_meio.read();
    dist_esquerda = ultrassonico_esquerda.read();
    dist_direita = ultrassonico_direita.read();

    /* os pontos de exclamação são necessários por que a lógica do infraVermelho é que quando ele não está lendo nada, o sinal é 1 e quando ele está lendo alguma coisa o sinal é 0. o ponto de exclamação nega os valores, trocando o 0 -> 1 e 1 -> 0.*/
    infraVermelho_tras_direita = !digitalRead(pino_infraVermelho_tras_direita);
    infraVermelho_frente_direita = !digitalRead(pino_infraVermelho_frente_direita);
    infraVermelho_frente_esquerda = !digitalRead(pino_infraVermelho_frente_esquerda);
    infraVermelho_tras_esquerda = !digitalRead(pino_infraVermelho_tras_esquerda);

#ifdef _DEBUG_SENSORES_
    Serial.println("\n");
    Serial.println("Sensores Ultrassônicos:");
    Serial.println("dist_meio = " + (String)dist_meio);
    Serial.println("dist_direita = " + (String)dist_direita);
    Serial.println("dist_esquerda = " + (String)dist_esquerda);
    Serial.println("Sensores Infravermelhos:");
    Serial.println("infraVermelho_tras_direita = " + (String)infraVermelho_tras_direita);
    Serial.println("infraVermelho_frente_direita = " + (String)infraVermelho_frente_direita);
    Serial.println("infraVermelho_frente_esquerda = " + (String)infraVermelho_frente_esquerda);
    Serial.println("infraVermelho_tras_esquerda = " + (String)infraVermelho_tras_esquerda);
#endif

    delay(500);

    /*
     * Atualmente ele simplesmente para quando encontra a linha, é necessário
     * implementar uma função que faça com que ele saia da linha uma vez que encontrou ela
     */

    // if ((dist_meio != 0 && dist_meio < 70) && (!na_linha))
    if ((dist_meio != 0 && dist_meio < 70))
    {
        avanco(ESC_esquerdo, ESC_direito);
    }
    else
    {
        mudar_orientacao();
    }
}

void saiu_do_ringue()
{

    if (infraVermelho_frente_direita == true || infraVermelho_frente_esquerda == true)
    {
        recuar(ESC_esquerdo, ESC_direito);
        delay(50);
        mudar_orientacao();
    }
    else if (infraVermelho_tras_direita == true || infraVermelho_tras_esquerda == true)
    {
        avanco(ESC_esquerdo, ESC_direito);
        delay(50);
        mudar_orientacao();
    }
}

void mudar_orientacao()
{
    parar(ESC_esquerdo, ESC_direito);
    if (dist_direita != 0 && dist_direita < 70)
    {
        girar_direita(ESC_esquerdo, ESC_direito);
        delay(1000);
        parar(ESC_esquerdo, ESC_direito);
    }
    else if ((dist_esquerda != 0) && (dist_esquerda < 70)) // Qual a diferença entre com e sem parênteses?
    {
        girar_esquerda(ESC_esquerdo, ESC_direito);
        delay(1000);
        parar(ESC_esquerdo, ESC_direito);
    }
    else
    {
        girar_esquerda(ESC_esquerdo, ESC_direito); // potencialmente substituir essa função por uma função que gira ele em 180°
        delay(1000);
        parar(ESC_esquerdo, ESC_direito);
    }
}

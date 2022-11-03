// Debug's
// #define _DEBUG_MICROSTART_ // Enquanto essa linha não for um comentário, as entradas do receptor IR serão mostrados no monitor serial
// #define _DEBUG_MOVIMENTOS_ // Enquanto essa linha não for um comentário, movimentos do robô serão mostrados no monitor serial
// #define _DEBUG_SENSORES_   // Enquanto essa linha não for um comentário, sensores do robô serão mostrados no monitor serial

#include <Ultrasonic.h>
#include <IRremote.hpp>
#include "movimentos_basicos.h"

using namespace Tera::movimento;

// Microstart
short pino_receptor_infravermelho{2}; // Usa o LED Interno como identificador
const long stop = 0xE0E036C9;               // Botão A do controle remoto
const long ready = 0xE0E0A857;              // Botão C do controle remoto
const long start = 0xE0E028D7;              // Botão B do controle remoto
IRrecv irrecv(pino_receptor_infravermelho); // Passa o Parâmetro para a função irrecv
decode_results status;                      // Variável que armazena os resultados do receptor infravermelho

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

    pinMode(LED_BUILTIN, OUTPUT);
    irrecv.enableIRIn(); // inicia a recepção dos sinais

    pinMode(pino_infraVermelho_tras_direita, INPUT);
    pinMode(pino_infraVermelho_frente_direita, INPUT);
    pinMode(pino_infraVermelho_frente_esquerda, INPUT);
    pinMode(pino_infraVermelho_tras_esquerda, INPUT);

    ESC_esquerdo.attach(pino_ESC_esquerdo);
    ESC_direito.attach(pino_ESC_direito);
}

void loop()
{
    if (irrecv.decode(&status)) // se algum código for recebido
    {
#ifdef _DEBUG_MICROSTART_
        Serial.print("Código HEX do Botao: ");
        Serial.println(status.value, HEX); // imprime o HEX
        Serial.print("Status: ");
#endif

        if (status.value == stop)
        {
#ifdef _DEBUG_MICROSTART_
            Serial.println("Stop");
#endif
            digitalWrite(LED_BUILTIN, HIGH);
            while (true)
            {
            }
        }
        else if (status.value == ready)
        {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(5);
            digitalWrite(LED_BUILTIN, LOW);
            delay(5);
            digitalWrite(LED_BUILTIN, HIGH);
            delay(5);
            digitalWrite(LED_BUILTIN, LOW);
#ifdef _DEBUG_MICROSTART_
            Serial.println("Ready");
#endif
        }
        else if (status.value == start)
        {
            digitalWrite(LED_BUILTIN, HIGH);
#ifdef _DEBUG_MICROSTART_
            Serial.println("Start");
#endif
        }

        irrecv.resume(); // reinicializa o receptor
    }

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

    delay(250);

    /*
     * Atualmente ele simplesmente para quando encontra a linha, é necessário
     * implementar uma função que faça com que ele saia da linha uma vez que encontrou ela
     */

    // if ((dist_meio != 0 && dist_meio < 70) && (!na_linha))
    if ((dist_meio != 0 && dist_meio < 70) && status.value == start)
    {
        avanco(ESC_esquerdo, ESC_direito);
    }
    else if (status.value == start)
    {
        mudar_orientacao();
    }
}

void saiu_do_ringue()
{

    if ((infraVermelho_frente_direita == true || infraVermelho_frente_esquerda == true) && status.value == start)
    {
        recuar(ESC_esquerdo, ESC_direito);
        delay(50);
        mudar_orientacao();
    }
    else if ((infraVermelho_tras_direita == true || infraVermelho_tras_esquerda == true) && status.value == start)
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
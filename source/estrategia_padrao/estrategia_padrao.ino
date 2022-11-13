// Debug's
// #define _DEBUG_MICROSTART_ // Enquanto essa linha não for um comentário, as entradas do receptor IR serão mostrados no monitor serial
// #define _DEBUG_SENSORES_   // Enquanto essa linha não for um comentário, sensores do robô serão mostrados no monitor serial

#include <IRremote.hpp>
#include <Ultrasonic.h>
#include "movimentos_basicos.hpp"

using namespace Tera::movimento;

// Microstart
short pino_receptor_infravermelho{2}; // Usa o LED Interno como identificador

const long stop = 0x4BA5; // Botão Vermelho do controle remoto
// const long ready = ; // Botão Verde do controle remoto
const long start = 0x4BA6; // Botão Amarelo do controle remoto

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
const int tempo_intervalo = 50;  // ms
const int tempo_movimento = 500; // ms

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
    // #ifdef _DEBUG_MICROSTART_ || _DEBUG_SENSORES_ || _DEBUG_MOVIMENTOS_
        //Serial.begin(115200);
    // #endif

    IrReceiver.begin(pino_receptor_infravermelho, ENABLE_LED_FEEDBACK); // inicia a recepção dos sinais
    pinMode(pino_infraVermelho_tras_direita, INPUT);
    pinMode(pino_infraVermelho_frente_direita, INPUT);
    pinMode(pino_infraVermelho_frente_esquerda, INPUT);
    pinMode(pino_infraVermelho_tras_esquerda, INPUT);

    ESC_esquerdo.attach(pino_ESC_esquerdo);
    ESC_direito.attach(pino_ESC_direito);
}

void loop()
{

    IrReceiver.decode();
    if (IrReceiver.decodedIRData.decodedRawData == stop)
    {
#ifdef _DEBUG_MICROSTART_
        Serial.println("Sinal STOP");
#endif
        while (true)
        {
            parar(ESC_esquerdo, ESC_direito);
            delay(tempo_intervalo);
        }
    }
    else if (IrReceiver.decodedIRData.decodedRawData == start)
    {
#ifdef _DEBUG_MICROSTART_
        Serial.println("Sinal START");
#endif
    }
#ifdef _DEBUG_MICROSTART_
    else
    {
        Serial.print("Valor do sinal: ");
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
        Serial.println("------------------------------------------------------");
    }
#endif

    IrReceiver.resume();

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
    Serial.println("------------------------------------------------------");
#endif

    saiu_do_ringue();

    if ((dist_meio != 0 && dist_meio < 70) && IrReceiver.decodedIRData.decodedRawData == start)
    {
        avanco(ESC_esquerdo, ESC_direito);
        delay(tempo_intervalo);
    }
    else if (IrReceiver.decodedIRData.decodedRawData == start)
    {
        delay(tempo_intervalo);
        mudar_orientacao();
    }
}

void saiu_do_ringue()
{

    if ((infraVermelho_frente_direita == true || infraVermelho_frente_esquerda == true) && IrReceiver.decodedIRData.decodedRawData == start)
    {
        recuar(ESC_esquerdo, ESC_direito);
        delay(tempo_intervalo);
        mudar_orientacao();
    }
    else if ((infraVermelho_tras_direita == true || infraVermelho_tras_esquerda == true) && IrReceiver.decodedIRData.decodedRawData == start)
    {
        avanco(ESC_esquerdo, ESC_direito);
        delay(tempo_intervalo);
        mudar_orientacao();
    }
}

void mudar_orientacao()
{
    parar(ESC_esquerdo, ESC_direito);
    delay(tempo_intervalo);
    if (dist_direita != 0 && dist_direita < 70  && IrReceiver.decodedIRData.decodedRawData == start)
    {
        girar_direita(ESC_esquerdo, ESC_direito);
        delay(tempo_movimento);
        parar(ESC_esquerdo, ESC_direito);
    }
    else if ((dist_esquerda != 0) && (dist_esquerda < 70) && IrReceiver.decodedIRData.decodedRawData == start) // Qual a diferença entre com e sem parênteses?
    {
        girar_esquerda(ESC_esquerdo, ESC_direito);
        delay(tempo_movimento);
        parar(ESC_esquerdo, ESC_direito);
    }
    else if (IrReceiver.decodedIRData.decodedRawData == start)
    {
        girar_direita(ESC_esquerdo, ESC_direito); // potencialmente substituir essa função por uma função que gira ele em 180°
        delay(tempo_movimento);
        parar(ESC_esquerdo, ESC_direito);
    }
}

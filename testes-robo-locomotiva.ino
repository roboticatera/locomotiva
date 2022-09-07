#include "comandos_movimento.h"

using namespace Tera::movimento; //namespace definido dentro de comandos_movimento.h

// minha proposição de trocas as constantes por enumerações pra aumentar a expressividade do código
// const int pino_ESC = 3; // PIN to control ESC, normally the white wire from ESC
// const int pino_botao_funcionamento = 5;
// const int pino_botao_tras = 6;
// const int pino_botao_frente = 7;
// const int pino_led_funcionamento = 8;

// a enumeração que substituiria as constantes
enum pino : short // no arduino short é 1 byte, então os valores só vão até 255
{
    ESC = 3,
    botao_funcionamento = 5,
    botao_tras = 6,
    botao_frente = 7,
    led_funcionamento = 8
};



// referencia da bounce no readme
Bounce bounce_frente = Bounce();
Bounce bounce_tras = Bounce();
Bounce bounce_reset = Bounce();
int aceleracao_atual{aceleracao::nula};
Servo s_ESC;
int throttle{aceleracao::nula};



void setup()
{
    Serial.begin(9600);
    Serial.println("Started Setup........");
    pinMode(pino::botao_funcionamento, INPUT_PULLUP); // Using Internal PULLUP resistor
    pinMode(pino::botao_tras, INPUT_PULLUP);
    pinMode(pino::botao_frente, INPUT_PULLUP);
    pinMode(pino::led_funcionamento, OUTPUT);
    bounce_frente.attach(pino::botao_frente);
    bounce_frente.interval(5);
    bounce_tras.attach(pino::botao_tras);
    bounce_tras.interval(5);
    bounce_reset.attach(pino::botao_funcionamento);
    bounce_reset.interval(5);
    s_ESC.attach(pino::ESC);
    s_ESC.writeMicroseconds(aceleracao::maxima);
    delay(2000);
    recuar(s_ESC);
    delay(2000);



    s_ESC.writeMicroseconds(aceleracao::nula);
}

void loop()
{
    bounce_frente.update();
    bounce_reset.update();
    bounce_tras.update();

    if (bounce_reset.fell())
    { // button pressed
        (void)bounce_tras.fell();
        (void)bounce_tras.fell();
        s_ESC.writeMicroseconds(aceleracao::nula);
    }
    else if (bounce_frente.fell())
    {
        // o (void) normalmente é interpretado pelos compiladores como um sinal de que
        // o resultado pode ser ignorado, facilitando na parte de otimizações, e para não disperdiçar memória
        (void)bounce_reset.fell();
        (void)bounce_tras.fell(); // limpa o status do botao_tras pra evitar que ambos sejam apertados em rápida
                                  // sucessão e que os comandos sejam transmitidos rapidamente em sequência
        s_ESC.writeMicroseconds(aceleracao::maxima);
    }
    else if (bounce_tras.fell())
    {
        (void)bounce_reset.fell();
        (void)bounce_frente.fell();              // limpa o status do botao_tras pra evitar que ambos sejam apertados em rápida
                                                 // sucessão e que os comandos sejam transmitidos rapidamente em sequência
        recuar(s_ESC);
        Serial.println("Ré"); // ré
    }
}

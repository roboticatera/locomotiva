#include "Bounce2.h"
#include <Servo.h>

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
    led_funcionamento = 8
};

enum aceleracao : int // no arduino short é 2 bytes, então os valores só vão até 65535
{
    minima = 1080,
    re = 1080, // para auxiliar também na expressividade do código
    nula = 1480,
    maxima = 1800
};

Bounce bounce_funcionamento = Bounce();
int aceleracao_atual{aceleracao::nula};
boolean startReading{false};
Servo s_ESC;
int throttle{aceleracao::nula};

void setup()
{
    Serial.begin(9600);
    Serial.println("Started Setup........");
    pinMode(pino::botao_funcionamento, INPUT_PULLUP); // Using Internal PULLUP resistor
    pinMode(pino::led_funcionamento, OUTPUT);
    bounce_funcionamento.attach(pino::botao_funcionamento);
    bounce_funcionamento.interval(5);
    s_ESC.attach(pino::ESC);
    s_ESC.writeMicroseconds(aceleracao::nula);

    digitalWrite(pino::led_funcionamento, HIGH);
    delay(1000);
    digitalWrite(pino::led_funcionamento, LOW);
}

void loop()
{
    bounce_funcionamento.update();

    if (bounce_funcionamento.fell())
    { // button pressed
        if (!startReading)
        {                                                // if not in reading mode
            startReading = true;                         // change to reading mode
            digitalWrite(pino::led_funcionamento, HIGH); // on the onboard LED, for visual indicator
            Serial.println("Start Sensor Read ----- ");
            s_ESC.writeMicroseconds(aceleracao::maxima);
        }
        else
        {                                              // currently in reading mode, should stop reading and brake DC brushed motor
            s_ESC.writeMicroseconds(aceleracao::nula); // brake DC brushed motor
            startReading = false;                      // change to stop reading mode
            throttle = aceleracao::nula;
            digitalWrite(pino::led_funcionamento, LOW); // off the onboard LED, for visual indicator
            Serial.println("Stop Sensor Read ----- ");
        }
    }
}

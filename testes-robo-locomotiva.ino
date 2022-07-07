#include "Bounce2.h"
#include <Servo.h>

const int pino_led_funcionamento = 8;
const int pino_botao_frente = 7;
const int pino_botao_tras = 6;
const int pino_botao_funcionamento = 5;
const int pino_ESC = 3; 


enum aceleracao : int
{
	minima = 1080,
	nula = 1480,
	maxima = 1800
};

Bounce botao_frente = Bounce();
Bounce botao_tras = Bounce();
Bounce botao_funcionamento = Bounce();
int aceleracao_atual = aceleracao::minima;
boolean startReading = false;
Servo ESC;
int throttle{aceleracao::minima};

void setup()
{
	Serial.begin(9600);
	Serial.println("Started Setup........");
	pinMode(pino_botao_funcionamento, INPUT_PULLUP); // Using Internal PULLUP resistor
	pinMode(pino_botao_tras, INPUT_PULLUP);
	pinMode(pino_botao_frente, INPUT_PULLUP);
	pinMode(pino_led_funcionamento, OUTPUT);
	botao_frente.attach(pino_botao_frente);
	botao_frente.interval(5);
	botao_tras.attach(pino_botao_tras);
	botao_tras.interval(5);
	botao_funcionamento.attach(pino_botao_funcionamento);
	botao_funcionamento.interval(5);
	ESC.attach(pino_ESC);
	ESC.writeMicroseconds(aceleracao::nula);

	digitalWrite(pino_led_funcionamento, HIGH);
	delay(1000);
	digitalWrite(pino_led_funcionamento, LOW);
}

void loop()
{

	if (botao_funcionamento.fell())
	{ // button pressed
		if (!startReading)
		{												// if not in reading mode
			startReading = true;						// change to reading mode
			digitalWrite(pino_led_funcionamento, HIGH); // on the onboard LED, for visual indicator
			Serial.println("Start Sensor Read ----- ");
		}
		else
		{												   // currently in reading mode, should stop reading and brake DC brushed motor
			ESC.writeMicroseconds(aceleracao::nula); // brake DC brushed motor
			startReading = false;						   // change to stop reading mode
			throttle = aceleracao::nula;
			digitalWrite(pino_led_funcionamento, LOW); // off the onboard LED, for visual indicator
			Serial.println("Stop Sensor Read ----- ");
		}
	}

	if (startReading)
	{ // in reading mode
		if(botao_frente.fell())
		{
			ESC.writeMicroseconds(aceleracao::maxima); 
		}
		else if(botao_tras.fell())
		{
			ESC.writeMicroseconds(aceleracao::minima);
		}
		

	}
}

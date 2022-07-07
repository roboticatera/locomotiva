#include "Bounce2.h"
#include <Servo.h>



// minha proposição de trocas as constantes por enumerações pra aumentar a expressividade do código
//const int pino_ESC = 3; // PIN to control ESC, normally the white wire from ESC
//const int pino_botao_funcionamento = 5;
//const int pino_botao_tras = 6;
//const int pino_botao_frente = 7;
//const int pino_led_funcionamento = 8;


// a enumeração que substituiria as constantes
enum pino : short // no arduino short é 1 byte, então os valores só vão até 255
{
	ESC = 3,
	botao_funcionamento = 5,
	botao_tras = 6,
	botao_frente = 7,
	led_funcionamento = 8
};

enum aceleracao : int // no arduino short é 2 bytes, então os valores só vão até 65535
{
	minima = 1080,
	re = 1080,// para auxiliar também na expressividade do código
	nula = 1480,
	maxima = 1800
};

Bounce botao_frente = Bounce();
Bounce botao_tras = Bounce();
Bounce botao_funcionamento = Bounce();
int aceleracao_atual{aceleracao::nula};
boolean startReading{false};
Servo ESC;
int throttle{aceleracao::nula};

void setup()
{
	Serial.begin(9600);
	Serial.println("Started Setup........");
	pinMode(pino::botao_funcionamento, INPUT_PULLUP); // Using Internal PULLUP resistor
	pinMode(pino::botao_tras, INPUT_PULLUP);
	pinMode(pino::botao_frente, INPUT_PULLUP);
	pinMode(pino::led_funcionamento, OUTPUT);
	botao_frente.attach(pino::botao_frente);
	botao_frente.interval(5);
	botao_tras.attach(pino::botao_tras);
	botao_tras.interval(5);
	botao_funcionamento.attach(pino::botao_funcionamento);
	botao_funcionamento.interval(5);
	ESC.attach(pino::ESC);
	ESC.writeMicroseconds(aceleracao::nula);

	digitalWrite(pino::led_funcionamento, HIGH);
	delay(1000);
	digitalWrite(pino::led_funcionamento, LOW);
}

void loop()
{

	if (botao_funcionamento.fell())
	{ // button pressed
		if (!startReading)
		{												// if not in reading mode
			startReading = true;						// change to reading mode
			digitalWrite(pino::led_funcionamento, HIGH); // on the onboard LED, for visual indicator
			Serial.println("Start Sensor Read ----- ");
		}
		else
		{												   // currently in reading mode, should stop reading and brake DC brushed motor
			ESC.writeMicroseconds(aceleracao::nula); // brake DC brushed motor
			startReading = false;						   // change to stop reading mode
			throttle = aceleracao::nula;
			digitalWrite(pino::led_funcionamento, LOW); // off the onboard LED, for visual indicator
			Serial.println("Stop Sensor Read ----- ");
		}
	}

	if (startReading)
	{ // in reading mode
		if(botao_frente.fell())
		{
			// o (void) normalmente é interpretado pelos compiladores como um sinal de que 
			// o resultado pode ser ignorado, facilitando na parte de otimizações, e para não disperdiçar memória
			(void)botao_tras.fell(); // limpa o status do botao_tras pra evitar que ambos sejam apertados em rápida
									 // sucessão e que os comandos sejam transmitidos rapidamente em sequência
			ESC.writeMicroseconds(aceleracao::maxima); 
		}
		else if(botao_tras.fell())
		{
			(void)botao_frente.fell(); // limpa o status do botao_tras pra evitar que ambos sejam apertados em rápida
									   // sucessão e que os comandos sejam transmitidos rapidamente em sequência
			ESC.writeMicroseconds(aceleracao::re);// ré
		}

	}
}

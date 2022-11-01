#include <IRremote.hpp>

// Pinos
const int pino_vermelho = 3;
const int pino_verde = 4;
const int pino_azul = 5;
const int pino_receptor_infravermelho = 7;

// Estados
const long stop = 0;
const long ready = 0xE0E020DF; // botão 1 do controle remoto
const long start = 0xE0E0A05F; // botão 2 do controle remoto

IRrecv irrecv(pino_receptor_infravermelho); // PASSA O PARÂMETRO PARA A FUNÇÃO irrecv
decode_results status;                      // VARIÁVEL QUE ARMAZENA OS RESULTADOS (SINAL IR RECEBIDO)

void setup()
{
  pinMode(pino_vermelho, OUTPUT);
  pinMode(pino_verde, OUTPUT);
  pinMode(pino_azul, OUTPUT);

  Serial.begin(9600);  // INICIALIZA A SERIAL
  irrecv.enableIRIn(); // INICIALIZA A RECEPÇÃO DE SINAIS

  status.value = stop;
  cor(255, 0, 0); // LED vermelho
}

void loop()
{

  if (irrecv.decode(&status)) // se algum código for recebido
  {
    Serial.println(status.value, HEX); // imprime o HEX Code
    irrecv.resume();                   // reinicializa o receptor

    if (status.value == ready)
    {
      cor(0, 0, 255); // LED azul
      irrecv.resume();
    }
    else if (status.value == start)
    {
      cor(0, 255, 0); // LED verde
      irrecv.resume();
    }
  }
}

void cor(unsigned char vermelho, unsigned char verde, unsigned char azul)
{
  analogWrite(pino_vermelho, vermelho);
  analogWrite(pino_verde, verde);
  analogWrite(pino_azul, azul);
}
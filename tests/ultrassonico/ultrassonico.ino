int pino_trig{5};
int pino_echo{6};
long tempo{};
double distancia{};

void setup()
{
    Serial.begin(9600);
    pinMode(pino_echo, INPUT);
    pinMode(pino_trig, OUTPUT);
}

void loop() 
{
  delay(100);
  digitalWrite(pino_trig,LOW);
  delayMicroseconds(2);
  digitalWrite(pino_trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pino_trig,LOW);
  tempo = pulseIn(pino_echo,HIGH);
  distancia = double(tempo) * 0.017;
  Serial.println(distancia);
}
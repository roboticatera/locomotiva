int sig{A0};
long out{};

void setup()
{
    Serial.begin(9600);
    pinMode(sig, INPUT);
    Serial.print("pino sig = ");
    Serial.println(sig);
}

void loop()
{
    delay(100);
    out = analogRead(sig);
    Serial.println(out);
}
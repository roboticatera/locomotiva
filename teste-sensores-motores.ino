#include <Ultrasonic.h>

short pino_ir_1{1};
short pino_ir_2{2};
short pino_ir_3{3};
short pino_ir_4{4};


Ultrasonic ultra1(5,6);//Ultrasonic ultra1(trig,echo);
Ultrasonic ultra1(7,8);
Ultrasonic ultra1(9,10);


void setup()
{
    Serial.begin(115200);
    pinMode(pino_ir_1, INPUT);
    pinMode(pino_ir_2, INPUT);
    pinMode(pino_ir_3, INPUT);
    pinMode(pino_ir_4, INPUT);
}

void loop()
{
    delay(2000);
    Serial.print("ir_1 = ");
    Serial.println(digitalRead(pino_ir_1));
    Serial.print("ir_2 = ");
    Serial.println(digitalRead(pino_ir_2));
    Serial.print("ir_3 = ");
    Serial.println(digitalRead(pino_ir_3));
    Serial.print("ir_4 = ");
    Serial.println(digitalRead(pino_ir_4));
    Serial.print("ultra_1 = ");
    Serial.println(ultra1.read());
    Serial.print("ultra_2 = ");
    Serial.println(ultra2.read());
    Serial.print("ultra_3 = ");
    Serial.println(ultra3.read());

}

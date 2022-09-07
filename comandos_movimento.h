#include "Bounce2.h"
#include <Servo.h>



namespace Tera
{
    namespace movimento
    {

        enum aceleracao : int // no arduino short é 2 bytes, então os valores só vão até 65535
        {
            minima = 1080,
            re = 1080, // para auxiliar também na expressividade do código
            nula = 1480,
            maxima = 1800
        };
        void recuar(Servo& ESC)
        {
            Serial.println(ESC.readMicroseconds());
            if (ESC.readMicroseconds() == aceleracao::maxima)
            {
                
                ESC.writeMicroseconds(aceleracao::re);
                delay(50);
                ESC.writeMicroseconds(aceleracao::nula);
                delay(50);
                ESC.writeMicroseconds(aceleracao::re);
            }
            else
            {
                ESC.writeMicroseconds(aceleracao::re);
            }
        }

    }
}



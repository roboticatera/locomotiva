#include <Servo.h>
#ifndef _MOVIMENTOS_BASICOS_H_
#define _MOVIMENTOS_BASICOS_H_

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

        void avanco_motor(Servo & ESC);
        void recuar(Servo & ESC1, Servo & ESC2);
        void avanco(Servo & ESC1, Servo & ESC2);
        void parar(Servo & ESC1, Servo & ESC2);
        void girar_esquerda(Servo & ESC1, Servo & ESC2);
        void girar_direita(Servo & ESC1, Servo & ESC2);
    }
}
#endif // _MOVIMENTOS_BASICOS_H_

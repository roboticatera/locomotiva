#include "Bounce2.h"
#include <Servo.h>

#ifndef _COMANDOS_MOVIMENTO_H_
#define _COMANDOS_MOVIMENTO_H_

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

        void recuar(Servo& ESC);
        
    }
}


#endif // _COMANDOS_MOVIMENTO_H_

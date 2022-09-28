#include "comandos_movimento.h"

void Tera::movimento::recuar(Servo &ESC) 
{
  ESC.writeMicroseconds(aceleracao::re);
  delay(50);
  ESC.writeMicroseconds(aceleracao::nula);
  delay(50);
  ESC.writeMicroseconds(aceleracao::re);
}

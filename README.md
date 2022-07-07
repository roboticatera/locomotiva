# testes-robo-locomotiva
Repositório destinado para o controle dos códigos utilizados nos testes e estudos para a cosntrução e programação da Locomotiva

Uma descrição mais completa do intuito do teste, curcuito e resultados estarão no readme de cada teste

# Teste  de inversão da direção do ESC

Esse commit contém o código utilizado, também da forma na qual ele foi utilizado para realizar o primeiro teste do ESC, o arquivo principal do sketch é o `testes-robo-locomotiva.ino`, que nada mais é o arquivo `ControlESC_Turnigy.ino` da biblioteca [`Arduino-Control-Brushed-ESC`](https://github.com/tungstenexe/Arduino-Control-Brushed-ESC). Um fork do projeto não foi realizado por que o intuito principal não era realizar uma continuação da biblioteca, mas apenas utiliza-la nesse teste.

## Circuito eletrônico utilizado

o circuito utilizado para esse teste foi o montado de acordo com o esquema contido no arquivo `circuit.pdf` desse commit.

## Intuito e resultados

O objetivo do teste era tentar realizar a inversão da rotação do motor, alterou-se o vaolor de `#define THROTTLE_MIN`, o que não é recomendado pois fugir da range entre `1000` e `2000` para a largura do pulso, pode forçar o ESC.

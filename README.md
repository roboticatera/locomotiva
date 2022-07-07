# testes-robo-locomotiva
Repositório destinado para o controle dos códigos utilizados nos testes e estudos para a cosntrução e programação da Locomotiva

Uma descrição mais completa do intuito do teste, curcuito e resultados estarão no readme de cada teste

# Teste de controle do ESC sem utilização do potenciômetro

Esse commit contém o código utilizado, também da forma na qual ele foi utilizado para realizar o teste do ESC sem potenciometro, o arquivo principal do sketch é o `testes-robo-locomotiva.ino`, que tem como base o arquivo `ControlESC_Turnigy.ino` da biblioteca [`Arduino-Control-Brushed-ESC`](https://github.com/tungstenexe/Arduino-Control-Brushed-ESC) refatorado para utilização dentro do Tera.

## Circuito eletrônico utilizado

o circuito utilizado para esse teste foi o montado de acordo com o esquema contido nos arquivos `circuit.pdf` e `circuit_tinkercad.png` desse commit.

## Intuito e resultados

O objetivo desse teste é estudar a reação do ESC agora sendo invertido totalmente pelo arduino, se a resposta será a mesma que obtemos quando testando o ESC com o radio controle. 

Até o momento desse commit apenas uma tentativa foi realizada, devido a falta de tempo, ela foi interrompida no meio e não foi bem sucedida, o motor girou brevemente mas na maior parte do tempo ele não reagia, nem o led de funcionamento chegou a ascender, então atualmente é provavel que tenha algum problema no circuito ou na programação.
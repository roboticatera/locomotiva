
# Locomotiva 🚂
O Locomotiva é um robô Sumô Autônomo 3kg, inicialmente feito para competir na [RoboCore Experience 2022](https://www.robocoreexperience.com/).

# Requisitos
- [Arduino IDE](https://www.arduino.cc/en/software): Ambiente de desenvolvimento da linha de microcontroladores Arduino, para compilar, editar e enviar o código para o microcontrolador.
  >Também é possível fazer a instalação do [Visual Studio Code (VScode)](https://code.visualstudio.com/download) 
  para a edição de código. O qual possui uma vasta gama de extensões para facilitar
  a programação. Para utilizar o VScode com arduino é necessário o download da extensão de nome Arduino,
  produzida pela própria Microsoft, obtida na aba de extensões.
  No caso de utilizar o VScode, certifique-se de que o sketch
  que está sendo compilado e upado é o sketch desejado. O que pode ser escolhido 
  por meio da paleta de comandos(atalho - `Ctrl+shift+o`).

- [Ultrassonic](https://github.com/ErickSimoes/Ultrasonic): Aquisição dos valores de distância pelo ultrassônico.

- [IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote): Decodificação de sinais do controle remoto.

## Instalando Bibliotecas
Todas as bibliotecas externas utilizadas no projeto podem ser instaladas de duas formas: 
- Instalando diretamente via gerenciador de bibliotecas da IDE do Arduino.
- Acessando o repositório e depois fazendo o download do repositório no formato zip clicando no botão `<>code` e clicando e download zip e então adicionando ele como uma biblioteca no gerenciador de bibliotecas da IDE do Arduino.

# Começando

## Obtendo o código
Para obter o código fonte desse reposítório, é altamente recomendado que se utilize o Git 
local associado com a sua conta do Github.

Então é possível utilizar o commando:
``` shell 
git clone https://github.com/roboticatera/locomotiva.git
```

E o Git fará o download automático do repositório.

Também é possível fazer o download do arquivo zip utilizando o botão `<>code`
e então em download zip ou diretamente do link
https://github.com/roboticatera/locomotiva/archive/refs/heads/main.zip

## Enviando o código para o microcontrolador

Para buildar o código certifique-se de que os requisitos estão 
instalados e então utilizando a IDE do arduio, abra o arquivo 
`.ino` desejado e clique no botão de `verificar` para compilar o código 
ou escolha a placa do arduino utilizada na barra de menu, 
em ferramentas -> placa -> \<placa\_utilizada\>. Então escolhar a porta USB
no qual o arduino está conectado clicando em Ferramentas -> Porta -> \<Porta\_do\_arduino\>. Após esses procedimentos, clique na setinha de `upload`
na interface da IDE do Arduino.

Opcionalmente também é possível realizar um procedimento semelhante utilizando o 
VScode.

# Biblioteca Interna

Os arquivos `movimentos_basicos.cpp` e `movimentos_basicos.hpp`, constituem a biblioteca interna do projeto, que contém os comandos básicos para a movimentação do mesmo. Por ser genérica, ela pode ser utilizada em outros projetos. As funções desenvolvidas dentro do Tera estão todas dentro do `namespace` do `Tera`,
que atualmente possui apenas outro namespace dentro chamado `movimento`.

O intuito dessa organização é evitar a colisão de nomes dentre bibliotecas
e também marcar o desenvolvimendo do Tera.

Para evitar usar longos nomes para chamar as funções é possível utilizar, 
no começo do arquivo, o statement: `using namespace Tera::movimento;` o
que trará as funções de dentro desse namespace para o escopo atual, podendo 
ser chamadas diretamente.

Para utilização em outros projetos deve-se alterar os valores contidos em `enum aceleracao : int`, que nada mais são que o tempo (milisegundos) do PWM gerado pelo ESC. Eles podem ser aferidos com a ajuda de um Osciloscópio Digital.

# Estrutura do repositório

Atualmente esse repositório armazena tanto os códigos utilizados para testar 
o robô (dentro da pasta `tests`), quanto o código utiliado pelo robô em batalha(pasta `source`).

Atualmente estamos utilizando as tags no repositório para marcar os commits 
no qual um teste foi finalizado ou a implementação de uma estratégia 
foi finalizada. Tags também são utilizadas para marcar as versões 
finais dos códigos utilizados de fato nas competições. 

Para visualizar as tags já existentes basta utilizar o commando `git tag` 
no repositório ou no github clicar em `tags` logo ao lado de onde marca 
a branch atual.

Vale ressalar que os arquivos da biblioteca interna devem estar presentes nas pastas da rotina que executar. Não conseguimos fazer com que essa biblioteca se comporte como as gerenciadas pela IDE do Arduino.

# Possíves melhorias para próximos projetos

- Tornar a utilização da biblioteca interna mais fácil.
- Tornar funções de escritas e leitura de dados menos genéricas e mais performáticas, diminuindo o tempo de resposta de comando.




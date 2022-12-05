
# Testes do Locomotiva
O Locomotiva é um robô de combate da categoria Sumô Autônomo 3kg, e este repositório é voltado para os testes e estudos realizados para a programação do Locomotiva


# Requisitos

- [Ultrassonic](https://github.com/ErickSimoes/Ultrasonic): que pode ser obtida 
  clicando no link do reposotório e depois fazendo o download do repositório
  no formato zip clicando no botão `<>code` e clicando e download zip.

  ou fazendo o download do zip diretamento do link https://github.com/ErickSimoes/Ultrasonic/archive/refs/heads/master.zip e 
  então adicionando ele como uma biblioteca no gerenciadore de bibliotecas da IDE do Arduino.

- [IRremote](https://github.com/Arduino-IRremote/Arduino-IRremote): Que pode ser obtida da mesma 
  forma que a Ultrassonic, fazendo o download do zip a partir do repositório no botão `<>code`
  ou diretamente por meio do link https://github.com/Arduino-IRremote/Arduino-IRremote/archive/refs/heads/master.zip

  também é possível instalar ela por meio do gerenciador de bibliotecas do arduino, pesquisando por `IRremote`, é a 
  biblioteca feita por Armin Joachimsmeyer

- Também, para que seja possível compilar e fazer o upload do sketch é necessária a instalação a [IDE do Arduino](https://www.arduino.cc/en/software).

- (Opcional) Também é possível fazer a instalação do [Visual Studio Code (VScode)](https://code.visualstudio.com/download) 
  para a edição de código. O qual possui uma vasta gama de extensões para facilitar
  a programação. Para utilizar o VScode com arduino é necessário o download da extensão de nome Arduino,
  produzida pela própria Microsoft, obtida na aba de extensões.
  No caso de utilizar o VScode, certifique-se de que o sketch
  que está sendo compilado e upado é o sketch desejado. O que pode ser escolhido 
  por meio da paleta de comandos(atalho - `Ctrl+shift+o`).

# Biblioteca do Tera

As funções desenvolvidas dentro do Tera estão todas dentro do `namespace` do `Tera`,
que atualmente possui apenas outro namespace dentro chamado `movimento`.

O intuito dessa organização é evitar a colisão de nomes dentre bibliotecas
e também marcar o desenvolvimendo do Tera.

Para evitar usar longos nomes para chamar as funções é possível utilizar, 
no começo do arquivo, o statement: `using namespace Tera::movimento;` o
que trará as funções de dentro desse namespace para o escopo atual, podendo 
ser chamadas diretamente.

## Estrutura do repositório

Atualmente esse repositório armazena tanto os códigos utilizados para testar 
o robô(dentro da pasta `tests`), quanto o código utiliado pelo robô em batalha(pasta `source`).

Atualmente estamos utilizando as tags no repositório para marcar os commites 
no qual um teste foi finalizado ou a implementação de uma estratégia 
foi finalizada. Tags também são utilizadas para marcar as versões 
finais dos códigos utilizados de fato nas competições. 

Para visualizar as tags já existentes basta utilizar o commando `git tag` 
no repositório ou no github clicar em `tags` logo ao lado de onde marca 
a branch atual.

para fazer o push das tags basta utilizar os commandos:

```bash
# push de uma única tag(os sinais < e > não fazer parte do comando ou nome )
git push <nome_do_remote> <nome_da_tag>

# para fazer o push de todas as tags
git push --tags
```

# Obtendo o código fonte

Para obter o código fonte desse reposítório, é altamente recomendado que se utilize o Git 
local associado com a sua conta do Github.

Então é possível utilizar o commando: `git clone https://github.com/roboticatera/locomotiva.git`

E o Git fará o download automático do repositório.

Também é possível fazer o download do arquivo zip utilizando o botão `<>code`
e então em download zip ou diretamente do link
https://github.com/roboticatera/locomotiva/archive/refs/heads/main.zip

# Build e upload

Para buildar o código certifique-se de que os requisitos estão 
instalados e então utilizando a IDE do arduio, abra o arquivo 
`.ino` desejado e clique no botão de `verificar` para compilar o código 
ou escolha a placa do arduino utilizada na barra de menu, 
em ferramentas -> placa -> \<placa\_utilizada\>. Então escolhar a porta USB
no qual o arduino está conectado clicando em Ferramentas -> Porta -> \<Porta\_do\_arduino\>. Após esses procedimentos, clique na setinha de upload
na interface da IDE do Arduino.

Opcionalmente também é possível realizar um procedimento semelhante utilizando o 
VScode.

# Melhorias a serem feitas




# LabMicApl - Trabalho Final
Repositório do Trabalho final da disciplina Laboratório de Microcontroladores e Aplicações. 

# Sobre o Repositório
Existem três pastas com projetos .ino independentes. 
* O projeto "stepper" é um teste do motor de passo e do LCD
* O projeto "tranca_versaoSerial" é uma versão do programa que utiliza a Serial como entrada para a senha, ao invés dos botões
* O projeto "tranca_versaoBotoes" é o projeto principal, o qual é descrito nesta documentação

# Proposta
A proposta do projeto consiste numa tranca de portão, que funcionará de acordo com as seguintes especificações:

  1. Quando aberto, o portão aguarda um comando para que seja fechado (por um botão).
  2. O motor é acionado e continua girando até que o fim de curso seja atingido.
  3. Quando o portão é fechado, ele gera uma senha númerica que deve ser utilizada para abrir o portão.
  4. Quando fechado, o portão aguarda a entrada da senha (através de um conjunto de quatro botões, cada um representando um digíto). Caso a senha seja correta, o portão abre. Caso se erre a senha três vezes, o sistema trava, o portão mantêm-se fechado e um alarme é disparado.

O funcionamento é bem representado pelo seguinte diagrama de estados:

![alt text](https://github.com/gabrielNT/LabMicApl_TrabalhoFinal/blob/master/Imagens/diagramaEstados.png "Diagrama de estados")

O conceito de máquina de estados também foi utilizado na implementação do projeto, evidenciado pelo uso do *switch case*.


# Detalhes de implementação
O projeto foi implementado para o [Arduino Mega 2560](https://www.arduino.cc/en/Main/ArduinoBoardMega2560), utilizando os componentes de um [kit Grove](http://www.seeedstudio.com/wiki/Grove_System). Os componentes utilizados foram:
  * Um sensor de toque, que simula os finais de curso do portão
  * Um botão, que será utilizado para o controle da mudança de estados (ordenar o fechamento do portão)
  * Um display LCD, que mostrará a senha que deverá ser utilizada na próxima abertura, e as mensagens do sistema
  * Um Buzzer, para sinalizar o clique dos botões de senha e para o alarme

Além disso, os seguintes componentes que não fazem parte do kit foram utilizados:
  * Um motor de passo, para a abertura e o fechamento do portão
  * Quatro botões, para a entrada das senhas
  * Um conjunto de transistores (no chip UNL2003)

Esquemático: 

[![IMAGE ALT TEXT](https://github.com/gabrielNT/LabMicApl_TrabalhoFinal/blob/master/Imagens/esquematico.jpg)](http://schematics.com/project/projetoportao-24714/ "Esquemático")


# Protótipo do projeto:

Vídeo do projeto em execução: 

[![IMAGE ALT TEXT](http://img.youtube.com/vi/V0DCulgi8PI/0.jpg)](http://www.youtube.com/watch?v=V0DCulgi8PI "Projeto Final "Portão com senha")

Foto do protótipo do projeto:

![alt text](https://github.com/gabrielNT/LabMicApl_TrabalhoFinal/blob/master/Imagens/fotoProjeto.jpg "Protótipo")

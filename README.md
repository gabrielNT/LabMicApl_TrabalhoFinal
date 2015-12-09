# LabMicApl_TrabalhoFinal
Repositório do Trabalho final da disciplina Laboratório de Microcontroladores e Aplicações. 

# Proposta
A proposta do projeto consiste numa tranca de portão, que funcionará de acordo com as seguintes especificações:

  1. Quando aberto, o portão aguarda um comando para que seja fechado (por um botão).
  2. O motor é acionado e continua girando até que o fim de curso seja atingido.
  3. Quando o portão é fechado, ele gera uma senha númerica que deve ser utilizada para abrir o portão.
  4. Quando fechado, o portão aguarda a entrada da senha (através de um conjunto de quatro botões, cada um representando um digíto). Caso a senha seja correta, o portão abre. Caso se erre a senha três vezes, o sistema trava e deve manter o portão fechado.

O funcionamento é bem representado pelo seguinte diagrama de estados:

[Inserir Diagrama de Estados]

# Detalhes de implementação
O projeto foi implementado para o [Arduino Mega 2560](https://www.arduino.cc/en/Main/ArduinoBoardMega2560), utilizando os componentes de um [kit Grove](http://www.seeedstudio.com/wiki/Grove_System). Os componentes utilizados foram:
  *Um sensor de toque, que simula os finais de curso do portão
  * Um botão, que será utilizado para o controle da mudança de estados (ordenar o fechamento do portão)
  * Um display LCD, que mostrará a senha que deverá ser utilizada na próxima abertura, e as mensagens do sistema

Além disso, os seguintes componentes que não fazem parte do kit foram utilizados:
  * Um motor de passo, para a abertura e o fechamento do portão
  * Quatro botões, para a entrada das senhas
  * Um conjunto de transistores (no chip UNL2003)

O esquemático do circuito está abaixo:

[Inserir esquemático]

# Imagens do protótipo do projeto

[Inserir fotos]

# Vídeo do projeto em execução
  
[Inserir vídeo]

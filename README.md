# MAC COLLECTOR

O intuito do protótipo é o entendimento e espelhamento do sistema coletor de macs da incubadora, tenho como objetivo conseguir resumir o código tornando mais compreensível e acessível a todos.

Até o momento o código faz o seguinte

1. Conecta a uma rede wifi atraves de outro hardware, seja celular ou computador, voce se conecta a rede gerada pelo ESP32 e entao conecta-se a uma rede que realmente tenha vinculo com a internet.
2. Atraves do wifi conectado o ESP32 ira recolher os enderecos macs proximos ao wifi e enviar em formato de tabela para o terminal
3. Caso o ESP32 esteja conectado a um computador ele ira gerar um bloco de notas com os mac coletados enquanto ficou ligado.

## Deployment

Caso queira utilizar modificar o código do projeto

- Faça download da Extensão do rfid ```PLATFORMIO```
- Conecte o rfid no computador
- Clique em BUILD para ver se há erro
- Clique em UPLOAD para enviar o código para o rfid
- Agora só clicar em SERIAL MONITOR para ver o código debuggar em tempo real.

## Used By

This project is used by the following companies:

- TecnoMaub

## Future Updates

- Inserir codigo que mude o canal do wifi
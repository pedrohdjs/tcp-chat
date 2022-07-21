# Bate-papo baseado em IRC para a disciplina de Redes de Computadores

> Projeto de bate-papo IRC customizado. Requisito parcial da disciplina de Redes de Computadores (SSC0142) do curso de Ciências de Computação do ICMC/USP durante o 1º semestre de 2022.

## Ferramentas utilizadas

O projeto foi desenvolvido no sistema operacional Ubuntu, através do compilador `gcc`. Oferece suporte a outras plataformas, como Mac e Windows.

## Estrutura do projeto

O projeto está subdivido nas pastas `src`, com o código-fonte e `dist`, com os arquivos gerados pela compilação. A pasta `src` está subdivida da seguinte forma:

- `client`: com os arquivos do cliente do sistema;do cliente do sistema;
- `server`: com os arquivos do servidor do sistema;
- `shared`: com os arquivos gerais compartilhados entre cliente e servidor.

## Instruções de compilação

Na raiz do projeto, execute os seguintes comandos:

- `make all`: faz a build do cliente e do servidor
- `make server`: faz a build do servidor
- `make client`: faz a build do cliente
- `make runserver`: executa o servidor
- `make runclient`: executa o cliente

## Operações disponíveis

O sistema fornece, ao cliente, as seguintes operações:

- `/help`: apresenta as operações disponíveis;
- `/clear`: limpa o terminal;
- `/connect`: conecta a um servidor (`/connect PORTA IP`);
- `/ping`: faz o servidor retornar um `pong`;
- `/nickname`: define um nickname ao usuário (`/nickname nickname`);
- `/join`: entra numa sala (`/join #sala`);
- `/mute`: muta um usuário (`/mute nickanme`);
- `/unmute`: desmuta um usuário (`/unmute nickanme`);
- `/kick`: expulsa um usuário (`/kick nickanme`);
- `/quit`: sai da aplicação.

Além disso, quando conectado a uma sala, basta digitar qualquer texto, sem o indicador de comando `/` para enviar uma mensagem aos demais participantes.

## Autores

- Matheus Henrique de Cerqueira Pinto (11911104)
- Pedro Henrique Dias Junqueira de Souza (11294312)
- Tarcídio Antonio Junior (10748347)

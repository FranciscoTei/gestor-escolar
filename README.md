# Gestor Escolar - Versão 1

## Descrição do Projeto
Este projeto faz parte da avaliação de Algoritmos e Estrutura de Dados I da faculdade. O objetivo do projeto é criar um sistema de gestão escolar que permita aos professores fazer login e manipular dados de alunos. Na versão atual, os dados são armazenados em arquivos `.txt`. Para a próxima versão, será permitido login tanto para professores quanto para alunos e migrar o armazenamento de dados para um banco de dados SQLite.

## Estrutura do Projeto
### Arquivos e Pastas
- `include/`: Contém arquivos de cabeçalho (`.h`).
- `src/`: Contém arquivos de implementação (`.c`).
- `data/`: Contém arquivos de dados (`.txt`).

## Como Iniciar o Projeto
### Pré-requisitos
- Clang
- Make
- Biblioteca SQLite3 (para a próxima versão)

### Passos para Compilar e Executar
1. Clone o repositório:
    ```sh
    git clone https://github.com/FranciscoTei/gestor-escolar.git
    cd gestor-escolar
    ```

2. Compile o projeto usando o Makefile sem parâmetros:
    ```sh
    make
    ```

3. Execute o programa:
    ```sh
    ./main
    ```

### Limpeza de Arquivos Compilados
Para limpar os arquivos compilados, use o comando:
```sh
make clean
```
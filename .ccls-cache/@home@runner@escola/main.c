#include <stdio.h>
#include <stdlib.h>
#include "include/professor.h"
#include "include/aluno.h"

void menu() {
    printf("\n=== Escolha uma opção ===\n");
    printf("1 - Cadastrar alunos 📝\n");
    printf("2 - Listar alunos 📓\n");
    printf("3 - Alterar média ✏️\n");
    printf("4 - Deletar aluno ✂️\n");
    printf("5 - Melhor aluno 🏅\n");
    printf("6 - Aprovados 📊\n");
    printf("0 - Sair ❌\n");
    printf("=========================\n▶️ ");
}

int main() {
    int qtd = 0;
    int option = -1;
    int loggedIn = 0;
    struct Aluno v[MAX_ALUNOS];
    struct Professor professor;

    boasVindas();

    int opcao = -1;


    while (!loggedIn) {
        printf("\nEscolha uma opção:\n");
        printf("1 - Login\n");
        printf("2 - Cadastrar Professor\n");
        printf("0 - Sair\n");
        printf("=========================\n");
        scanf("%d", &option);

        switch (option) {
            case 1:
                loggedIn = login(&professor);
                break;
            case 2:
                loggedIn = cadastrarProfessor(&professor);
                break;
            case 0:
                printf("Saindo do programa.\n");
                return 0;
            default:
                printf("Opção inválida.\n");
        }
    }

    option = -1;

    while (option != 0) {
        menu();
        scanf("%d", &option);
        switch (option) {
            case 1:
                cadastrarAluno(v, &qtd);
                break;
            case 2:
                listarAlunos(v, qtd);
                break;
            case 3:
                atualizarMedia(v, qtd);
                break;
            case 4:
                deletarAluno(v, &qtd);
                break;
            case 5:
                melhorAluno(v, qtd);
                break;
            case 6:
                listarAprovados(v, qtd);
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}
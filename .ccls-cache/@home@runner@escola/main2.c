#include <stdio.h>
#include <stdlib.h>
#include "professor.h"
#include "aluno.h"

void menu() {
    printf("\n=== Escolha uma opção ===\n");
    printf("1 - Cadastrar alunos 📝\n");
    printf("2 - Listar alunos 📓\n");
    printf("3 - Alterar média ✏️\n");
    printf("4 - Deletar aluno ✂️\n");
    printf("5 - Melhor aluno 🏅\n");
    printf("6 - Aprovados 📊\n");
    printf("0 - Sair ❌\n");
    printf("=========================\n");
}

int main() {
    int qtd = 0;
    int option;
    struct Aluno v[MAX_ALUNOS];
    struct Professor professor;

    boasVindas();

    printf("\n=== Menu Principal ===\n");
    printf("1 - Fazer login\n");
    printf("2 - Cadastrar novo professor\n");
    printf("0 - Sair\n");
    printf("=======================\n");

    int opcao;
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            if (login(&professor)) {
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
            }
            break;
        case 2:
            cadastrarProfessor(&professor);
            break;
        case 0:
            printf("Saindo do programa.\n");
            break;
        default:
            printf("Opção inválida.\n");
    }

    return 0;
}
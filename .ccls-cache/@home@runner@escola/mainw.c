#include <stdio.h>
#include <stdlib.h>

struct Aluno {
    char nome[10];
    int mat;
    float media;
};

void cadastrar(struct Aluno* v, int* qtd) {
    printf("informe os dados do %dº aluno: \n", *qtd+1);
    scanf("%d %s %f", &v[*qtd].mat, v[*qtd].nome, &v[*qtd].media);
    *qtd = *qtd + 1;
}

void listar(struct Aluno* v, int qtd) {
    int i;
    printf("Tabela de alunos cadastrados: \n");
    for (i = 0; i < qtd; i++) {
        printf("Aluno: %d %s %f\n", v[i].mat, v[i].nome, v[i].media);
    }
}

void update (struct Aluno*v, int qtd) {
    int mat;
    int i;
    char confirmar;
    int updated = 0;

    printf("informe a matricula do aluno: \n");
    scanf("%d", &mat);
    for (i = 0; i < qtd; i++) {
        if (v[i].mat == mat) {
            updated = 1;
            printf("Alterando a nota do aluno %s. Confirmar? S/n.\n", v[i].nome);
            scanf(" %c", &confirmar);
            if (confirmar == 'S') {
            printf("Digite a nota do aluno.");
            scanf("%f", &v[i].media);
            }
        }
    }
    if (updated == 0) {
        printf("Aluno não encontrado.\n");
    }
}

void deletar (struct Aluno*v, int *qtd) {
    int mat;
    int i;
    char confirmar;
    int deleted = 0;
    printf("informe a matricula do aluno que deseja deletar: \n");
    scanf("%d", &mat);
    for (i = 0; i < *qtd; i++) {
        if (v[i].mat == mat) {
            deleted = 1;
            printf("Deletando o aluno %s do sistema. confirmar? S/n\n", v[i].nome);
            scanf(" %c", &confirmar);
            if (confirmar == 'S') {
                printf("Aluno deletado com sucesso.\n");
            }
        }
    }
    if (deleted == 0) {
        printf("Aluno não encontrado.\n");
    }
}

void menu() {
    printf("=== Escolha uma opção ===\n");
    printf("1 - Cadastrar alunos\n");
    printf("2 - Listar alunos\n");
    printf("3 - Alterar média\n");
    printf("4 - Deletar aluno\n");
    printf("0 - sair\n");
    printf("====================\n");
}

int main() {
    //!showMemory(start=65520)
    int qtd;
    qtd = 0;
    int option;
    menu();

    struct Aluno v[2];

    scanf("%d", &option);
    switch (option) {
        case 1:
            cadastrar(v, &qtd);
            break;
        case 2:
            listar(v, qtd);
            break;
        case 3:
            update(v, qtd);
            break;
        case 4:
            deletar(v, &qtd);
            break;
        menu();
        scanf("%d", &option);
    }

    return 0;
}
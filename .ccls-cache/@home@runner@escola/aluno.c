#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

void cadastrarAluno(struct Aluno* v, int* qtd) {
    int i;
    char input[20];
    if (*qtd >= MAX_ALUNOS) {
        printf("Limite de alunos atingido.\n");
        return;
    }
    printf("Deseja cadastrar quantos alunos? (máximo disponível: %d)\n▶️ ", MAX_ALUNOS - *qtd);
    scanf("%d", &i);
    if (*qtd + i > MAX_ALUNOS) {
        printf("‼️ Você só pode cadastrar mais %d alunos.\n", MAX_ALUNOS - *qtd);
        i = MAX_ALUNOS - *qtd;
    }
    printf("Digite 'cancelar' a qualquer momento para interromper\n");
    for (int j = 0; j < i; j++) {
        printf("Informe os dados do %dº aluno (matricula nome media): \n▶️ ", j+1);
        scanf(" %[^\n]", input);

        if (strcmp(input, "cancelar") == 0) {
            printf("\n❌ Cadastro cancelado.\n");
            return;
        }
        if (sscanf(input, "%d %s %f", &v[*qtd].mat, v[*qtd].nome, &v[*qtd].media) != 3) {
            printf("\n⚠️ Entrada inválida. Por favor, digite a matrícula, nome e média corretamente separados por espaços.\n\n");
            j--;
            continue;
        }
        (*qtd)++;
    }
    printf("\n✅ Cadastro efetuado com sucesso.\n");
}

void listarAlunos(struct Aluno* v, int qtd) {
    printf("\nTabela de alunos cadastrados: \n");
    for (int i = 0; i < qtd; i++) {
        printf("Aluno: %d %s %.2f\n", v[i].mat, v[i].nome, v[i].media);
    }
}

void atualizarMedia(struct Aluno* v, int qtd) {
    int mat;
    char confirmar;
    int updated = 0;

    printf("Informe a matrícula do aluno: \n▶️ ");
    scanf("%d", &mat);
    for (int i = 0; i < qtd; i++) {
        if (v[i].mat == mat) {
            updated = 1;
            printf("Alterando a nota do aluno %s. Confirmar? S/n.\n▶️ ", v[i].nome);
            scanf(" %c", &confirmar);
            if (confirmar == 'S' || confirmar == 's') {
                printf("Digite a nova nota do aluno.\n▶️ ");
                scanf("%f", &v[i].media);
            }
            break;
        }
    }
    if (!updated) {
        printf("\n⚠️ Aluno não encontrado.\n");
    }
}

void deletarAluno(struct Aluno* v, int* qtd) {
    int mat;
    char confirmar;
    int deleted = 0;

    printf("Informe a matrícula do aluno que deseja deletar: \n▶️ ");
    scanf("%d", &mat);

    for (int i = 0; i < *qtd; i++) {
        if (v[i].mat == mat) {
            printf("Deletando o aluno %s do sistema. Confirmar? S/n\n▶️ ", v[i].nome);
            scanf(" %c", &confirmar);
            if (confirmar == 'S' || confirmar == 's') {
                for (int j = i; j < *qtd - 1; j++) {
                    v[j] = v[j + 1];
                }
                (*qtd)--;
                deleted = 1;
                printf("\n✅ Aluno deletado com sucesso.\n");
            } else {
                printf("❕ Aluno não deletado.\n");
            }
            break;
        }
    }

    if (!deleted) {
        printf("\n🔎 Aluno não encontrado.\n");
    }
}

void melhorAluno(struct Aluno* v, int qtd) {
    if (qtd == 0) {
        printf("\n📤 Nenhum aluno cadastrado.\n");
        return;
    }

    float melhor_media = 0;
    for (int i = 0; i < qtd; i++) {
        if (v[i].media > melhor_media) {
            melhor_media = v[i].media;
        }
    }

    printf("Alunos com melhor nota: \n");
    for (int i = 0; i < qtd; i++) {
        if (v[i].media == melhor_media) {
            printf("%d, %s, %.2f\n", v[i].mat, v[i].nome, v[i].media);
        }
    }
}

void listarAprovados(struct Aluno* v, int qtd) {
    if (qtd == 0) {
        printf("\n📤 Nenhum aluno cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (v[i].media < v[j].media) {
                struct Aluno temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }

    printf("\nAlunos ordenados por melhor nota: \n");
    for (int i = 0; i < qtd; i++) {
        printf("%d %s %.2f ", v[i].mat, v[i].nome, v[i].media);
        if (v[i].media >= 7) {
            printf("APROVADO\n");
        } else {
            printf("REPROVADO\n");
        }
    }
}
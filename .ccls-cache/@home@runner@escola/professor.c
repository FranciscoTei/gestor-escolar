#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "professor.h"

void boasVindas() {
    printf("\n\x1b[32m=== Bem-vindo ao Sistema Integrado de Gestão de Alunos ===\n");
    printf("         Universidade Federal Rural do Semi-Árido       \n");
    printf("==========================================================\n\x1b[34m");
}

int login(struct Professor* professor) {
    char nome[MAX_NOME];
    char senha[MAX_SENHA];
    FILE *file;
    FILE *log;
    time_t tempo = time(NULL);

    printf("\n=== Login ===\n");
    printf("Nome: ");
    scanf(" %[^\n]", nome);
    printf("Senha: ");
    scanf(" %[^\n]", senha);

    file = fopen("professores.txt", "r");
    if (file == NULL) {
        printf("\n❌ Não foi possível abrir o arquivo de credenciais.\n");
        return 0;
    }

    while (fscanf(file, "%s %s %s", professor->nome, professor->email, professor->senha) != EOF) {
        if (strcmp(professor->nome, nome) == 0 && strcmp(professor->senha, senha) == 0) {
            printf("\n✅ Bem-vindo, Professor %s!\n", professor->nome);
            fclose(file);

            log = fopen("logs.txt", "a");
            if (log == NULL) {
                printf("\n❌ Não foi possível abrir o arquivo de logs.\n");
                return 0;
            }
            fprintf(log, "Professor %s efetuou login em %s", professor->nome, ctime(&tempo));
            fclose(log);

            return 1;
        }
    }

    printf("\n❌ Nome ou senha incorretos. Tente novamente.\n");
    fclose(file);
    return 0;
}


bool validarEmail(const char *email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');
    return at != NULL && dot != NULL && at < dot;
}

int cadastrarProfessor(struct Professor* professor) {
    FILE *file;
    char email[MAX_EMAIL];

    printf("\n=== Cadastro de Professor ===\n");
    printf("Nome: ");
    scanf(" %[^\n]", professor->nome);
    printf("Email: ");
    scanf(" %[^\n]", email);
    printf("Senha: ");
    scanf(" %[^\n]", professor->senha);

    if (!validarEmail(email)) {
        printf("\n❌ Digite um email válido.\n");
        return 0;
    }

    file = fopen("professores.txt", "a+");
    if (file == NULL) {
        printf("\n❌ Não foi possível abrir o arquivo de credenciais.\n");
        return 0;
    }

    char nome_lido[MAX_NOME];
    char email_lido[MAX_EMAIL];
    char senha_lida[MAX_SENHA];

    while (fscanf(file, "%s %s %s", nome_lido, email_lido, senha_lida) != EOF) {
        if (strcmp(email_lido, email) == 0) {
            printf("\n❌ Email já registrado.\n");
            fclose(file);
            return 0;
        }
    }

    strcpy(professor->email, email);

    fprintf(file, "%s %s %s\n", professor->nome, professor->email, professor->senha);
    fclose(file);

    printf("\n✅ Cadastro efetuado com sucesso.\n");
    printf("\n Bem-vindo, Professor %s!\n", professor->nome);
    return 1;
}
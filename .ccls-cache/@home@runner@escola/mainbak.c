#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Aluno {
    char nome[10];
    int mat;
    float media;
};

struct Professor {
    char nome[30];
    char senha[20];
};

void cadastrarAluno(struct Aluno* v, int* qtd) {
    int i;
    char input[20];
    if (*qtd >= 5) {
        printf("Limite de alunos atingido.\n");
        return;
    }
    printf("Deseja cadastrar quantos alunos? (máximo disponível: %d)\n▶️ ", 5 - *qtd);
    scanf("%d", &i);
    if (*qtd + i > 5) {
        printf("‼️ Você só pode cadastrar mais %d alunos.\n", 5 - *qtd);
        i = 5 - *qtd;
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
        } else{
            printf("REPROVADO\n");
        }
    }
}

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

int login(struct Professor* professor) {
    char nome[30];
    char senha[20];
    FILE *file;

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

    while (fscanf(file, "%s %s", professor->nome, professor->senha) != EOF) {
        if (strcmp(professor->nome, nome) == 0 && strcmp(professor->senha, senha) == 0) {
            printf("\n✅ Bem-vindo, Professor %s!\n", professor->nome);
            fclose(file);
            return 1;
        }
    }

    printf("\n❌ Nome ou senha incorretos. Tente novamente.\n");
    fclose(file);
    return 0;
}

void cadastrarProfessor(struct Professor* professor) {
    FILE *file;

    printf("\n=== Cadastro de Professor ===\n");
    printf("Nome: ");
    scanf(" %[^\n]", professor->nome);
    printf("Senha: ");
    scanf(" %[^\n]", professor->senha);

    file = fopen("professores.txt", "a");
    if (file == NULL) {
        printf("\n❌ Não foi possível abrir o arquivo de credenciais.\n");
        return;
    }

    fprintf(file, "%s %s\n", professor->nome, professor->senha);
    fclose(file);

    printf("\n✅ Cadastro efetuado com sucesso.\n");
}

void boasVindas() {
    printf("\n  === Bem-vindo ao Sistema de Gestão de Alunos ===\n");
    printf("       Universidade Federal Rural do Semi-Árido       \n");
    printf("=====================================================\n");
}

int main() {
    int qtd = 0;
    int option = -1;
    int loggedIn = 0;
    struct Aluno v[5];
    struct Professor professor;

    boasVindas();

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
                cadastrarProfessor(&professor);
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

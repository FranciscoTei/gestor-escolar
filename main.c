#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/forum.h"
#include "include/login.h"
#include "include/utils.h"
#include "include/professor.h"


void menuPrincipal(struct Usuario usuario);
void menuForum(struct Usuario usuario, int turma_id);

int main() {
    struct Usuario usuario;

    if (login(&usuario)) {
        if (strcmp(usuario.tipo, "professor") == 0) {
            menuProfessor(usuario.id);
        } else if (strcmp(usuario.tipo, "aluno") == 0) {
            // Menu para alunos pode ser implementado aqui
        } else {
            printf("Tipo de usuário desconhecido!\n");
        }
    } else {
        printf("Falha no login.\n");
    }
    menuPrincipal(usuario);

    return 0;
}

void menuPrincipal(struct Usuario usuario) {
    int opcao;
    int turma_id;

    do {
        printf("\n=== Menu Principal ===\n");
        printf("1. Ver Fórum\n");
        printf("2. Sair\n");
        printf("Escolha uma opção: ");

        scanf("%d", &opcao);
        //limpar_terminal();
        switch (opcao) {
            case 1:
                printf("Digite o ID da turma: ");
                scanf("%d", &turma_id);
                menuForum(usuario, turma_id);
                break;
            case 2:
                printf("Saindo...\n");
                exit(0);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 2);
}

void menuForum(struct Usuario usuario, int turma_id) {
    int opcao;
    int pagina = 1;

    do {
        listarForum(usuario, turma_id, pagina);
        printf("\n=== Menu do Fórum ===\n");
        printf("1. Próxima Página\n");
        printf("2. Anterior Página\n");
        printf("3. Abrir Tópico\n");
        if (strcmp(usuario.tipo, "professor") == 0 || strcmp(usuario.tipo, "monitor") == 0) {
            printf("4. Criar Tópico\n");
            printf("5. Editar Tópico\n");
            printf("6. Deletar Tópico\n");
        }
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                pagina++;
                break;
            case 2:
                if (pagina > 1) {
                    pagina--;
                }
                break;
            case 3:
                {
                    int forum_id;
                    printf("Digite o ID do tópico: ");
                    scanf("%d", &forum_id);
                    verTopico(usuario, forum_id);
                }
                break;
            case 4:
                if (strcmp(usuario.tipo, "professor") == 0 || strcmp(usuario.tipo, "monitor") == 0) {
                    char titulo[100];
                    char mensagem[500];
                    printf("Digite o título do tópico: ");
                    scanf(" %[^\n]", titulo);
                    printf("Digite a mensagem do tópico: ");
                    scanf(" %[^\n]", mensagem);
                    criarForum(usuario, turma_id, titulo, mensagem);
                }
                break;
            case 5:
                if (strcmp(usuario.tipo, "professor") == 0) {
                    int forum_id;
                    char novo_titulo[100];
                    char nova_mensagem[500];
                    printf("Digite o ID do tópico: ");
                    scanf("%d", &forum_id);
                    printf("Digite o novo título do tópico: ");
                    scanf(" %[^\n]", novo_titulo);
                    printf("Digite a nova mensagem do tópico: ");
                    scanf(" %[^\n]", nova_mensagem);
                    editarForum(usuario, forum_id, novo_titulo, nova_mensagem);
                }
                break;
            case 6:
                if (strcmp(usuario.tipo, "professor") == 0 || strcmp(usuario.tipo, "monitor") == 0) {
                    int forum_id;
                    printf("Digite o ID do tópico: ");
                    scanf("%d", &forum_id);
                    deletarForum(usuario, forum_id);
                }
                break;
            case 0:
                return;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

void verTopico(struct Usuario usuario, int forum_id) {
    int opcao;
    int pagina = 1;

    do {
        listarComentarios(usuario, forum_id, pagina);
        printf("\n=== Menu do Tópico ===\n");
        printf("1. Próxima Página\n");
        printf("2. Anterior Página\n");
        printf("3. Comentar\n");
        printf("0. Voltar ao Menu do Fórum\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                pagina++;
                break;
            case 2:
                if (pagina > 1) {
                    pagina--;
                }
                break;
            case 3:
                {
                    char mensagem[500];
                    printf("Digite a mensagem: ");
                    scanf(" %[^\n]", mensagem);
                    postarForum(usuario, forum_id, mensagem);
                }
                break;
            case 0:
                return;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

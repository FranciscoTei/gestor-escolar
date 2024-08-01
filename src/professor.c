#include "../include/professor.h"
#include <stdio.h>

void menuProfessor(int usuario_id) {
    int opcao;
    do {
        printf("\nMenu Professor\n");
        printf("1. Turmas\n");
        printf("2. Horários\n");
        printf("3. Configurações\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                gerenciarTurmas(usuario_id);
                break;
            case 2:
                gerenciarHorarios(usuario_id);
                break;
            case 3:
                configuracoesProfessor(usuario_id);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

void gerenciarTurmas(int usuario_id) {
    listarTurmas(usuario_id);
}

void gerenciarHorarios(int usuario_id) {
    printf("Gerenciar Horários - Em Desenvolvimento\n");
}

void configuracoesProfessor(int usuario_id) {
    printf("Configurações do Professor - Em Desenvolvimento\n");
}

void listarTurmas(int usuario_id) {
    printf("\nListar Turmas - Em Desenvolvimento\n");
    int turma_id = 1; // Exemplo de turma_id
    menuTurma(turma_id);
}

void menuTurma(int turma_id) {
    int opcao;
    do {
        printf("\nMenu Turma %d\n", turma_id);
        printf("1. Alunos\n");
        printf("2. Atividades\n");
        printf("3. Avisos\n");
        printf("4. Fórum\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                gerenciarAlunos(turma_id);
                break;
            case 2:
                gerenciarAtividades(turma_id);
                break;
            case 3:
                gerenciarAvisos(turma_id);
                break;
            case 4:
                gerenciarForum(turma_id);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

void gerenciarAlunos(int turma_id) {
    int opcao;
    do {
        printf("\nGerenciar Alunos\n");
        printf("1. Listar Alunos\n");
        printf("2. Cadastrar Notas\n");
        printf("3. Ver Notas\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarAlunos(turma_id);
                break;
            case 2:
                cadastrarNotas(turma_id);
                break;
            case 3:
                verNotas(turma_id);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

void listarAlunos(int turma_id) {
    printf("Listar Alunos - Em Desenvolvimento\n");
}

void cadastrarNotas(int turma_id) {
    printf("Cadastrar Notas - Em Desenvolvimento\n");
}

void verNotas(int turma_id) {
    printf("Ver Notas - Em Desenvolvimento\n");
}

void gerenciarAtividades(int turma_id) {
    int opcao;
    do {
        printf("\nGerenciar Atividades\n");
        printf("1. Listar Atividades\n");
        printf("2. Criar Nova Atividade\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarAtividades(turma_id);
                break;
            case 2:
                criarAtividade(turma_id);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

void listarAtividades(int turma_id) {
    printf("Listar Atividades - Em Desenvolvimento\n");
}

void abrirAtividade(int atividade_id) {
    printf("Abrir Atividade - Em Desenvolvimento\n");
}

void criarAtividade(int turma_id) {
    printf("Criar Atividade - Em Desenvolvimento\n");
}

void gerenciarAvisos(int turma_id) {
    int opcao;
    do {
        printf("\nGerenciar Avisos\n");
        printf("1. Listar Avisos\n");
        printf("2. Criar Novo Aviso\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarAvisos(turma_id);
                break;
            case 2:
                criarAviso(turma_id);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

void listarAvisos(int turma_id) {
    printf("Listar Avisos - Em Desenvolvimento\n");
}

void abrirAviso(int aviso_id) {
    printf("Abrir Aviso - Em Desenvolvimento\n");
}

void criarAviso(int turma_id) {
    printf("Criar Aviso - Em Desenvolvimento\n");
}

void gerenciarForum(int turma_id) {
    int opcao;
    do {
        printf("\nGerenciar Fórum\n");
        printf("1. Listar Tópicos\n");
        printf("2. Criar Novo Tópico\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listarTopicos(turma_id);
                break;
            case 2:
                criarTopico(turma_id);
                break;
            case 0:
                printf("Voltando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

void listarTopicos(int turma_id) {
    printf("Listar Tópicos - Em Desenvolvimento\n");
}

void abrirTopico(int topico_id) {
    printf("Abrir Tópico - Em Desenvolvimento\n");
}

void criarTopico(int turma_id) {
    printf("Criar Tópico - Em Desenvolvimento\n");
}

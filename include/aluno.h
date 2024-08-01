#ifndef ALUNO_H
#define ALUNO_H

#define MAX_NOME_ALUNO 10
#define MAX_ALUNOS 5

struct Aluno {
    char nome[MAX_NOME_ALUNO];
    int mat;
    float media;
};

void cadastrarAluno(struct Aluno* v, int* qtd);
void listarAlunos(struct Aluno* v, int qtd);
void atualizarMedia(struct Aluno* v, int qtd);
void deletarAluno(struct Aluno* v, int* qtd);
void melhorAluno(struct Aluno* v, int qtd);
void listarAprovados(struct Aluno* v, int qtd);

#endif
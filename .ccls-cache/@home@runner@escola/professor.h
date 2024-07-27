#ifndef PROFESSOR_H
#define PROFESSOR_H

#define MAX_NOME 30
#define MAX_EMAIL 80
#define MAX_SENHA 20
#include <stdbool.h>
struct Professor {
  char nome[MAX_NOME];
  char email[MAX_EMAIL];
  char senha[MAX_SENHA];
};

void boasVindas();
int login(struct Professor *professor);
int cadastrarProfessor(struct Professor *professor);
bool validarEmail(const char *email);

#endif
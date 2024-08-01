#ifndef LOGIN_H
#define LOGIN_H

#define MAX_NOME 30
#define MAX_EMAIL 80
#define MAX_SENHA 20
#define MAX_STATUS 15
#include <stdbool.h>

struct Usuario {
  char nome[MAX_NOME];
  char email[MAX_EMAIL];
  char senha[MAX_SENHA];
  char tipo[MAX_STATUS];
  int id;
};

void boasVindas();
int login(struct Usuario *usuario);
int cadastrarUsuario(struct Usuario *usuario);
bool validarEmail(const char *email);

#endif
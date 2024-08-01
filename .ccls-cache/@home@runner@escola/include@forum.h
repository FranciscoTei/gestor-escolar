#ifndef FORUM_H
#define FORUM_H
#include "../include/login.h"

void criarForum(struct Usuario usuario, int turma_id, const char *titulo, const char *mensagem);
void postarForum(struct Usuario usuario, int forum_id, const char *mensagem);
void editarForum(struct Usuario usuario, int forum_id, const char *novo_titulo, const char *nova_mensagem);
void deletarForum(struct Usuario usuario, int forum_id);
void listarForum(struct Usuario usuario, int turma_id, int pagina);
void listarComentarios(struct Usuario usuario, int forum_id, int pagina);
void verTopico(struct Usuario usuario, int forum_id);

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sqlite3.h>
#include "../include/login.h"

void boasVindas() {
    printf("\n\x1b[32m=== Bem-vindo ao Sistema Integrado de Gestão de Alunos ===\n");
    printf("         Universidade Federal Rural do Semi-Árido       \n");
    printf("==========================================================\n\x1b[34m");
}

bool validarEmail(const char *email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');
    return at != NULL && dot != NULL && at < dot;
}

int login(struct Usuario* usuario) {
    char nome[MAX_NOME];
    char senha[MAX_SENHA];
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT nome, email, senha, tipo FROM usuario WHERE nome = ? AND senha = ?";

    printf("\n=== Login ===\n");
    printf("Nome: ");
    scanf(" %[^\n]", nome);
    printf("Senha: ");
    scanf(" %[^\n]", senha);

    if (sqlite3_open("data/database/escola.db", &db) != SQLITE_OK) {
        printf("\n❌ Não foi possível abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("\n❌ Falha ao preparar a consulta SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, nome, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, senha, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        strcpy(usuario->nome, (const char*)sqlite3_column_text(stmt, 0));
        strcpy(usuario->email, (const char*)sqlite3_column_text(stmt, 1));
        strcpy(usuario->senha, (const char*)sqlite3_column_text(stmt, 2));
        strcpy(usuario->tipo, (const char*)sqlite3_column_text(stmt, 3));
        printf("\n✅ Bem-vindo, %s %s!\n", usuario->tipo, usuario->nome);

        // Log the login attempt
        FILE *log = fopen("logs.txt", "a");
        if (log != NULL) {
            time_t tempo = time(NULL);
            fprintf(log, "%s %s efetuou login em %s", usuario->tipo, usuario->nome, ctime(&tempo));
            fclose(log);
        } else {
            printf("\n❌ Não foi possível abrir o arquivo de logs.\n");
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    } else {
        printf("\n❌ Nome ou senha incorretos. Tente novamente.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

int cadastrarUsuario(struct Usuario* usuario) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO usuario (nome, email, senha, tipo) VALUES (?, ?, ?, ?)";
    char email[MAX_EMAIL];

    printf("\n=== Cadastro de Usuário ===\n");
    printf("Nome: ");
    scanf(" %[^\n]", usuario->nome);
    printf("Email: ");
    scanf(" %[^\n]", email);
    printf("Senha: ");
    scanf(" %[^\n]", usuario->senha);
    printf("Tipo (aluno/professor/monitor/coordenador/administrador): ");
    scanf(" %[^\n]", usuario->tipo);

    if (!validarEmail(email)) {
        printf("\n❌ Digite um email válido.\n");
        return 0;
    }

    if (sqlite3_open("data/database/escola.db", &db) != SQLITE_OK) {
        printf("\n❌ Não foi possível abrir o banco de dados.\n");
        return 0;
    }

    const char *checkEmailSQL = "SELECT email FROM usuario WHERE email = ?";
    if (sqlite3_prepare_v2(db, checkEmailSQL, -1, &stmt, NULL) != SQLITE_OK) {
        printf("\n❌ Falha ao preparar a consulta SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("\n❌ Email já registrado.\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    sqlite3_finalize(stmt);

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("\n❌ Falha ao preparar a consulta SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    sqlite3_bind_text(stmt, 1, usuario->nome, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, usuario->senha, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, usuario->tipo, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("\n❌ Falha ao cadastrar usuário.\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    strcpy(usuario->email, email);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    printf("\n✅ Cadastro efetuado com sucesso.\n");
    printf("\n Bem-vindo, %s %s!\n", usuario->tipo, usuario->nome);
    return 1;
}

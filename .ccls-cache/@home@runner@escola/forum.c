#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int sql() {
    sqlite3 *db;
    char *errmsg = 0;
    int rc;

    rc = sqlite3_open("meubanco.db", &db);
    if (rc) {
        fprintf(stderr, "Não foi possível abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Banco de dados aberto com sucesso\n");
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS Professores("  \
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
                      "Nome TEXT NOT NULL," \
                      "Email TEXT NOT NULL," \
                      "Senha TEXT NOT NULL);";

    rc = sqlite3_exec(db, sql, 0, 0, &errmsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabela: %s\n", errmsg);
        sqlite3_free(errmsg);
    } else {
        fprintf(stdout, "Tabela criada com sucesso\n");
    }

    sql = "INSERT INTO Professores (Nome, Email, Senha) "  \
          "VALUES ('John Doe', 'john@example.com', 'password');";

    rc = sqlite3_exec(db, sql, 0, 0, &errmsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao inserir dados: %s\n", errmsg);
        sqlite3_free(errmsg);
    } else {
        fprintf(stdout, "Dados inseridos com sucesso\n");
    }

    sqlite3_stmt *stmt;
    sql = "SELECT * FROM Professores;";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao buscar dados: %s\n", sqlite3_errmsg(db));
        return(0);
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        printf("ID: %d | Nome: %s | Email: %s\n", 
                sqlite3_column_int(stmt, 0), 
                sqlite3_column_text(stmt, 1), 
                sqlite3_column_text(stmt, 2));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

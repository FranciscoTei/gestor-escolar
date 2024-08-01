#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sqlite3.h>
#include "../include/login.h"

void print_sqlite_error(sqlite3 *db, const char *file, int line) {
    printf("❌ Falha ao preparar a consulta SQL: %s\nArquivo: %s, Linha: %d\n", sqlite3_errmsg(db), file, line);
}

#define PRINT_SQLITE_ERROR(db) print_sqlite_error(db, __FILE__, __LINE__)

void criarForum(struct Usuario usuario, int turma_id, const char *titulo, const char *mensagem) {
    if (strcmp(usuario.tipo, "professor") != 0 && strcmp(usuario.tipo, "monitor") != 0) {
        printf("❌ Apenas professores e monitores podem criar tópicos no fórum.\n");
        return;
    }

    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO forums (turma_id, professor_id, titulo, descricao, data_criacao) VALUES (?, ?, ?, ?, datetime('now'))";

    if (sqlite3_open("data/database/escola.db", &db) != SQLITE_OK) {
        PRINT_SQLITE_ERROR(db);
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        PRINT_SQLITE_ERROR(db);
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmt, 1, turma_id);
    sqlite3_bind_int(stmt, 2, usuario.id);
    sqlite3_bind_text(stmt, 3, titulo, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, mensagem, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("❌ Falha ao criar tópico no fórum.\n");
        PRINT_SQLITE_ERROR(db);
    } else {
        printf("✅ Tópico criado com sucesso.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void postarForum(struct Usuario usuario, int forum_id, const char *mensagem) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO comentarios_forum (forum_id, usuario_id, comentario, data_comentario) VALUES (?, ?, ?, datetime('now'))";

    if (sqlite3_open("data/database/escola.db", &db) != SQLITE_OK) {
        PRINT_SQLITE_ERROR(db);
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        PRINT_SQLITE_ERROR(db);
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmt, 1, forum_id);
    sqlite3_bind_int(stmt, 2, usuario.id);
    sqlite3_bind_text(stmt, 3, mensagem, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("❌ Falha ao postar comentário no fórum.\n");
        PRINT_SQLITE_ERROR(db);
    } else {
        printf("✅ Comentário postado com sucesso.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void editarForum(struct Usuario usuario, int forum_id, const char *novo_titulo, const char *nova_mensagem) {
    if (strcmp(usuario.tipo, "professor") != 0) {
        printf("❌ Apenas professores podem editar tópicos no fórum.\n");
        return;
    }

    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE forums SET titulo = ?, descricao = ? WHERE id = ? AND professor_id = ?";

    if (sqlite3_open("data/database/escola.db", &db) != SQLITE_OK) {
        PRINT_SQLITE_ERROR(db);
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        PRINT_SQLITE_ERROR(db);
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, novo_titulo, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, nova_mensagem, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, forum_id);
    sqlite3_bind_int(stmt, 4, usuario.id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("❌ Falha ao editar tópico no fórum.\n");
        PRINT_SQLITE_ERROR(db);
    } else {
        printf("✅ Tópico editado com sucesso.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void deletarForum(struct Usuario usuario, int forum_id) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sqlProfessor = "DELETE FROM forums WHERE id = ? AND professor_id = ?";
    const char *sqlMonitor = "DELETE FROM forums WHERE id = ? AND professor_id = ? AND tipo = 'monitor'";

    if (sqlite3_open("data/database/escola.db", &db) != SQLITE_OK) {
        printf("❌ Não foi possível abrir o banco de dados.\n");
        PRINT_SQLITE_ERROR(db);
        return;
    }

    if (strcmp(usuario.tipo, "professor") == 0) {
        if (sqlite3_prepare_v2(db, sqlProfessor, -1, &stmt, NULL) != SQLITE_OK) {
            printf("❌ Falha ao preparar a consulta SQL.\n");
            PRINT_SQLITE_ERROR(db);
            sqlite3_close(db);
            return;
        }
    } else if (strcmp(usuario.tipo, "monitor") == 0) {
        if (sqlite3_prepare_v2(db, sqlMonitor, -1, &stmt, NULL) != SQLITE_OK) {
            printf("❌ Falha ao preparar a consulta SQL.\n");
            PRINT_SQLITE_ERROR(db);
            sqlite3_close(db);
            return;
        }
    } else {
        printf("❌ Apenas professores e monitores podem deletar tópicos no fórum.\n");
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmt, 1, forum_id);
    sqlite3_bind_int(stmt, 2, usuario.id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("❌ Falha ao deletar tópico no fórum.\n");
        PRINT_SQLITE_ERROR(db);
    } else {
        printf("✅ Tópico deletado com sucesso.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void listarForum(struct Usuario usuario, int turma_id, int pagina) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sqlTodos = 
        "SELECT f.id, f.titulo, u.nome AS criador, "
        "(SELECT COUNT(*) FROM comentarios_forum p WHERE p.forum_id = f.id) AS posts, "
        "(SELECT MAX(p.data_comentario) FROM comentarios_forum p WHERE p.forum_id = f.id) AS latest_post_date, "
        "(SELECT u2.nome FROM comentarios_forum p2 JOIN usuario u2 ON p2.usuario_id = u2.id WHERE p2.forum_id = f.id ORDER BY p2.data_comentario DESC LIMIT 1) AS ultimo_post_autor "
        "FROM forums f "
        "JOIN usuario u ON f.professor_id = u.id "
        "WHERE f.turma_id = ? "
        "LIMIT 5 OFFSET ?";

    const char *sqlEspecifico = 
        "SELECT f.id, f.titulo, u.nome AS criador, "
        "(SELECT COUNT(*) FROM comentarios_forum p WHERE p.forum_id = f.id) AS posts, "
        "(SELECT MAX(p.data_comentario) FROM comentarios_forum p WHERE p.forum_id = f.id) AS latest_post_date, "
        "(SELECT u2.nome FROM comentarios_forum p2 JOIN usuario u2 ON p2.usuario_id = u2.id WHERE p2.forum_id = f.id ORDER BY p2.data_comentario DESC LIMIT 1) AS ultimo_post_autor "
        "FROM forums f "
        "JOIN usuario u ON f.professor_id = u.id "
        "WHERE f.turma_id = ? AND f.professor_id = ? "
        "LIMIT 5 OFFSET ?";
    int offset = (pagina - 1) * 5;

    if (sqlite3_open("data/database/escola.db", &db) != SQLITE_OK) {
        PRINT_SQLITE_ERROR(db);
        return;
    }

    if (turma_id == 0) {
        if (sqlite3_prepare_v2(db, sqlTodos, -1, &stmt, NULL) != SQLITE_OK) {
            printf("❌ Falha ao preparar a consulta SQL.\n");
            PRINT_SQLITE_ERROR(db);
            sqlite3_close(db);
            return;
        }
        sqlite3_bind_int(stmt, 1, usuario.id);
        sqlite3_bind_int(stmt, 2, offset);
    } else {
        if (sqlite3_prepare_v2(db, sqlEspecifico, -1, &stmt, NULL) != SQLITE_OK) {
            PRINT_SQLITE_ERROR(db);
            sqlite3_close(db);
            return;
        }
        sqlite3_bind_int(stmt, 1, turma_id);
        sqlite3_bind_int(stmt, 2, usuario.id);
        sqlite3_bind_int(stmt, 3, offset);
    }

    printf("\n=== Lista de Tópicos do Fórum ===\n");
    printf("ID  %-30s %-6s %-12s\n", "TÍTULO", "POSTS", "LATEST POST");
    int found = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char *titulo = (const char*)sqlite3_column_text(stmt, 1);
        const char *criador = (const char*)sqlite3_column_text(stmt, 2);
        int posts = sqlite3_column_int(stmt, 3);
        const char *latest_post_date = (const char*)sqlite3_column_text(stmt, 4);
        const char *ultimo_post_autor = (const char*)sqlite3_column_text(stmt, 5);

        // Truncate title if it's longer than 30 characters
        char truncated_title[31];
        if (strlen(titulo) > 30) {
            strncpy(truncated_title, titulo, 28);
            truncated_title[28] = '.';
            truncated_title[29] = '.';
            truncated_title[30] = '\0';
        } else {
            strncpy(truncated_title, titulo, 30);
            truncated_title[30] = '\0';
        }

        printf("%02d  %-30s %-6d %-12s\n", id, truncated_title, posts, latest_post_date ? latest_post_date : "N/A");
        printf("    ↳created by: %-20s ↳ %s\n", criador, ultimo_post_autor ? ultimo_post_autor : criador);
        found = 1;
    }
    if (!found) {
        printf("\n    Nenhum tópico encontrado.\n");
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void listarComentarios(struct Usuario usuario, int forum_id, int pagina) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, usuario_id, comentario, data_comentario FROM comentarios_forum WHERE forum_id = ? LIMIT 5 OFFSET ?";
    int offset = (pagina - 1) * 5;

    if (sqlite3_open("escola.db", &db) != SQLITE_OK) {
        printf("❌ Não foi possível abrir o banco de dados.\n");
        PRINT_SQLITE_ERROR(db);
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        PRINT_SQLITE_ERROR(db);
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmt, 1, forum_id);
    sqlite3_bind_int(stmt, 2, offset);

    printf("=== Comentários do Tópico ===\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        int usuario_id = sqlite3_column_int(stmt, 1);
        const char *mensagem = (const char*)sqlite3_column_text(stmt, 2);
        const char *data_comentario = (const char*)sqlite3_column_text(stmt, 3);

        printf("ID: %d\nUsuário ID: %d\nMensagem: %s\nData do Comentário: %s\n\n", id, usuario_id, mensagem, data_comentario);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
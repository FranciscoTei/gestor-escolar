// data/database/create_tables.c
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#define DB_FILE "data/database/escola.db"
#define SQL_FILE "data/database/models.sql"

int execute_sql_file(sqlite3 *db, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open SQL file: %s\n", filename);
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *sql = (char *)malloc(file_size + 1);
    if (!sql) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return -1;
    }

    size_t bytes_read = fread(sql, 1, file_size, file);
    if (bytes_read != file_size) {
        fprintf(stderr, "Failed to read the entire SQL file\n");
        free(sql);
        fclose(file);
        return -1;
    }
    sql[file_size] = '\0';

    fclose(file);

    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    free(sql);
    return rc;
}

int mainn(void) {
    sqlite3 *db;
    int rc = sqlite3_open(DB_FILE, &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    rc = execute_sql_file(db, SQL_FILE);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute SQL file\n");
    } else {
        printf("Tables created successfully\n");
    }

    sqlite3_close(db);
    return rc;
}

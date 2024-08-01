all: main

CC = clang
override CFLAGS += -g -Wno-everything -pthread -lm

# Adicionando a biblioteca de importação do SQLite
LDFLAGS = -L. -lsqlite3

# Encontrando os arquivos .c e .h no projeto
SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

# Regra para compilar o executável principal
main: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o "$@" $(LDFLAGS)

# Regra para compilar o executável de debug
main-debug: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -O0 $(SRCS) -o "$@" $(LDFLAGS)

# Regra para limpar os arquivos compilados
clean:
	rm -f main main-debug

# Adicionando a regra para criar as tabelas
create-tables: $(SRCS) $(HEADERS)
	@rm -f data/database/escolaa.db
	$(CC) $(CFLAGS) -x c -o /tmp/create_models_temp data/database/create_tables.c -lsqlite3
	/tmp/create_models_temp
	rm -f /tmp/create_models_temp
	
# Regra para inserir dados no banco de dados
insert-data:
	sqlite3 data/database/escola.db < data/database/insert_data.sql

# Regra para criar tabelas e inserir dados
setup: create-tables insert-data
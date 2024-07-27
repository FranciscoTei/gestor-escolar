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

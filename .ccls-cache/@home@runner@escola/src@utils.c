#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#ifdef _WIN32
#include <conio.h>
#define CLEAR_COMMAND "cls"
#else
#include <termios.h>
#define CLEAR_COMMAND "clear"
#endif

static struct termios orig_termios;

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void execute_command(const char *command) {
    system(command);
}

void limpar_terminal() {
    system(CLEAR_COMMAND);
}

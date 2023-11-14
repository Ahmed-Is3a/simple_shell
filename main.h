#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define TOK_DELIMITERS " \t\r\n\a\""
#define BUFF_SIZE 1024
#define MAX_COMMANDS 10
#define MAX_COMMAND_LENGTH 100

extern char *shell;
int main(int argc, char *argv[]);
int pass_betty_check(void);
int execute_args(char *command);
void handle_PATH(char **args);
void handle_multi_commands(char *input);
void display_shell_prompt(void);

#endif

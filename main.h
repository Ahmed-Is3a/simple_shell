#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define TOK_DELIMITERS " \t\r\n\a\""
#define MAX_COMMANDS 10
#define MAX_COMMAND_LENGTH 100

int pass_betty_check(void);
int execute_args(char *command, char *shell);
void handle_multi_commands(char *input, char *shell);
void display_shell_prompt(char *shell);

#endif

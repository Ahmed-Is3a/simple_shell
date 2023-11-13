#include "main.h"

/**
 * handle_multi_commands - handles multipule commands when seperated with (;)
 *
 * @input: the command which the user entered
 * @shell: the shell name (the executable program name)
*/
void handle_multi_commands(char *input, char *shell)
{
	int i;
	char *commands[MAX_COMMANDS];
	char *token;
	int num_of_commands = 0;

	token = strtok(input, ";");
	while (token != NULL && num_of_commands < MAX_COMMANDS)
	{
		commands[num_of_commands++] = strdup(token);
		token = strtok(NULL, ";");
	}

	/*  Execute each command in a separate child process */
	for (i = 0; i < num_of_commands; ++i)
	{
		execute_args(commands[i], shell);
	}
}

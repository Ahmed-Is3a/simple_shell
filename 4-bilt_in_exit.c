#include "main.h"

/**
 * exit_shell - trminate the shell loop
 * @i
*/
void exit_shell(char *command)
{
	/*   Remove newline character */
	command[strcspn(command, "\n")] = '\0';
	if (strcmp(command, "exit") == 0)
		exit(EXIT_SUCCESS);
}

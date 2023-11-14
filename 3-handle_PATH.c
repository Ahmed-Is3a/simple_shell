#include "main.h"

/**
 * handle_PATH - handle the path of the command
 *
 * @args: command arguments
*/
void handle_PATH(char **args, char *shell)
{
	char *path;
	char full_path[BUFF_SIZE];
	char *token;

	/* Get the PATH environment variable */
	path = getenv("PATH");
	if (path == NULL)
	{
		fprintf(stderr, "PATH environment variable not set.\n");
		exit(EXIT_FAILURE);
	}

	/* Tokenize the PATH variable to get individual directories */
	token = strtok(path, ":");
	while (token != NULL)
	{
		/* Construct the full path to the executable */
		snprintf(full_path, sizeof(full_path), "%s/%s", token, args[0]);

		/* execute the command */
		execve(full_path, args, NULL);

		/* If execve fails, try the next directory in PATH */
		token = strtok(NULL, ":");
	}

	/* If we reach here, the command was not found in any directory in PATH */
	perror(shell);
	exit(EXIT_FAILURE);
}

#include "main.h"

/**
 * handle_PATH - handle the path of the command
 *
 * @args: command arguments
 * @shell: shell name
 */
void handle_PATH(char **args, char *shell)
{
	char *path;
	char full_path[BUFF_SIZE];
	char *token, *full_path_ptr;
	char *args_ptr;

	/* Get the PATH environment variable */
	path = getenv("PATH");
	if (path == NULL)
	{
		/* fprintf(stderr, "PATH environment variable not set.\n"); */
		exit(EXIT_FAILURE);
	}

	/* Tokenize the PATH variable to get individual directories */
	token = strtok(path, ":");
	while (token != NULL)
	{
		/* Construct the full path to the executable */
		full_path_ptr = full_path;

		/* Copy the directory path */
		while (*token != '\0')
		{
			*full_path_ptr = *token;
			full_path_ptr++;
			token++;
		}

		/*  Add '/' between directory path and executable name */
		*full_path_ptr = '/';
		full_path_ptr++;

		/*  Copy the executable name */
		args_ptr = args[0];
		while (*args_ptr != '\0')
		{
			*full_path_ptr = *args_ptr;
			full_path_ptr++;
			args_ptr++;
		}

		/* Null-terminate the string */
		*full_path_ptr = '\0';

		/* execute the command */
		execve(full_path, args, NULL);

		/* If execve fails, try the next directory in PATH */
		token = strtok(NULL, ":");
	}

	/* If we reach here, the command was not found in any directory in PATH */
	perror(shell);
	exit(EXIT_FAILURE);
}

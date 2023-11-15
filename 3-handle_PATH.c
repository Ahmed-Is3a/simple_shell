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

	path = getenv("PATH"); /* Get the PATH environment variable */
	if (path == NULL) /* if PATH not set */
		exit(EXIT_FAILURE);

	/* Tokenize the PATH variable to get individual directories */
	token = strtok(path, ":");
	while (token != NULL)
	{
		/* Construct the full path to the executable */
		full_path_ptr = full_path;

		while (*token != '\0') /* Copy the directory path */
		{
			*full_path_ptr = *token;
			full_path_ptr++;
			token++;
		}
		/*  Add '/' between directory path and executable name */
		*full_path_ptr = '/';
		full_path_ptr++;
		args_ptr = args[0]; /*  Copy the executable name */
		while (*args_ptr != '\0')
		{
			*full_path_ptr = *args_ptr;
			full_path_ptr++;
			args_ptr++;
		}
		*full_path_ptr = '\0'; /* Null-terminate the string */
		execve(full_path, args, NULL); /* execute the command */

		/* If execve fails, try the next directory in PATH */
		token = strtok(NULL, ":");
	}
	perror(shell); /* command was not found in any directory in PATH */
	exit(EXIT_FAILURE);
}

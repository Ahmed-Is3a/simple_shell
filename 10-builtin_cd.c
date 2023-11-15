#include "main.h"

/**
 * my_cd - change the current directory
 *
 * @args: command arguments
 * @current_dir: current working directory
 * Return: 1 on success, -1 on failure
 */
int builtin_cd(char **args)
{
	char current_dir[BUFF_SIZE];
	char new_dir[BUFF_SIZE];

	if (strcmp(args[0], "cd") != 0)
		return (-1);

	if (getcwd(current_dir, sizeof(current_dir)) == NULL) /* if fails */
		perror("getcwd");

	if (args[1] == NULL || strcmp(args[1], "~") == 0)
	{
		/*  No argument or argument is "~", change to home directory */
		if (chdir(getenv("HOME")) != 0)
			perror("cd");
	}
	else if (strcmp(args[1], "-") == 0)
	{
		/*  Change to the previous directory */
		if (chdir(current_dir) != 0)
			perror("cd");
	}
	else
	{
		/* Change to the specified directory */
		if (chdir(args[1]) != 0)
			perror("cd");
	}

	/* Update the PWD environment variable */
	if (getcwd(new_dir, sizeof(new_dir)) != NULL)
		setenv("PWD", new_dir, 1);
	else
		perror("getcwd");
	return (1);
}

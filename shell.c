#include "main.h"
#include <sys/wait.h>
#include <string.h>

/**
 * read_line - read a line from stdin
 *
 * Return: pointer that points to a str with the line content
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1) /* if getline fails */
	{
			free(line); /* avoid memory leaks when getline fails */
			perror("error while reading the line from stdin");
			exit(EXIT_FAILURE);
	}
	return (line);
}

/**
 * split_line - split a string into multiple strings
 * @line: string to be splited
 *
 * Return: pointer that points to the new array
 */
char **split_line(char *line)
{
	int bufsize = 64;
	int i = 0;
	int j;
	char **tokens = malloc(bufsize * sizeof(char *));
	char **tmp_tokens;
	char *token;

	if (!tokens)
	{
		perror("allocation error in split_line: tokens\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, TOK_DELIMITERS);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		if (i >= bufsize)
		{
			bufsize += bufsize;
			tmp_tokens = malloc(bufsize * sizeof(char *));
			for (j = 0; j < 64; j++)
			{
				tmp_tokens[i] = tokens[i];
			}
			free(tokens);
			tokens = tmp_tokens;
			free(tmp_tokens);
			if (!tokens)
			{
				perror("reallocation error in split_line: tokens");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOK_DELIMITERS);
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * execute_args - map if command is a builtin or a process
 *
 * @args: command to be executed
 *
 * Return: 1 on sucess, 0 otherwise
 */
int execute_args(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL) /* if no command was entered */
		return (-1);

	/* create a new process */
	pid = fork();
	if (pid ==  0) /* child process created if fork returns 0 */
	{
		/* child process */
		if (execve(args[0], args, NULL) == -1) /* if execve fails to execute new program */
		{
			fprintf(stderr, "%s: error std", args[0]);
			perror("error in execute_args: child process");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0) /* error, fork fail if return negative value */
		perror("error in execute_args: forking");
	else
	{
		/* parent process */
		do {
			waitpid(pid, &status, 0); /* wait for the child process to complete */
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (-1);
}

/**
 * display_shell_prompt - display a shell prompt
 * and wait for the user to enter a command
 *
 */
void display_shell_prompt(void)
{
	char *line;
	char **args;
	int status = -1;

	do {
		printf("$ "); /* print prompt symbol */
		line = read_line(); /* read line from stdin */
		args = split_line(line); /* tokenize line */
		status = execute_args(args); /* execute arguments (command and options) */

		/* free allocated memory to avoid memory leaks */
		free(line);
		free(args);
		/* exit with status */
		if (status >= 0)
		{
			exit(status);
		}
	} while (status == -1);
}


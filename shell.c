#include "main.h"


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
 * @command: command to be executed
 * @shell: shell name
 * Return: 1 on sucess, 0 otherwise
 */
int execute_args(char *command, char *shell)
{
	char **args;
	pid_t pid;
	int status;

	args = split_line(command); /* tokenize line */

	if (args[0] == NULL) /* if no command was entered */
		return (-1);
	/* Check if the command is "cd" */
		if (builtin_cd(args) == 1)
			return (1);
		/* create a new process */
		pid = fork();
		if (pid ==  0) /* child process created if fork returns 0 */
		{
			/* child process */
			if (execve(args[0], args, NULL) == -1) /* if execve failed */
			{
				/* handle PATH */
				handle_PATH(args, shell);
				perror(shell);
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
 * @shell: shell name
 */
void display_shell_prompt(char *shell)
{
	char *line;
	int int_mode = 1;

	while (int_mode)
	{
		/* test whether a file descriptor refers to a terminal */
		int_mode = isatty(STDIN_FILENO);

		if (int_mode == 1)
			write(STDOUT_FILENO, "$ ", 2);

		line = read_line(); /* read line from stdin */
		exit_shell(line);
		/* handle multi commands */
		handle_multi_commands(line, shell);

		/* free allocated memory to avoid memory leaks */
		free(line);
	}

}

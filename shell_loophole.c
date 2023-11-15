#include "shell.h"

/**
 * hsh - main shell loophole
 * @cue: the parameter & return cue struct
 * @av: the main() vector of argument
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(cue_t *cue, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_cue(cue);
		if (interactive(cue))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(cue);
		if (r != -1)
		{
			set_cue(cue, av);
			builtin_ret = find_builtin(cue);
			if (builtin_ret == -1)
				find_cmd(cue);
		}
		else if (interactive(cue))
			_putchar('\n');
		free_cue(cue, 0);
	}
	write_history(cue);
	free_cue(cue, 1);
	if (!interactive(cue) && cue->status)
		exit(cue->status);
	if (builtin_ret == -2)
	{
		if (cue->err_num == -1)
			exit(cue->status);
		exit(cue->err_num);
	}
	return (builtin_ret);
}
/**
 * find_builtin - discovers the builtin command
 * @cue: the parameter & return cue struct
 *
 * Return: -1 if builtin is not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtin(cue_t *cue)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _ourexit},
		{"env", _ourenv},
		{"help", _ourhelp},
		{"history", _ourhistory},
		{"setenv", _oursetenv},
		{"unsetenv", _ourunsetenv},
		{"cd", _ourcd},
		{"alias", _ouralias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(cue->argv[0], builtintbl[i].type) == 0)
		{
			cue->line_count++;
			built_in_ret = builtintbl[i].func(cue);
			break;
		}
	return (built_in_ret);
}
/**
 * find_cmd - discovers the command in PATH
 * @cue: the parameter & return cue struct
 *
 * Return: void
 */
void find_cmd(cue_t *cue)
{
	char *path = NULL;
	int i, k;

	cue->path = cue->argv[0];
	if (cue->linecount_flag == 1)
	{
		cue->line_count++;
		cue->linecount_flag = 0;
	}
	for (i = 0, k = 0; cue->arg[i]; i++)
		if (!is_delim(cue->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(cue, _getenv(cue, "PATH="), cue->argv[0]);
	if (path)
	{
		cue->path = path;
		fork_cmd(cue);
	}
	else
	{
		if ((interactive(cue) || _getenv(cue, "PATH=")
					|| cue->argv[0][0] == '/') && is_cmd(cue, cue->argv[0]))
			fork_cmd(cue);
		else if (*(cue->arg) != '\n')
		{
			cue->status = 127;
			print_error(cue, "not found\n");
		}
	}
}
/**
 * fork_cmd - an exec becomes to fork thread to run cmd
 * @cue: the parameter & return cue struct
 *
 * Return: void
 */
void fork_cmd(cue_t *cue)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(cue->path, cue->argv, get_environ(cue)) == -1)
		{
			free_cue(cue, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(cue->status));
		if (WIFEXITED(cue->status))
		{
			cue->status = WEXITSTATUS(cue->status);
			if (cue->status == 126)
				print_error(cue, "Permission denied\n");
		}
	}
}

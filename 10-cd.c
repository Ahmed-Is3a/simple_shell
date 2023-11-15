#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

#define ARG_MAX 100
#define ARG_MAX_COUNT 10
/*
** tokenize – implementation of builtin command that changes the present directory process
*/
int tokenize(char *load, char **args, int max_args)
{
	int arg_count = 0;
	int in_arg = 0;

	while (*load)
	{
		if (*load == ' ' || *load == '\t' || *load == '\n')
		{
		*load = '\0';
		in_arg = 0;
		}
		else if (!in_arg)
		{
		args[arg_count] = load;
		arg_count++;

		if (arg_count >= max_args)
		{
		fprintf(stderr, "Numerous arguments. Max is %d.\n", ARG_MAX_COUNT);
		return (-1);
		}
		in_arg = 1;
		}
		load++;
	}
	args[arg_count] = NULL;
	return (arg_count);
}

/*
** main – commands syntax cd direstory.
*/
int main(void)
{
	char command[ARG_MAX];
	char args[ARG_MAX_COUNT][ARG_MAX];
	char present_directory[PATH_MAX];

	while (1)
	{
	printf("simple_shell$ ");

	if (fgets(command, ARG_MAX, stdin) == NULL)
	{
	printf("\n");
	break;
	}
	command[strcspn(command, "\n")] = '\0';

	int arg_count = tokenize(command, args, ARG_MAX_COUNT);

	if (arg_count < 0)
	{
		continue;
	}

	if (arg_count > 0)
	{
		if (strcmp(args[0], "exit") == 0)
		{
			int exit_status = 0;
			if (arg_count == 2)
			{
			exit_status = atoi(args[1]);
			}
			exit(exit_status);
		}
		else if (strcmp(args[0], "env") == 0)
		{
			for (char **env = environ; *env; env++)
			{
				printf("%s\n", *env);
			}
		}
	}
	else if (strcmp(args[0], "setenv") == 0)
	{
		if (arg_count != 3)
		{
			fprintf(stderr, "Utilization: setenv FLUTUATING VALUE\n");
		}
		else
		{
			if (setenv(args[1], args[2], 1) != 0)
			{
				fprintf(stderr, "Go phut to set environment variable.\n");
			}
	}
	else if (strcmp(args[0], "unsetenv") == 0)
	{
		if (arg_count != 2)
		{
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		}
		else
		{
			if (unsetenv(args[1]) != 0)
			{
				fprintf(stderr, "Go phut to unset environment variable.\n");
			}
		}
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		char *new_directory = (arg_count == 1) ? getenv("HOME") : args[1];
		if (chdir(new_directory) != 0)
		{
			fprintf(stderr, "Go phut to change directory to %s\n", new_directory);
		}
		else
		{
			getcwd(present_directory, sizeof(present_directory));
			setenv("PWD", present_directory, 1);
		}
	}
	else
	{
		char *path = getenv("PATH");
		char *path_copy = strdup(path);
		char *dir = strtok(path_copy, ":");
		int command_found = 0;

		while (dir != NULL)
		{
			snprintf(args[0], sizeof(args[0]), "%s/%s", dir, args[0]);

			if (access(args[0], X_OK) == 0)
			{
			command_found = 1;
			int pid = fork();
			if (pid == 0)
			{
				execv(args[0], args);
				fprintf(stderr, "Command execution Go phut.\n");
				exit(1);
			}
		}
	}
	else if (pod > 0)
	{
	wait(NULL);
	break;
	}
	{
		fprintf(stderr, "Fork Go phut.\n");
	}
	dir = strtok(NULL, ":");
	}
	free(path_copy);

	if (!command_found)
	{
	fprintf(stderr, "Command not discovered in PATH.\n");
	}

	return (0);
}

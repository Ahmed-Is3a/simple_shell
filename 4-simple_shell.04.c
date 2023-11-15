#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define ARG_MAX 100
#define ARG_MAX_COUNT 10
/*
** main – implementation of the exit built-in that exists the shell
*/
int main(void)
{
	char command[ARG_MAX];
	char *args[ARG_MAX_COUNT];

	while (1)
	{
	printf("simple_shell$ ");

	if (fgets(command, ARG_MAX, stdin) == NULL)
	{
		printf("\n");
		break;
	}

	command[strcspn(command, "\n")] = '\0';

	char *token = strtok(command, " ");
	int arg_count = 0;

	while (token != NULL)
	{
		args[arg_count] = token;
		arg_count++;
		if (arg_count >= ARG_MAX_COUNT)
		{
			fprintf(stderr, "Too many arguments. Max is %d.\n", ARG_MAX_COUNT);
			arg_count = 0;
			break;
		}
		token = strtok(NULL, " ");
	}
	args[arg_count] = NULL;

	if (arg_count > 0)
	{
		if (strcmp(args[0], "exit") == 0)
		{
			break;
		}
		char *path = getenv("PATH");
		char *path_copy = strdup(path);
		char *dir = strtok(path_copy, ":");
		int command_found = 0;

		while (dir != NULL)
		{
			char command_path[ARG_MAX];

			snprintf(command_path, sizeof(command_path), "%s/%s", dir, args[0]);

			if (access(command_path, X_OK) == 0)
			{
			command_found = 1;
			int pid = fork();

			if (pid == 0)
			{
			execv(command_path, args);
			fprintf(stderr, "Command execution Go phut.\n");
			exit(1);
			}
			else if (pid > 0)
			{
				wait(NULL);
				break;
			}
			{
				fprintf(stderr, "Fork Go phut.\n");
			}
			}

			dir = strtok(NULL, ":");
		}
		free(path_copy);

		if (!command_found)
		{
			fprintf(stderr, "Command not found in PATH.\n");
		}
		}
	}
	return (0);
}

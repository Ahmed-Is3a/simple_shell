#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARG_MAX 100
/**
 *  main – Display a prompt and wait for user to type a command.
 * Return: 0 (Success)
 */
int main(void)
{
	char command[ARG_MAX];

	while (1)
	{
		printf("simple_shell$ ");

		if (fgets(command, ARG_MAX, stdin) == NULL)
		{
			printf("\n");
			break;
		}

		command[strcspn(command, "\n")] = '\0';

		int status = system(command);

		if (status == -1)
		{
			fprintf(stderr, "Command execution Go phut.\n");
		}
	}

	return (0);
}

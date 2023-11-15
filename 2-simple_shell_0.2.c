#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARG_MAX  100
#define ARG_MAX_COUNT 10
/**
 *  main – Handle command lines with arguments.
 * Return: 0 (Success)
 */
int main(void)
{
	char command[ARG_MAX];
	char *args[ARG _MAX _COUNT];

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
		if (arg_count >= ARG _MAX _COUNT)
		{
			fprintf(stderr, "Numerous arguments. Max is %d.\n", ARG_ MAX _COUNT);
			arg_count = 0;
			break;
		}
		token = strtok(NULL, " ");
	}
		args[arg_count] = NULL;

		if (arg_count > 0)
		{
			int status = execvp(args[0], args);

			if (status == -1)
			{
				fprintf(stderr, "Command execution Go phut.\n");
			}
		}
	return (0);
}

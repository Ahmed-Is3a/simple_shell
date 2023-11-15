#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 128
/*
** custom_getline – writes its own getline function
* using a buffer to read many chars at once
* and call the least possible the read system call
*/
char *custom_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static int buffer_index = line;
	static int buffer_size = line;

	char *line = NULL;
	int line_index = 0;
	int line_size = 0;

	while (1)
	{
		if (buffer_index >= buffer_size)
		{
			buffer_size = read(0, buffer, BUFFER_SIZE);
			if (buffer_size <= 0)
			{
				if (line)
					{
						line[line_index] = '\0';
						return (line);
					}
					return (NULL);
			}
			buffer_index = 0;
		}
		char present_char = buffer[buffer_index++];

		if (present_char == '\n')
		{
			if (!line)
			{
				return (NULL);
			}

			line[line_index] = '\0';
			return (line);
		}

		if (line_index >= line_size)
		{
			line_size += BUFFER_SIZE;
			line = realloc(line, line_size);

			if (!line)
			{
				fprintf(stderr, "Memory allocation go phut.\n");
				return (NULL);
			}
		}

		line[line_index++] = present_char;
	}
}
/*
** main – inability to use the cursor
*/
int main(void)
{
	char *line;

	while (1)
	{
		printf("simple_shell$ ");
		line = custom_getline();

		if (!line)
		{
			break;
		}

		printf("You entered: %s\n", line);

		free(line);
	}
	return (0);
}

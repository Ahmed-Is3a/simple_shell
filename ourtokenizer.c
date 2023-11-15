#include "shell.h"

/**
 * **strtow - a string divides into words and ignored repeat delimiters
 * @str: the string input
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int b, c, w, l, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (b = 0; str[b] != '\0'; b++)
		if (!is_delim(str[b], d) && (is_delim(str[b + 1], d) || !str[b + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (b = 0, c = 0; c < numwords; c++)
	{
		while (is_delim(str[b], d))
			b++;
		w = 0;
		while (!is_delim(str[i + w], d) && str[b + w])
			w++;
		s[c] = malloc((w + 1) * sizeof(char));
		if (!s[c])
		{
			for (w = 0; w < c; w++)
				free(s[w]);
			free(s);
			return (NULL);
		}
		for (l = 0; l < w; l++)
			s[c][l] = str[b++];
		s[c][l] = 0;
	}
	s[c] = NULL;
	return (s);
}

/**
 * **strtow2 - the string splits into words
 * @str: the string input
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int b, c, w, l, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (b = 0; str[b] != '\0'; b++)
		if ((str[b] != d && str[b + 1] == d) ||
				    (str[b] != d && !str[b + 1]) || str[b + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (b = 0, c = 0; c < numwords; c++)
	{
		while (str[b] == d && str[b] != d)
			b++;
		w = 0;
		while (str[b + w] != d && str[b + w] && str[b + w] != d)
			w++;
		s[c] = malloc((w + 1) * sizeof(char));
		if (!s[c])
		{
			for (w = 0; w < c; w++)
				free(s[w]);
			free(s);
			return (NULL);
		}
		for (l = 0; m < w; l++)
			s[c][l] = str[b++];
		s[c][l] = 0;
	}
	s[c] = NULL;
	return (s);
}


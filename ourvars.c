#include "shell.h"

/**
 * is_loop – the current char in buffer is tested is a chain delimeter
 * @cue: the struct parameter
 * @buf: the buffer char
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_loop(cue_t *cue, char *buf, size_t *p)
{
	size_t c = *p;

	if (buf[c] == '|' && buf[c + 1] == '|')
	{
		buf[c] = 0;
		c++;
		cue->cmd_buf_type = CMD_OR;
	}
	else if (buf[c] == '&' && buf[j + 1] == '&')
	{
		buf[c] = 0;
		c++;
		cue->cmd_buf_type = CMD_AND;
	}
	else if (buf[c] == ';')
	{
		buf[c] = 0;
		cue->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = c;
	return (1);
}

/**
 * check_loop - checks we should continue looping based on last status
 * @cue: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buffer
 * @i: starting position in buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void check_loop(cue_t *cue, char *buf, size_t *p, size_t i, size_t len)
{
	size_t c = *p;

	if (cue->cmd_buf_type == CMD_AND)
	{
		if (cue->status)
		{
			buf[i] = 0;
			c = len;
		}
	}
	if (cue->cmd_buf_type == CMD_OR)
	{
		if (!cue->status)
		{
			buf[i] = 0;
			c = len;
		}
	}

	*p = c;
}

/**
 * depose_alias - an aliases is deposed in the tokenized string
 * @cue: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int depose_alias(cue_t *cue)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(cue->alias, cue->argv[0], '=');
		if (!node)
			return (0);
		free(cue->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		cue->argv[0] = p;
	}
	return (1);
}

/**
 * depose_vars - deposes vars in the tokenized string
 * @cue: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int depose_vars(cue_t *cue)
{
	int i = 0;
	list_t *node;

	for (i = 0; cue->argv[i]; i++)
	{
		if (cue->argv[i][0] != '$' || !cue->argv[i][1])
			continue;

		if (!_strcmp(cue->argv[i], "$?"))
		{
			replace_string(&(cue->argv[i]),
					_strdup(convert_number(cue->status, 10, 0)));
			continue;
		}
		if (!_strcmp(cue->argv[i], "$$"))
		{
			replace_string(&(cue->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(cue->env, &cue->argv[i][1], '=');
		if (node)
		{
			replace_string(&(cue->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&cue->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * depose_string - deposes string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int depose_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

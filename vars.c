#include "shell.h"

/**
 * is_chain - check if the current character in the buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the character buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = '\0';
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = '\0';
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = '\0'; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*p = j;
	return (1);
}

/**
 * check_chain - check if chaining should
 * continue based on the last status
 * @info: the parameter struct
 * @buf: the character buffer
 * @p: address of the current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t i = *p;

	if (i < len && buf[i] == '&' && buf[i + 1] == '&')
	{
		info->status = !(info->last_status == 0);
		buf[i] = '\0';
		*p = i + 2;
	}
	else if (i < len && buf[i] == '|' && buf[i + 1] == '|')
	{
		info->status = !(info->last_status == 0);
		buf[i] = '\0';
		*p = i + 2;
	}
	else if (i < len && buf[i] == ';')
	{
		buf[i] = '\0';
		*p = i + 1;
	}
	else
		*p = i;
}

/**
 * replace_alias - replaces an alias in the tokenized string
 * @info: pointer to the info_t struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_alias(info_t *info)
{
	int i;
	list_t *alias_node;
	char *alias_value;

	for (i = 0; i < 10; i++)
	{
		alias_node = find_alias_node(info->alias, info->argv[0]);
		if (!alias_node)
			return (0);
		free(info->argv[0]);
		alias_value = get_alias_value(alias_node);
		if (!alias_value)
			return (0);
		info->argv[0] = _strdup(alias_value);
		if (!info->argv[0])
			return (0);
	}

	return (1);
}

/**
 * replace_vars - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_vars(info_t *info)

{
	int i = 0;
	list_t *var_node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]), _strdup(convert_number(info->status,
						       10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		var_node = find_variable(info->env, &(info->argv[i][1]));
		if (var_node)
		{
			replace_string(&(info->argv[i]), _strdup(get_value_from_node(var_node)));
			continue;
		}
		replace_string(&(info->argv[i]), _strdup(""));
	}

	return (0);
}

/**
 * replace_string - replaces a string with a new string
 * @old: address of the old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_string(char **old, char *new)

{
	free(*old);
	*old = _strdup(new);
	if (*old == NULL)
		return (0);
	return (1);
}

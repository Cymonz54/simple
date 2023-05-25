#include "shell.h"

/**
 * **strtow - Splits the input string into words
 * based on the specified delimiter string.
 * @str: The input string
 * @str: The input string
 * @d: The delimiter string/character
 *
 * Return: a pointer to an array of strings, representing the words,
 * or NULL on failure
 */

char **strtow(char *str, char d)

{
	int i, j, k, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
	{
		if (!(*d) && str[i] != *d)
			num_words++;
		else if (*d && str[i] != *d && (str[i + 1] == *d || str[i + 1] == '\0'))
			num_words++;
	}
	if (num_words == 0)
		return (NULL);
	s = malloc((num_words + 1) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (*str && *d && *str == *d)
			str++;
		k = 0;
		while (*str && *d && *str != *d)
			k++, str++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[-k + m];
		s[j][m] = '\0';
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - Split a string into words using a specified delimiter
 * @str: The input string
 * @d: The delimiter character
 *
 * Return: A pointer to an array of strings representing the words,
 * or NULL on failure
 */

char **strtow2(char *str, char *d)

{
	int i, j, k, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			num_words++;
	}
	if (num_words == 0)
		return (NULL);
	s = malloc((num_words + 1) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = '\0';
	}
	s[j] = NULL;
	return (s);
}

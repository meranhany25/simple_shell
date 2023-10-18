#include "shell.h"
/**
 * tokenizer - Splits the input string into tokens and stores them in an array.
 *@input_string: Input string to be parsed.
 *@delim: Delimiter character to be used.
 *Return: Array of tokens
 */
char **tokenizer(char *input_string, char *delim)
{
	int num_delim = 0;
	char **av = NULL;
	char *token = NULL;
	char *save_ptr = NULL;

	token = _strtok_r(input_string, delim, &save_ptr);
	while (token != NULL)
	{
		av = _realloc(av, sizeof(*av) * num_delim, sizeof(*av) * (num_delim + 1));
		av[num_delim] = token;
		token = _strtok_r(NULL, delim, &save_ptr);
		num_delim++;
	}

	av = _realloc(av, sizeof(*av) * num_delim, sizeof(*av) * (num_delim + 1));
	av[num_delim] = NULL;

	return (av);
}
/**
 *print - Prints a string to the specified output stream.
 *@string: String to be printed.
 *@stream: Output stream to print.
 *Return: void
 */
void print(char *string, int stream)
{
	int i = 0;

	for (; string[i] != '\0'; i++)
		write(stream, &string[i], 1);
}
/**
 *remove_newline - Removes newline characters from a string.
 *@str: String to be modified.
 *Return: void
 */
void remove_newline(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			break;
		i++;
	}
	str[i] = '\0';
}
/**
 *_strcpy - Copies a string from source to destination.
 *@source: Source string to copy from.
 *@dest: Destination buffer to copy to.
 * Return: void
 */
void _strcpy(char *source, char *dest)
{
	int i = 0;

	for (; source[i] != '\0'; i++)
		dest[i] = source[i];
	dest[i] = '\0';
}
/**
 *_strlen - Calculates the length of a string.
 *@string: String to be measured.
 * Return: Length of the string.
 */
int _strlen(char *string)
{
	int len = 0;

	if (string == NULL)
		return (len);
	for (; string[len] != '\0'; len++)
		;
	return (len);
}

#include "shell.h"
/**
 *split_string - Splits the input string into tokens & store in an array.
 *@input: Input string to be parsed.
 *@delimiter: Delimiter character to be used.
 *Return: Array of tokens.
 */
char **split_string(char *input, char *delimiter)
{
	int num_tokens = 0;
	char **tokens = NULL;
	char *token = NULL;
	char *save_ptr = NULL;

	token = tokenize_string(input, delimiter, save_ptr);
	while (token != NULL)
	{
		tokens = reallocate(tokens, sizeof(*tokens) * num_tokens,
							sizeof(*tokens) * (num_tokens + 1));
		tokens[num_tokens] = token;
		token = tokenize_string(NULL, delimiter, save_ptr);
		num_tokens++;
	}
	tokens = reallocate(tokens, sizeof(*tokens) * num_tokens,
						sizeof(*tokens) * (num_tokens + 1));
	tokens[num_tokens] = NULL;
	return (tokens);
}
/**
 * custom_print - Prints a string to the specified output stream.
 * @string: String to be printed.
 * @stream: Output stream to print to.
 * Return: void.
 */
void custom_print(char *string, int stream)
{
	int i = 0;

	for (; string[i] != '\0'; i++)
		write(stream, &string[i], 1);
}
/**
 * remove_newline - Removes newline characters from a string.
 * @str: String to be modified.
 * Return: void.
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
 * custom_strcpy - Copies a string from source to destination.
 * @source: Source string to copy from.
 * @dest: Destination buffer to copy to.
 * Return: void.
 */
void custom_strcpy(char *source, char *dest)
{
	int i = 0;

	for (; source[i] != '\0'; i++)
		dest[i] = source[i];
	dest[i] = '\0';
}
/**
 * custom_strlen - Calculates the length of a string.
 * @string: String to be measured.
 * Return: Length of the string.
 */
int custom_strlen(char *string)
{
	int len = 0;

	if (string == NULL)
		return (len);
	for (; string[len] != '\0'; len++)
		;
	return (len);
}

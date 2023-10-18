#include "shell.h"
/**
 * tokenize_string - Tokenizes a string.
 * @string: The string to be tokenized.
 * @delim: The delimiter used to tokenize the string.
 * @save_ptr: Pointer to keep track of the next token.
 * Return: The next available token.
 */
char *tokenize_string(char *string, char *delim, char **save_ptr)
{
	char *next_token;

	if (string == NULL)
		string = *save_ptr;
	if (*string == '\0')
	{
		*save_ptr = string;
		return (NULL);
	}
	string += get_prefix_length(string, delim);
	if (*string == '\0')
	{
		*save_ptr = string;
		return (NULL);
	}
	next_token = string + get_segment_length(string, delim);
	if (*next_token == '\0')
	{
		*save_ptr = next_token;
		return (string);
	}
	*next_token = '\0';
	*save_ptr = next_token + 1;
	return (string);
}
/**
 * convert_string_to_integer - Converts a string to an integer.
 * @s: The string to be converted.
 * Return: The converted integer.
 */
int convert_string_to_integer(char *s)
{
	unsigned int result = 0;

	do {
		if (*s == '-')
			return (-1);
		else if ((*s < '0' || *s > '9') && *s != '\0')
			return (-1);
		else if (*s >= '0' && *s <= '9')
			result = (result * 10) + (*s - '0');
		else if (result > 0)
			break;
	}	while (*s++);
	return (result);
}
/**
 * reallocate - Reallocates a memory block.
 * @ptr: Pointer to the memory previously allocated with malloc.
 * @old_size: Size of the original memory block.
 * @new_size: Size of the new memory block.
 * Return: Pointer to the address of the new memory block.
 */
void *reallocate(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_block;
	unsigned int i;

	if (ptr == NULL)
	{
		new_block = malloc(new_size);
		return (new_block);
	}
	else if (new_size == old_size)
	{
		return (ptr);
	}
	else if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		new_block = malloc(new_size);
		if (new_block != NULL)
		{
			for (i = 0; i < min(old_size, new_size); i++)
				*((char *)new_block + i) = *((char *)ptr + i);
			free(ptr);
			return (new_block);
		}
		else
		{
			return (NULL);
		}
	}
}
/**
 * handle_ctrl_c - Handles the signal raised by CTRL-C.
 * @signum: Signal number.
 * Return: void.
 */
void handle_ctrl_c(int signum)
{
	if (signum == SIGINT)
		custom_print("\n($) ", STDIN_FILENO);
}
/**
 * remove_comment - Removes/ignores everything after a '#' character.
 * @input: The input string.
 * Return: void.
 */
void remove_comment(char *input)
{
	int i = 0;

	if (input[i] == '#')
		input[i] = '\0';
	while (input[i] != '\0')
	{
		if (input[i] == '#' && input[i - 1] == ' ')
			break;
		i++;
	}
	input[i] = '\0';
}

#include "shell.h"

/**
 * compare_strings - Compares two strings and
 *			returns the difference between them.
 * @str1: The first string to be compared.
 * @str2: The second string to be compared.
 * Return: The difference between the two strings.
 */
int compare_strings(char *str1, char *str2)
{
	int i = 0;

	while (str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			break;
		i++;
	}
	return (str1[i] - str2[i]);
}
/**
 * concatenate_strings - Concatenates two strings
 *			and returns the new string.
 * @dest: The string to which the second string is concatenated.
 * @src: The string that is concatenated to the destination string.
 * Return: The address of the new string.
 */
char *concatenate_strings(char *dest, char *src)
{
	char *new_string = NULL;
	int dest_length = custom_strlen(dest);
	int src_length = custom_strlen(src);

	new_string = malloc(sizeof(*new_string) * (dest_length + src_length + 1));

	custom_strcpy(dest, new_string);
	custom_strcpy(src, new_string + dest_length);
	new_string[dest_length + src_length] = '\0';
	return (new_string);
}
/**
 * prefix_length - Calculates the length of a prefix substring
 *			in str1 that matches str2.
 * @str1: The string to be searched.
 * @str2: The string to be used as the prefix.
 * Return: The number of bytes in the initial segment of str1 that match str2.
 */
int prefix_length(char *str1, char *str2)
{
	int i = 0;
	int match = 0;

	while (str1[i] != '\0')
	{
		if (character_search(str2, str1[i]) == NULL)
			break;
		match++;
		i++;
	}
	return (match);
}
/**
 * segment_length - Calculates the length of the segment in
 *			str1 that consists of characters not in str2.
 * @str1: The string to be searched.
 * @str2: The string containing the characters to be excluded.
 * Return: The index at which a character from str1 is found in str2.
 */
int segment_length(char *str1, char *str2)
{
	int length = 0;
	int i;

	for (i = 0; str1[i] != '\0'; i++)
	{
		if (character_search(str2, str1[i]) != NULL)
			break;
		length++;
	}
	return (length);
}
/**
 * character_search - Locates a character in a string.
 * @str: The string to be searched.
 * @ch: The character to be located.
 * Return: A pointer to the first occurrence of the character
 *			in the string, or NULL if not found.
 */
char *character_search(char *str, char ch)
{
	int i = 0;

	for (; str[i] != ch && str[i] != '\0'; i++)
		;
	if (str[i] == ch)
		return (str + i);
	else
		return (NULL);
}

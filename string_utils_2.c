#include "shell.h"
/**
 *_strcmp - Compares two strings and returns the difference between them.
 *@first: The first string to be compared.
 *@second: The second string to be compared.
 * Return: The difference between the two strings.
 */
int _strcmp(char *first, char *second)
{
	int i = 0;

	while (first[i] != '\0')
	{
		if (first[i] != second[i])
			break;
		i++;
	}
	return (first[i] - second[i]);
}
/**
 *_strcat - Concatenates two strings and returns the new string.
 *@destination: The string to which the second string is concatenated.
 *@source: The string that is concatenated to the destination string.
 * Return: The address of the new string.
 */
char *_strcat(char *destination, char *source)
{
	char *new_string =  NULL;
	int len_dest = _strlen(destination);
	int len_source = _strlen(source);

	new_string = malloc(sizeof(*new_string) * (len_dest + len_source + 1));
	_strcpy(destination, new_string);
	_strcpy(source, new_string + len_dest);
	new_string[len_dest + len_source] = '\0';
	return (new_string);
}
/**
 *_strspn - Calculates length of a prefix substring in str1 that match str2.
 *@str1: The string to be searched.
 *@str2: The string to be used as the prefix.
 *Return: The number of bytes in the initial segment of str1 that match str2.
 */
int _strspn(char *str1, char *str2)
{
	int i = 0;
	int match = 0;

	while (str1[i] != '\0')
	{
		if (_strchr(str2, str1[i]) == NULL)
			break;
		match++;
		i++;
	}
	return (match);
}
/**
 *_strcspn - Calculates length of segment in str1 with chars not in str2.
 *@str1: The string to be searched.
 *@str2: The string containing the characters to be excluded.
 *Return: The index at which a character from str1 is found in str2.
 */
int _strcspn(char *str1, char *str2)
{
	int len = 0, i;

	for (i = 0; str1[i] != '\0'; i++)
	{
		if (_strchr(str2, str1[i]) != NULL)
			break;
		len++;
	}
	return (len);
}
/**
 *_strchr - Locates a character in a string.
 *@s: The string to be searched.
 *@c: The character to be located.
 *Return: Pointer to first occurrence of character, or NULL if not found.
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	for (; s[i] != c && s[i] != '\0'; i++)
		;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}

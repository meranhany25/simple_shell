#include "shell.h"
/**
 * print_environment_variables - Prints the current environment variables.
 * @tokenized_command: The command entered.
 * Description: This function prints the current environment variables
 *              to the standard output.
 * Return: void.
 */
void print_environment_variables(char **tokenized_command
		__attribute__((unused)))
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		custom_print(environ[i], STDOUT_FILENO);
		custom_print("\n", STDOUT_FILENO);
	}
}
/**
 * exit_shell - Exits the shell.
 * @tokenized_command: The command entered.
 * Description: This function exits the shell. If no argument is provided,
 *              it exits with the current status. If an argument is provided,
 *              it exits with the specified status value.
 * Return: void.
 */
void exit_shell(char **tokenized_command)
{
	int num_tokens = 0, arg;

	for (; tokenized_command[num_tokens] != NULL; num_tokens++)
		;

	if (num_tokens == 1)
	{
		free(tokenized_command);
		free(line);
		free(commands);
		exit(status);
	}
	else if (num_tokens == 2)
	{
		arg = convert_string_to_integer(tokenized_command[1]);

		if (arg == -1)
		{
			custom_print(shell_name, STDERR_FILENO);
			custom_print(": 1: exit: Illegal number: ", STDERR_FILENO);
			custom_print(tokenized_command[1], STDERR_FILENO);
			custom_print("\n", STDERR_FILENO);
			status = 2;
		}
		else
		{
			free(line);
			free(tokenized_command);
			free(commands);
			exit(arg);
		}
	}
	else
	{
		custom_print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
	}
}

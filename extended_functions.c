#include "shell.h"
/**
 * determine_command_type - Determines the type of the command.
 * @command: The command to be analyzed.
 * Return: A constant representing the type of the command.
 */
int determine_command_type(char *command)
{
	int i;
	char *internal_commands[] = {"env", "exit", NULL};
	char *path = NULL;

	for (i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == '/')
			return (EXTERNAL_COMMAND);
	}
	for (i = 0; internal_commands[i] != NULL; i++)
	{
		if (compare_strings(command, internal_commands[i]) == 0)
			return (INTERNAL_COMMAND);
	}
	path = find_command_path(command);
	if (path != NULL)
	{
		free(path);
		return (PATH_COMMAND);
	}

	return (INVALID_COMMAND);
}
/**
 * execute_command - Executes a command based on its type.
 * @tokenized_command: The tokenized form of the command.
 * @command_type: The type of the command.
 * Return: void.
 */
void execute_command(char **tokenized_command, int command_type)
{
	void (*func)(char **command);

	if (command_type == EXTERNAL_COMMAND)
	{
		if (execve(tokenized_command[0], tokenized_command, NULL) == -1)
		{
			perror(get_environment_variable("PWD"));
			exit(2);
		}
	}
	if (command_type == PATH_COMMAND)
	{
		if (execve(find_command_path(tokenized_command[0]),
					tokenized_command, NULL) == -1)
		{
			perror(get_environment_variable("PWD"));
			exit(2);
		}
	}
	if (command_type == INTERNAL_COMMAND)
	{
		func = get_function(tokenized_command[0]);
		func(tokenized_command);
	}
	if (command_type == INVALID_COMMAND)
	{
		custom_print(shell_name, STDERR_FILENO);
		custom_print(": 1: ", STDERR_FILENO);
		custom_print(tokenized_command[0], STDERR_FILENO);
		custom_print(": not found\n", STDERR_FILENO);
		status = 127;
	}
}
/**
 * find_command_path - Checks if a command is found in the
 * PATH environment variable.
 * @command: The command to be checked.
 * Return: The path where the command is found, or NULL if not found.
 */
char *find_command_path(char *command)
{
	char **path_array = NULL;
	char *temp, *temp2, *path_cpy;
	char *path = get_environment_variable("PATH");
	int i;

	if (path == NULL || custom_strlen(path) == 0)
		return (NULL);
	path_cpy = malloc(sizeof(*path_cpy) * (custom_strlen(path) + 1));
	custom_strcpy(path, path_cpy);
	path_array = split_string(path_cpy, ":");
	for (i = 0; path_array[i] != NULL; i++)
	{
		temp2 = concatenate_strings(path_array[i], "/");
		temp = concatenate_strings(temp2, command);
		if (access(temp, F_OK) == 0)
		{
			free(temp2);
			free(path_array);
			free(path_cpy);
			return (temp);
		}
		free(temp);
		free(temp2);
	}
	free(path_cpy);
	free(path_array);
	return (NULL);
}
/**
 * get_function - Retrieves a function based on the given command and mapping.
 * @command: The command to check against the mapping.
 * Return: A pointer to the corresponding function, or NULL on failure.
 */
void (*get_function(char *command))(char **)
{
	int i;
	function_map mapping[] = {
		{"env", print_environment_variables}, {"exit", exit_shell}};

	for (i = 0; i < 2; i++)
	{
		if (compare_strings(command, mapping[i].command_name) == 0)
			return (mapping[i].func);
	}
	return (NULL);
}
/**
 * get_environment_variable - Returns the value of an environment variable.
 * @name: The name of the environment variable.
 * Return: The value of the variable as a string.
 */
char *get_environment_variable(char *name)
{
	char **env_var;
	char *pair_ptr;
	char *name_cpy;

	for (env_var = environ; *env_var != NULL; env_var++)
	{
		for (pair_ptr = *env_var, name_cpy = name;
			 *pair_ptr == *name_cpy; pair_ptr++, name_cpy++)
		{
			if (*pair_ptr == '=')
				break;
		}
		if ((*pair_ptr == '=') && (*name_cpy == '\0'))
			return (pair_ptr + 1);
	}
	return (NULL);
}

#include "shell.h"
char **commands = NULL;
char *line = NULL;
char *shell_name = NULL;
int status = 0;

/**
 * shell_main - The main function of the shell program.
 * @argc: The number of arguments passed to the program.
 * @argv: The program arguments to be parsed.
 * Return: 0 on success.
 */
int shell_main(int argc __attribute__((unused)), char **argv)
{
	char **current_command = NULL;
	int i, command_type = 0;
	size_t buffer_size = 0;

	signal(SIGINT, handle_ctrl_c);
	shell_name = argv[0];
	while (1)
	{
		process_non_interactive_mode();
		custom_print(" ($) ", STDOUT_FILENO);
		if (getline(&line, &buffer_size, stdin) == -1)
		{
			free(line);
			exit(status);
		}

		remove_newline(line);
		remove_comment(line);
		commands = split_string(line, ";");

		for (i = 0; commands[i] != NULL; i++)
		{
			current_command = split_string(commands[i], " ");
			if (current_command[0] == NULL)
			{
				free(current_command);
				break;
			}

			command_type = determine_command_type(current_command[0]);
			execute_command_handler(current_command, command_type);
			free(current_command);
		}

		free(commands);
	}

	free(line);

	return (status);
}

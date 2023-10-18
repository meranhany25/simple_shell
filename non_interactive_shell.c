#include "shell.h"

/**
 * process_non_interactive_mode - Handles the non-interactive mode of the shell
 * Return: void.
 */
void process_non_interactive_mode(void)
{
	char **current_command = NULL;
	int i, command_type = 0;
	size_t buffer_size = 0;

	if (!(isatty(STDIN_FILENO)))
	{
		while (getline(&line, &buffer_size, stdin) != -1)
		{
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
		exit(status);
	}
}

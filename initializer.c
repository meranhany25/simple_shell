#include "shell.h"

/**
 * execute_command_handler - Executes the given command based on its type.
 * @command: The command to be executed.
 * @command_type: The type of the command.
 * Return: void.
 */
void execute_command_handler(char **command, int command_type)
{
	pid_t pid;

	if (command_type == EXTERNAL_COMMAND || command_type == PATH_COMMAND)
	{
		pid = fork();

		if (pid == 0)
		{
			execute_command(command, command_type);
		}
		else
		{
			waitpid(pid, &status, 0);
			status >>= 8;
		}
	}
	else
	{
		execute_command(command, command_type);
	}
}

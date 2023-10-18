#include "shell.h"
/**
 * initializer - Executes the given command based on its type.
 * @current_command: The command to be executed.
 * @type_command: The type of the command.
 * Description: This function runs forks for external
 * /path & executes internally.
 * Return: void.
 */
void initializer(char **current_command, int type_command)
{
	pid_t PID;

	if (type_command == EXTERNAL_COMMAND || type_command == PATH_COMMAND)
	{
		PID = fork();
		if (PID == 0)
			execute_command(current_command, type_command);
		else
		{
			waitpid(PID, &status, 0);
			status >>= 8;
		}
	}
	else
		execute_command(current_command, type_command);
}

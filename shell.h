#ifndef shell_h
#define shell_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>

/*constants headers*/
#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1

#define min(x, y) (((x) < (y)) ? (x) : (y))
/**
 * struct map - A struct that maps a command name to a function.
 * @command_name: The name of the command.
 * @func: The function that executes the command.
 */
typedef struct map
{
	char *command_name;
	void (*func)(char **command);
} function_map;

extern char **environ;
extern char *line;
extern char **commands;
extern char *shell_name;
extern int status;

/*string_utils_1*/
char **split_string(char *, char *);
void custom_print(char *, int);
void remove_newline(char *);
void custom_strcpy(char *, char *);
int custom_strlen(char *);

/*string_utils_2*/
int compare_strings(char *, char *);
char *concatenate_strings(char *, char *);
int prefix_length(char *, char *);
int segment_length(char *, char *);
char *character_search(char *, char);

/*string_utils_3*/
char *tokenize_string(char *, char *, char **);
int convert_string_to_integer(char *);
void *reallocate(void *ptr, unsigned int old_size, unsigned int new_size);
void handle_ctrl_c(int);
void remove_comment(char *);

/*extended_functions*/
int determine_command_type(char *);
void execute_command(char **, int);
char *find_command_path(char *);
void (*get_function(char *))(char **);
char *get_environment_variable(char *);

/*builtin_fuctions*/
void print_environment_variables(char **);
void exit_shell(char **);

/*main*/
extern void process_non_interactive_mode(void);
extern void execute_command_handler(char **command, int command_type);

#endif

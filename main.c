#include "shell.h"

/**
 * main - Entry point for the simple shell program
 *
 * Description:
 * This function initializes the simple shell program and provides a basic
 * command-line interface where users can enter commands to be executed.
 * It reads user input, tokenizes it into commands and arguments, and
 * then uses the execve function to execute the specified commands.
 * The main loop continues to prompt for input and execute commands until
 * the user either enters the "exit" command or signals an end-of-file (EOF)
 * condition (usually with Ctrl+D).
 *
 * Return:
 * Return 0 upon successful execution of the program.
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	char *token;
	size_t len = 0;
	/* Adjust the array size as needed */
	char *args[10];
	int arg_count = 0;
	char *command;
	char *full_path; /* Stores the full path to the executable*/
	pid_t child_pid;
	(void)argc;
	(void)argv;
	/* While TRUE (Infinite Loop)*/
	while (True)
	{
		/* Display the prompt and get user INPUTS*/
		print("($) ");

		/* Read user INPUTS line*/
		if (getline(&line, &len, stdin) == -1)
		{
			/* Handle EOF (Ctrl+D)*/
			break;
		}

		/* Tokenize the user INPUTS */
		token = strtok(line, " \t\n");
		if (token == NULL)
		{
			/* Handle empty input */
			continue;
		}

		if (strcmp(token, "exit") == 0)
		{
			/* Handle exit command*/
			break;
		}
		
		if (strcmp(token, "env") == 0)
		{
			/* Handle env command */
			print_environment();
		}
		else
		{
			/* Reset arg_count for a new command */
			arg_count = 0;
			/* Identify the command and its arguments */
			command = token;
			/* Search for the command in PATH directories*/
			full_path = search_path(command);
			if (full_path == NULL)
			{
				/* Command not found*/
				/*print(argv[0]);
				print(": 1: ");
				print(command);
				print(": not found\n");*/
				/*printf("%s: %d: %s: %s \n", argv[0], errno, command, strerror(errno));*/
				perror("system");
				continue;
			}

			while (token != NULL)
			{
				args[arg_count++] = token;
				token = strtok(NULL, " \t\n");
			}
			/* Null-terminate the argument list */
			args[arg_count] = NULL;

			child_pid = fork();
			if (child_pid == 0)
			{
				/* Child process*/
				/* Pass the environment variables using the global 'environ' variable*/
				execve(full_path, args, environ);
				/* execve only returns if an error occurs*/
				perror(args[0]);
				exit(1);
			}
			else if (child_pid > 0)
			{
				/* Parent process*/
				wait(NULL); /* Wait for the child process to finish*/
			}
			else
			{
				perror("fork");
			}
		}

		/* Clear the memory for the next iteration */
		memset(line, 0, len);
	}

	free(line);
	return (0);
}

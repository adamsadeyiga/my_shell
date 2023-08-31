#include "shell.h"

/**
 * print - Custom function to display messages using write.
 *
 * @message: The message to be displayed.
 */
void print(const char *message)
{
	size_t length = 0;

	while (message[length] != '\0')
	{
		length++;
	}
	write(STDOUT_FILENO, message, length);
}

/**
 * get_last_element - Extract the last element from a
 * path string
 * @path: The input path string
 *
 * This function takes a path string as input and
 * extracts the last element (filename or directory)
 * from it by splitting the string at each "/" character.
 * The extracted last element is then returned.
 *
 * Return: A pointer to the last element of the path string.
 */
const char *get_last_element(const char *path)
{
	const char *last_element = path;
	const char *ptr = path;

	while (*ptr)
	{
		if (*ptr == '/')
		{
			last_element = ptr + 1; /* Move past the "/" */
		}
		ptr++;
	}

	return (last_element);
}

/**
 * search_path - Search for an executable command
 * in the PATH directories
 * @command: The command name to search for
 *
 * This function searches for the specified command in
 * the directories listed in the PATH environment variable.
 * It constructs the full path to the command if found and
 * returns it. If the command is not found in any of the directories,
 * NULL is returned.
 *
 * Return: A pointer to the full path of the executable command, or NULL
 * if the command is not found in any of the directories.
 */
char *search_path(const char *command)
{
	char *path_env;
	char *path_copy;
	char *dir;
	char *end;
	char full_path[MAX_PATH_LENGTH];

	path_env = getenv("PATH");
	if (path_env == NULL)
	{
		fprintf(stderr, "PATH environment variable not set\n");
		return (NULL);
	}

	path_copy = strdup(path_env);
	if (path_copy == NULL)
	{
		perror("strdup");
		return (NULL);
	}

	dir = path_copy;
	end = dir + strlen(dir);
	while (dir < end)
	{
		char *delimiter = strchr(dir, ':');
		
		if (delimiter)
			*delimiter = '\0';
		command = get_last_element(command);
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

		if (access(full_path, F_OK | X_OK) == 0)
		{
			/* Executable found, return its full path*/
			free(path_copy);
			return (strdup(full_path));
		}

		dir = delimiter ? delimiter + 1 : end;
	}

	free(path_copy);
	return (NULL); /* Command not found in any directory*/
}

void print_environment(void)
{
	extern char **environ;
	int i;
	for (i = 0; environ[i] != NULL; i++)
	{
		print(environ[i]);
		print("\n");
	}
}

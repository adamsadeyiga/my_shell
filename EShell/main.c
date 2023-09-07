#include "main.h"

int main(int argc, char **argv)
{
	string prompt, command, command_copy, token;
	size_t len;
	__ssize_t nchar_read;
	const char *delim;
	int num_token;
	int i;

	(void)argc;

	command = NULL;
	command_copy = NULL;
	delim = " \n";
	len = 0;
	num_token = 0;

	while (1)
	{
		prompt = "(Eshell) $ ";
		printf("%s", prompt);
		nchar_read = getline(&command, &len, stdin);

		command_copy = malloc(sizeof(char) * len);
		if(command_copy == NULL)
		{
			perror("Memory allocation failed.");
			return (-1);
		}
		strcpy(command_copy, command);

		if (nchar_read == -1)
		{
			printf("Exiting shell....\n");
			return (-1);
		}else
		{
			token = strtok(command, delim);
			while (token != NULL)
			{
				num_token++;
				token = strtok(NULL, delim);
			}
			num_token++;

			argv = malloc(sizeof(char *) * num_token);
			token = strtok(command_copy, delim);

			for (i = 0; token != NULL; i++)
			{
				argv[i] = malloc(sizeof(char) * sizeof(token));
				strcpy(argv[i], token);
				token = strtok(NULL, delim);
			}
			argv[i] = NULL;

			execmd(argv);
		}
		
	}

	free(argv);
	free(command_copy);
	free(command);
	
	return (0);
}

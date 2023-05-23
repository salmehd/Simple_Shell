 #include "shell.h"

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/**
 * help_env -  information on shellby builtin command 'env'.
 */
void help_env(void)
{
	char *mssg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, mssg, _strlen(mssg));
}

/**
 * help_setenv -  information on shellby builtin command 'setenv'.
 */
void help_setenv(void)
{
	char *mssg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
}

/**
 * help_unsetenv -  information on shellby builtin command
 * 'unsetenv'.
 */
void help_unsetenv(void)
{
	char *mssg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
	mssg = "message to stderr.\n";
	write(STDOUT_FILENO, mssg, _strlen(mssg));
}

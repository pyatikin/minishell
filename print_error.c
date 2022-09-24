#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

int	print_err(char *main, char	*word, char ch)
{
	int	stdout;

	stdout = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (main && word)
		printf(main, word);
	else if (main && ch)
		printf(main, ch);
	else
		printf("%s", main);
	dup2(stdout, STDOUT_FILENO);
	close(stdout);
	return (1);
}

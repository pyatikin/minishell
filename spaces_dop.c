#include "minishell.h"

int	is_space(char *cmd, int i)
{
	if (cmd[i] == ' ')
		return (1);
	return (0);
}

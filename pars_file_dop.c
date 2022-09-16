#include "minishell.h"

void	ft_ff_dop(char **pipe_line, int *i, int l, char **file)
{
	if (ft_quotes(*pipe_line) == 0)
	{
		while ((*i) < l)
		{
			(*file)[(*i)] = (*pipe_line)[(*i)];
			(*i)++;
		}
	}
	return ;
}

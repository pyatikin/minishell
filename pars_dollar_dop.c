#include "minishell.h"

void	ft_fev_dop(char **res, char **env, int i, int *k)
{
	(*res) = (char *)malloc(ft_strlen(env[i]) - (*k));
	(*res)[ft_strlen(env[i]) - (*k) - 1] = '\0';
	(*k)++;
}

void	ft_cl_pl(int *del, t_command *command, char **pipe_line)
{
	while (*pipe_line && (*del) < command->tmp)
	{
		(*del)++;
		(*pipe_line)--;
	}
	command->tmp = 0;
	free(*pipe_line);
}

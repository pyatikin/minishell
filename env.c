#include "minishell.h"

int	ft_env(t_env_var *vars, t_simpleCommand *cur_command)
{
	int	i;

	i = 0;
	while (vars->env[i])
	{
		printf("%s\n", vars->env[i]);
		i++;
	}
	return (0);
}

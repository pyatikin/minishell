#include "minishell.h"

int	ft_env(t_env_var *vars, t_simpleCommand *cur_command)
{
	int	i;

	if (cur_command->arguments[1])
	{
		ft_putstr_fd("env: no options or flags\n", 2);
		vars->status = 127;
		return (1);
	}
	i = 0;
	while (vars->env[i])
	{
		printf("%s\n", vars->env[i]);
		i++;
	}
	return (0);
}

#include "minishell.h"

void	find_and_del(t_env_var *vars, char *del)
{
	int		i;
	int		c;
	int		j;
	char	**tmp;

	i = -1;
	c = 0;
	while (vars->env[++i])
		c++;
	tmp = malloc(sizeof(char *) * (c));
	tmp[c - 1] = NULL;
	i = -1;
	j = -1;
	while (vars->env[++i])
		if (ft_strncmp(vars->env[i], del, ft_strlen(del)) != 0)
			tmp[++j] = ft_strdup(vars->env[i]);
	i = -1;
	while (vars->env[++i])
		free(vars->env[i]);
	free(vars->env[i]);
	free(vars->env);
	vars->env = tmp;
}

int	ft_unset(t_env_var *vars, t_simpleCommand *cur_command)
{
	int	i;

	i = 0;
	vars->status = 0;
	if (cur_command->number_of_arguments == 1)
		return (0);
	while (cur_command->number_of_arguments > ++i)
	{
		if (find_env(vars->env, cur_command->arguments[i]) == -1)
			continue ;
		find_and_del(vars, cur_command->arguments[i]);
	}
	return (0);
}

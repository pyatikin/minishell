#include "minishell.h"

int	find_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	print_export(t_env_var *var)
{
	int	i;

	i = 0;
	while (var->env[i])
	{
		printf("declare - x %s\n", var->env[i]);
		i++;
	}
	return (0);
}

void	add_new_env(t_env_var *vars, char *new)
{
	int		i;
	int		c;
	char	**tmp;

	i = -1;
	c = 1;
	while (vars->env[++i])
		c++;
	tmp = malloc(sizeof(char *) * (c + 1));
	tmp[c] = NULL;
	i = -1;
	while (vars->env[++i])
		tmp[i] = ft_strdup(vars->env[i]);
	tmp[i] = ft_strdup(new);
	i = -1;
	while (vars->env[++i])
		free(vars->env[i]);
	free(vars->env);
	vars->env = tmp;
}

void	free_pointers(char ***tmp, int **len)
{
	free((*tmp)[0]);
	free((*tmp)[1]);
	free(*tmp);
	free(*len);
}

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

int	add_new_env(t_env_var *vars, char *new)
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

int	available_var(t_env_var *vars, char *arguments)
{
	char	*tmp[3];
	int		len[2];
	int		i;
	int		j;

	i = 0;
	len[0] = 0;
	len[1] = 0;
	while (arguments[i++] != '=')
		len[0]++;
	while (arguments[i++])
		len[1]++;
	tmp[0] = (char *)malloc(sizeof(char) * (len[0] + 1));
	tmp[1] = (char *)malloc(sizeof(char) * (len[1] + 1));
	i = -1;
	while (arguments[++i] != '=')
		tmp[0][i] = arguments[i];
	tmp[0][i] = '\0';
	j = -1;
	while (arguments[i])
		tmp[1][++j] = arguments[i++];
	tmp[1][j] = '\0';
	if (find_env(vars->env, tmp[0]) >= 0)
	{
		tmp[2] = vars->env[find_env(vars->env, tmp[0])];
		vars->env[find_env(vars->env, tmp[0])] = \
			ft_strdup(arguments);
		free((tmp[2]));
	}
	else
		add_new_env(vars, arguments);
	free(tmp[0]);
	free(tmp[1]);
	return (0);
}

void	check_export(t_env_var *vars, t_simpleCommand *cur_command)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (cur_command->number_of_arguments > ++i)
	{
		if (ft_isalpha(*cur_command->arguments[i]) == false)
		{
			print_err(MSG_ERR_INVAL_ENVNAME, cur_command->arguments[i], false);
			flag = 1;
			continue ;
		}
		else if (find_equal(cur_command->arguments[i]))
			continue ;
		available_var(vars, cur_command->arguments[i]);
	}
	if (flag)
		vars->status = 1;
	else
		vars->status = 0;
}

int	ft_export(t_env_var *vars, t_simpleCommand *cur_command)
{
	int	i;

	if (cur_command->number_of_arguments == 1)
	{
		print_export(vars);
		return (1);
	}
	else
		check_export(vars, cur_command);
	return (0);
}

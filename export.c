#include "minishell.h"

void	available_var_extra(int *i, int **len, char *arguments, char ***tmp)
{
	(*len) = malloc(sizeof(int) * 2);
	(*tmp) = malloc(sizeof(char *) * 3);
	*i = 0;
	(*len)[0] = 0;
	(*len)[1] = 0;
	while (arguments[(*i)++] != '=')
		(*len)[0]++;
	while (arguments[(*i)++])
		(*len)[1]++;
	(*tmp)[0] = (char *)malloc(sizeof(char) * ((*len)[0] + 1));
	(*tmp)[1] = (char *)malloc(sizeof(char) * ((*len)[1] + 1));
	*i = -1;
	while (arguments[++(*i)] != '=')
		(*tmp)[0][*i] = arguments[*i];
	(*tmp)[0][*i] = '\0';
}

int	available_var(t_env_var *vars, char *arguments)
{
	char	**tmp;
	int		*len;
	int		i;
	int		j;

	available_var_extra(&i, &len, arguments, &tmp);
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
	free_pointers(&tmp, &len);
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
	if (cur_command->number_of_arguments == 1)
	{
		print_export(vars);
		return (1);
	}
	else
		check_export(vars, cur_command);
	return (0);
}

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

int	available_var(t_env_var *vars, t_simpleCommand *cur_command)
{
	char	*tmp[2];
	int		len[2];
	int		i;
	int		j;

	i = 0;
	len[0] = 0;
	len[1] = 0;
	while (cur_command->arguments[1][i++] != '=')
		len[0]++;
	while (cur_command->arguments[1][i++])
		len[1]++;
	printf("len[0] = %d, len[1] = %d\n", len[0], len[1]);
	tmp[0] = (char *)malloc(sizeof(char) * (len[0] + 1));
	tmp[1] = (char *)malloc(sizeof(char) * (len[1] + 1));
	i = -1;
	while (cur_command->arguments[1][++i] != '=')
		tmp[0][i] = cur_command->arguments[1][i]; 
	//printf("tmp0 = %s, tmp1 = %s\n", tmp[0], tmp[1]);   
	tmp[0][i] = '\0';
	j = 0;
	while (cur_command->arguments[1][i])
		tmp[1][j++] = cur_command->arguments[1][i++];
	tmp[1][j] = '\0';
	printf("tmp0 = %s, tmp1 = %s\n", tmp[0], tmp[1]);
	return (0);
}

int	ft_export(t_env_var *vars, t_command *args, t_simpleCommand *cur_command)
{
	int	i;

	//printf("ARGS = %d", cur_command->number_of_arguments);
	if (cur_command->number_of_arguments == 1)
	{
		print_export(vars);
		return (1);
	}
	else if (cur_command->number_of_arguments == 2 && \
			!find_equal(cur_command->arguments[1]))
	{
		//write(1, "1", 1);
		available_var(vars, cur_command);
	}
	if (find_env(vars->env, cur_command->arguments[1]) >= 0)
		printf("OK = %d\n", find_env(vars->env, cur_command->arguments[1]));
	printf("NOT OK\n");
	return (0);
}

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

int add_new_env(t_env_var *vars, char* new)
{
	int		i;
	int		c;
	char	**tmp;

	i = -1;
	c = 1;
	while(vars->env[++i])
		c++;
	tmp = malloc(sizeof(char *) * (c + 1));
	tmp[c] = NULL;
	i = -1;
	while(vars->env[++i])
		tmp[i] = ft_strdup(vars->env[i]);
	tmp[i] = ft_strdup(new);
	i = -1;
	while(vars->env[++i])
		free(vars->env[i]);
	free(vars->env);
	vars->env = tmp;
	
}

int	available_var(t_env_var *vars, t_simpleCommand *cur_command)
{
	char	*tmp[3];
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
	//printf("len[0] = %d, len[1] = %d\n", len[0], len[1]);
	tmp[0] = (char *)malloc(sizeof(char) * (len[0] + 1));
	tmp[1] = (char *)malloc(sizeof(char) * (len[1] + 1));
	i = -1;
	while (cur_command->arguments[1][++i] != '=')
		tmp[0][i] = cur_command->arguments[1][i]; 
	//printf("tmp0 = %s, tmp1 = %s\n", tmp[0], tmp[1]);   
	tmp[0][i] = '\0';
	j = -1;
	while (cur_command->arguments[1][i])
		tmp[1][++j] = cur_command->arguments[1][i++];
	tmp[1][j] = '\0';
	//printf("tmp0 = %s, tmp1 = %s\n", tmp[0], tmp[1]);
	if (find_env(vars->env, tmp[0]) >= 0){
		//printf("OK = %s\n", vars->env[find_env(vars->env, tmp[0])]);
		tmp[2] = vars->env[find_env(vars->env, tmp[0])];
		vars->env[find_env(vars->env, tmp[0])] = ft_strdup(cur_command->arguments[1]);
		free((tmp[2]));
		//vars->env[find_env(vars->env, tmp[0])] = ft_strdup(cur_command->arguments[1]);
		//printf("OK2 = %s\n", vars->env[find_env(vars->env, tmp[0])]);
		
		//printf("OK3 = %s\n", vars->env[find_env(vars->env, tmp[0])]);
	}
	else
	{
		add_new_env(vars, cur_command->arguments[1]);
		//printf("NOT OK\n");
	}
	free(tmp[0]);
	free(tmp[1]);
	return (0);
}

int	ft_export(t_env_var *vars, t_simpleCommand *cur_command)
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
	
	return (0);
}

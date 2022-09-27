#include "minishell.h"

void	clean_vars(t_env_var *vars)
{
	int	i;

	i = -1;
	while (vars->path[++i])
	{
		free(vars->path[i]);
	}
	free(vars->path[i]);
	free(vars->path);
}

void	ft_clean(t_command *command, t_env_var *vars)
{
	int	i;
	int	j;

	i = 0;
	free(command->cmd);
	while (command->simple_commands[i])
	{
		free(command->simple_commands[i]->in_file);
		free(command->simple_commands[i]->out_file);
		j = 0;
		while (command->simple_commands[i]->arguments[j])
		{
			free(command->simple_commands[i]->arguments[j]);
			j++;
		}
		free(command->simple_commands[i]->arguments);
		free(command->simple_commands[i]);
		i++;
	}
	free(command->simple_commands);
	free(command);
	clean_vars(vars);
}

void	last_clean(t_env_var *vars)
{
	int	i;

	i = -1;
	while (vars->env[++i])
		free(vars->env[i]);
	free(vars->env[i]);
	free(vars->env);
	close(vars->stdin_fd);
	close(vars->stdout_fd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	close(19);
	close(20);
}

int	check_alphas(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (ft_isalpha(s[i]) == 1 || ft_isalnum(s[i]) == 0)
			return (1);
	}
	return (0);
}

int	ft_exit(t_env_var *vars, t_simpleCommand *cur_command)
{
	if (cur_command->number_of_arguments > 2)
	{
		vars->status = 1;
		vars->exit = 0;
		ft_putendl_fd("exit: too many arguments", 2);
		return (0);
	}
	else if (cur_command->number_of_arguments == 1)
		vars->exit = 0;
	else if (check_alphas(cur_command->arguments[1]))
		vars->exit = 2;
	else
		vars->exit = (unsigned char) ft_atoi(cur_command->arguments[1]);
	vars->status = -1;
	return (1);
}

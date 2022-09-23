#include "minishell.h"

int	clean_vars(t_env_var *vars)
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

int	ft_clean(t_command *command, t_env_var *vars)
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

int	last_clean(t_command *args, t_env_var *vars)
{
	int	i;

	i = -1;
	while (vars->env[++i])
		free(vars->env[i]);
	free(vars->env[i]);
	free(vars->env);
	close(vars->stdin_fd);
	close(vars->stdout_fd);
}

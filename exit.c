#include "minishell.h"

int clean_vars(t_env_var *vars)
{
	int	i;

	i = -1;
	while(vars->path[++i])
	{
		free(vars->path[i]);
	}
	free(vars->path[i]);
	free(vars->path);
}

//int ft_clean(t_command *args, t_env_var *vars)
//{
//    int	i[2];
//	int	j;
//
//	i[0] = -1;
//	//printf("!!!!!! %d", args->number_of_simple_commands);
//	//printf("2222222 = %p\n", args);//////////////////////////
//    while (++i[0] < args->number_of_simple_commands)
//	{
//		i[1] = 0;
//		free(args->simple_commands[i[0]]->in_file);
//		free(args->simple_commands[i[0]]->out_file);
//		while (++i[1] < args->simple_commands[i[0]]->number_of_arguments)
//			free(args->simple_commands[i[0]]->arguments[i[1]]);
//		free(args->simple_commands[i[0]]->arguments[i[1]]);
//		free(args->simple_commands[i[0]]->arguments);
//		free(args->simple_commands[i[0]]);
//	}
//	free(args->simple_commands[i[0]]);
//	free(args->cmd);
//	free(args->simple_commands);
//	
//}
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

int last_clean(t_command *args, t_env_var *vars)
{
	int	i;

	i = -1;
	while(vars->env[++i])
		free(vars->env[i]);
	free(vars->env[i]);
	free(vars->env);
	//i = -1;
	//while(vars->path[++i])
	//	free(vars->path[i]);
	//free(vars->path[i]);
	//free(vars->path);
	close(vars->stdin_fd);
	close(vars->stdout_fd);

		
}
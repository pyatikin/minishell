#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "minishell.h"

int	check_command_extra(t_simpleCommand *cur_command,
		t_env_var *vars, char **com, t_command *args)
{
	*com = cur_command->arguments[0];
	if (cur_command->in_file_type == read_input)
	{
		set_signals(3, 1, vars);
		do_read_input(ft_strdup(cur_command->in_file), cur_command);
		set_signals(1, 0, vars);
	}
	if (ft_strcmp(*com, "echo\0") == 0 || ft_strcmp(*com, "cd\0") == 0 || \
	ft_strcmp(*com, "pwd\0") == 0 || ft_strcmp(*com, "export\0") == 0 || \
	ft_strcmp(*com, "unset\0") == 0 || ft_strcmp(*com, "env\0") == 0 || \
	ft_strcmp(*com, "exit\0") == 0)
	{
		build_in(*com, vars, args, cur_command);
		return (1);
	}
	return (0);
}

int	ret_func(char *com, t_env_var *vars)
{
	ft_putstr_fd(com, vars->stdout_fd);
	ft_putstr_fd(": command not found\n", vars->stdout_fd);
	vars->status = 127;
	return (1);
}

int	check_command(
	t_simpleCommand *cur_command, t_env_var *vars, t_command *args)
{
	char		*com;
	char		*tmp;
	int			k;

	k = -1;
	if (check_command_extra(cur_command, vars, &com, args))
		return (0);
	while (vars->path[++k])
	{
		tmp = check_exec(vars->path[k], cur_command->arguments[0]);
		if (tmp)
		{
			execute_command(tmp, cur_command->arguments, vars);
			free(tmp);
			return (0);
		}
	}
	tmp = check_exec(NULL, cur_command->arguments[0]);
	if (tmp)
	{
		execute_command(tmp, cur_command->arguments, vars);
		free(tmp);
		return (0);
	}
	return (ret_func(com, vars));
}

int	back_redirections(t_env_var *env)
{
	dup2(env->stdin_fd, STDIN_FILENO);
	dup2(env->stdout_fd, STDOUT_FILENO);
	return (0);
}

int	exec_loop(t_command *args, t_env_var *vars)
{
	int	i;

	i = 0;
	while (i < args->number_of_simple_commands)
	{
		do_redirections(args, i, vars);
		do_db_redirections(args, i);
		get_db_redirections(args, i);
		check_command(args->simple_commands[i], vars, args);
		back_redirections(vars);
		if (vars->status)
			break ;
		i++;
	}
	return (0);
}

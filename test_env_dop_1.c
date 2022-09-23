#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "minishell.h"

int	do_db_redirections(t_command *args, int i)
{
	if (!(args->simple_commands[i]->out_file == NULL && \
			args->number_of_simple_commands > i + 1 && \
			args->simple_commands[i + 1]->in_file == NULL))
		return (1);
	pipe(args->simple_commands[i]->db_fd);
	dup2(args->simple_commands[i]->db_fd[1], STDOUT_FILENO);
	close(args->simple_commands[i]->db_fd[1]);
	return (0);
}

int	get_db_redirections(t_command *args, int i)
{
	if (i > 0 && args->simple_commands[i - 1]->out_file == NULL && \
		args->simple_commands[i]->in_file == NULL)
	{
		dup2(args->simple_commands[i - 1]->db_fd[0], STDIN_FILENO);
		close(args->simple_commands[i - 1]->db_fd[0]);
	}
	return (0);
}

int	do_redirections(t_command *args, int i, t_env_var *vars)
{
	if (args->simple_commands[i]->in_file_type == 1)
		args->simple_commands[i]->in_fd = \
		open(args->simple_commands[i]->in_file, O_RDONLY | O_CREAT);
	else if (args->simple_commands[i]->in_file_type == 2)
		args->simple_commands[i]->in_fd = vars->stdin_fd;
	else
		args->simple_commands[i]->in_fd = vars->stdin_fd;
	if (args->simple_commands[i]->out_file_type == 1)
		args->simple_commands[i]->out_fd = open(args->\
		simple_commands[i]->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (args->simple_commands[i]->out_file_type == 2)
		args->simple_commands[i]->out_fd = open(args->\
		simple_commands[i]->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		args->simple_commands[i]->out_fd = vars->stdout_fd;
	if (dup2(args->simple_commands[i]->in_fd, STDIN_FILENO) == -1
		|| dup2(args->simple_commands[i]->out_fd, STDOUT_FILENO) == -1)
		return (1);
	if (args->simple_commands[i]->in_fd != vars->stdin_fd)
		close(args->simple_commands[i]->in_fd);
	if (args->simple_commands[i]->out_fd != vars->stdout_fd)
		close(args->simple_commands[i]->out_fd);
	return (0);
}

int	execute_command(char *tmp, char **arg, t_env_var *vars)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		vars->status = execve(tmp, arg, vars->env);
	else if (pid < 0)
		return (-1);
	waitpid(pid, &status, 0);
	return (0);
}

int	build_in(
	char *com, t_env_var *vars, t_command *args, t_simpleCommand *cur_command)
{
	if (ft_strcmp(com, "echo\0") == 0)
		return (ft_echo((cur_command->arguments)));
	else if (ft_strcmp(com, "cd\0") == 0)
		return (ft_cd(cur_command->arguments, vars));
	else if (ft_strcmp(com, "pwd\0") == 0)
		return (ft_pwd());
	else if (ft_strcmp(com, "export\0") == 0)
		return (ft_export(vars, cur_command));
	else if (ft_strcmp(com, "unset\0") == 0)
		return (ft_unset(args, vars, cur_command));
	else if (ft_strcmp(com, "env\0") == 0)
		return (ft_env(vars, cur_command));
	else if (ft_strcmp(com, "exit\0") == 0)
		return (0);
	return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "minishell.h"
#define CLOSE "\001\033[0m\002"                 // Закрыть все свойства
#define BLOD  "\001\033[1m\002"                 // Подчеркнуть, жирным шрифтом, выделить
//#define BEGIN(x,y) "\001\033["#x";"#y"m\002"    // x: background, y: foreground
#define MYSHELL "Myshell > "

int	find_env(char **env, char *s)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], s, ft_strlen(s)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	count_colomns(char *s)
{
	int	i;

	i = 1;
	while (*s)
	{
		if (*s == ':')
			i++;
		s++;
	}
	return (i);
}

void	make_path_vector(char *path, char **path_vector, int l)
{
	int		i;
	char	*tmp;

	path = ft_substr(path, 0, ft_strlen(path));
	while (*path)
	{
		//write(1,"1\n", 2);
		i = 0;
		while (*path && *(path++) != ':')
			i++;
		if (*(--path) != ':')
			path++;
		path = path - i;
		//printf("%d)%s\n\n",i, path);
		(path_vector)[--l] = ft_substr(path, 0, i);
		//printf("%s", path_vector[l]);
		tmp = path;
		path = ft_substr(tmp, i + 1, ft_strlen(tmp) + 1);		
		free(tmp);		
	}
	free(path);
}

char	*check_exec(char *dir, char *cmd)
{
	char		*all;
	struct stat	sb;

	all = NULL;
	if (dir != NULL && (cmd[0] == '/' || cmd[0] == '.'))
		return (NULL);
	if (dir)
	{
		if (dir[ft_strlen(dir)] != '/')
			dir = ft_strjoin(dir, "/\0");
	}
	all = ft_strjoin(dir, cmd);
	if(ft_strcmp(dir, "/") != 0)
		free(dir);
	//printf("!!!!!!!!!   %s\n", all);
	if (access(all, F_OK) == 0)
	{
		if (stat(all, &sb) != 0 && ((sb.st_mode & S_IFMT) != S_IFREG ||\
			(sb.st_mode & S_IFMT) != S_IFDIR))
		{
			printf("%s: No such file or directory\n", all);
			free(all);
			return (NULL);
		}
		return (all);
	}
	free(all);
	return (NULL);
}

int	do_db_redirections(t_command *args, int i, t_env_var *vars)
{
	//printf("NUM = %d", args->number_of_simple_commands);
	if (!(args->simple_commands[i]->out_file == NULL && \
			args->number_of_simple_commands > i + 1 && \
			args->simple_commands[i + 1]->in_file == NULL))
		return (1);
	//write(1, "1\n", 2);
	pipe(args->simple_commands[i]->db_fd);
	//printf("fd[0] = %d,\t fd[1] = %d", args->simple_commands[i]->db_fd[0], args->simple_commands[i]->db_fd[1]);
	dup2(args->simple_commands[i]->db_fd[1], STDOUT_FILENO);
	close(args->simple_commands[i]->db_fd[1]);
	return (0);
}

int	get_db_redirections(t_command *args, int i, t_env_var *vars)
{
	if (i > 0 && args->simple_commands[i - 1]->out_file == NULL && \
		args->simple_commands[i]->in_file == NULL)
	{
		//printf("fd[0] = %d,\t fd[1] = %d", args->simple_commands[i]->db_fd[0], args->simple_commands[i]->db_fd[1]);
		dup2(args->simple_commands[i - 1]->db_fd[0], STDIN_FILENO);
		close(args->simple_commands[i - 1]->db_fd[0]);
	}
	return (0);
}

int	do_redirections(t_command *args, int i, t_env_var *vars)
{
	int	in;
	int	out;
	//TODO IN < and << 
	if (args->simple_commands[i]->in_file_type == 1)
		args->simple_commands[i]->in_fd = open(args->simple_commands[i]->in_file, O_RDONLY | O_CREAT);
	else if (args->simple_commands[i]->in_file_type == 2)
		//args->simple_commands[i]->in_fd = open(args->simple_commands[i]->in_file, O_RDONLY | O_CREAT);
		args->simple_commands[i]->in_fd = vars->stdin_fd;
	else 
		args->simple_commands[i]->in_fd = vars->stdin_fd;
	if	(args->simple_commands[i]->out_file_type == 1)
		args->simple_commands[i]->out_fd = open(args->simple_commands[i]->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (args->simple_commands[i]->out_file_type == 2)
		args->simple_commands[i]->out_fd = open(args->simple_commands[i]->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		args->simple_commands[i]->out_fd = vars->stdout_fd;
	if(dup2(args->simple_commands[i]->in_fd, STDIN_FILENO) == -1 ||
		dup2(args->simple_commands[i]->out_fd, STDOUT_FILENO) == -1)
		return (1);
	//printf("before: fd_in = %d, fd_out = %d", args->simple_commands[i]->in_fd, args->simple_commands[i]->out_fd);
	if (args->simple_commands[i]->in_fd != vars->stdin_fd)
		close(args->simple_commands[i]->in_fd);
	if (args->simple_commands[i]->out_fd != vars->stdout_fd)
		close(args->simple_commands[i]->out_fd);
	return (0);
}
int execute_command(char	*tmp, char **arg, t_env_var *vars)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		//printf("STATUS = %d\n", vars->status);
		vars->status = execve(tmp, arg, vars->env);
	}
	else if (pid < 0)
		return (-1);
	waitpid(pid, &status, 0);
	//printf("STATUS = %d\n", WEXITSTATUS (status));
	//rl_on_new_line();
	//perror("execve");
}

int	build_in(char *com, t_env_var *vars,t_command *args, t_simpleCommand *cur_command)
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
}
int	check_command(t_simpleCommand *cur_command, t_env_var *vars, t_command *args)
{
	char		*com;
	struct stat	sb;
	char		*tmp;
	int			k;

	k = 0;
	com = cur_command->arguments[0];
	if (cur_command->in_file_type == read_input)
	{
		//set_signals(2, 0);
		do_read_input(ft_strdup(cur_command->in_file), cur_command);
		//set_signals(1, 0);
	}
	if (ft_strcmp(com, "echo\0") == 0 || ft_strcmp(com, "cd\0") == 0 || \
	ft_strcmp(com, "pwd\0") == 0 || ft_strcmp(com, "export\0") == 0 || \
	ft_strcmp(com, "unset\0") == 0 || ft_strcmp(com, "env\0") == 0 || \
	ft_strcmp(com, "exit\0") == 0)
	{ //TODO исправить на strcmp
		build_in(com, vars, args, cur_command);
		return (0);
	}
	while (vars->path[k])
	{
		if (tmp = check_exec(vars->path[k], cur_command->arguments[0]))
		{
			//return (3); //remake
			//execve(tmp, args->simple_commands[0]->arguments, vars->env);
			execute_command(tmp, cur_command->arguments, vars); 
			free(tmp);
			return (0);
		}
		k++;
	}
	if (tmp = check_exec(NULL, cur_command->arguments[0]))
	{
		//return (3); //remake
		//execve(tmp, args->simple_commands[0]->arguments, vars->env);
		execute_command(tmp, cur_command->arguments, vars);
		free(tmp);
		return (0);
	}
	printf("%s: command not found\n", com);
	return (1);
}

int	back_redirections(t_command *args, int i, t_env_var *env)
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
		//printf("fd[0] = %d,\t fd[1] = %d", args->simple_commands[i]->db_fd[0], args->simple_commands[i]->db_fd[1]);
		//printf("QQQQQQQQQ = %p", args->simple_commands[i+1]);	
		do_db_redirections(args, i, vars);
		get_db_redirections(args, i, vars);
		//printf("in = %d, out = %d\n", args->simple_commands[i]->in_fd, args->simple_commands[i]->out_fd);
		//set_signals(3, 1);
		check_command(args->simple_commands[i], vars, args);
		//set_signals(1, 0);
		back_redirections(args, i, vars);
		//args->cmd = readline(BEGIN(30, 36) MYSHELL CLOSE);
		//if (!args->cmd)
		//{
		//	printf("exit\n");
		//	return (0);
		//}
		//if (ft_strlen(args->cmd))
		//	add_history(args->cmd);
		//args->cmd = ft_chng_line(&(args->cmd));
		//if (check_cmd((args->cmd)) != 0)
		//	continue;
		////write(1, args->cmd, sizeof(args->cmd));
		//
		//args = parsbody(args->cmd);
		//printf("|%s|\n", args->cmd);
		///////////////////| exec |/////////////////////////
		//int k = 0;
		//char *tmp;
		//while(vars->path[k])
		//{
		//if(tmp = check_exec(vars->path[k], args->simple_commands[0]->arguments[0]))
//		//	
//		//		execve(tmp, args->simple_commands[0]->arguments, vars->env);
//
		//	k++;
		//}
		i++;
	}
}

int	start_path(t_command *args, t_env_var *vars)
{
	
	//printf("%s\n", (vars->env[find_env(vars->env, "PATH")]));
	if (find_env(vars->env, "PATH") != -1)
	{
	vars->path = malloc(sizeof(char *) * \
	(count_colomns(vars->env[find_env(vars->env, "PATH")]) + 1));
	vars->path[count_colomns(vars->env[find_env(vars->env, "PATH")])] = NULL;
	make_path_vector(vars->env[find_env(vars->env, "PATH")] + 5, vars->path, \
	count_colomns(vars->env[find_env(vars->env, "PATH")]));
	}
	else
		vars->path = calloc(sizeof(char *), 1);
	//int l = count_colomns(vars->env[find_env(vars->env, "PATH")]);
	//while(l--)
	//{
	//	printf("%d)\t%s\n",l, vars->path[l]);
	//}
	//exec_loop(args, vars);
	//printf("NUM = %d", args->number_of_simple_commands);
}

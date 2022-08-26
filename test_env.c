#include <stdio.h>
# include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "minishell.h"
#define CLOSE "\001\033[0m\002"                 // Закрыть все свойства
#define BLOD  "\001\033[1m\002"                 // Подчеркнуть, жирным шрифтом, выделить
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"    // x: background, y: foreground
#define MYSHELL "Myshell > "

int	find_env(char **env, char *s)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if(ft_strncmp(env[i], s, ft_strlen(s)) == 0)
			return (i);
		i++;
	}
	return (-1);
}
int	count_colomns(char *s)
{
	int i;

	i = 1;
	while(*s)
	{
		if(*s == ':')
			i++;
		s++;
	}
	return (i);
}
void make_path_vector(char* path, char** path_vector, int l)
{
	int		i;
	char	*tmp;

	while(*path)
	{
		//write(1,"1\n", 2);
		
		i = 0;
		while(*path && *(path++) != ':')
			i++;
		if(*(--path) != ':')
			path++;
		path = path - i;
		printf("%d)%s\n\n",i, path);
		(path_vector)[--l] = ft_substr(path, 0, i);
		//printf("%s", path_vector[l]);
		tmp = path;
		path = ft_substr(tmp, i+1, ft_strlen(tmp)+1);				
	}
}

char *check_exec(char *dir, char *cmd)
{
	char 		*all;
	struct stat	sb;

	if(dir[ft_strlen(dir)] != '/')
		dir = ft_strjoin(dir, "/\0");
	all = ft_strjoin(dir, cmd);
	if (access(all, F_OK) == 0)
	{
		if (stat(all, &sb) > 0 && ((sb.st_mode & S_IFMT) != S_IFREG || (sb.st_mode & S_IFMT) != S_IFDIR))
		{
			printf("%s: No such file or directory\n", all);
			free(all);
			return (NULL);
		}
		return (all);
	}
	return(NULL);
}

int	loop(t_command *args, t_env_var *vars, char **env)
{
	while (1)
	{
		args->cmd = readline(BEGIN(30, 36) MYSHELL CLOSE);
		if (!args->cmd)
		{
			printf("exit\n");
			return (0);
		}
		if (ft_strlen(args->cmd))
			add_history(args->cmd);
		args->cmd = ft_chng_line(&(args->cmd));
		if (check_cmd((args->cmd)) != 0)
			continue;
		//write(1, args->cmd, sizeof(args->cmd));
		
		args = parsbody(args->cmd);
		printf("|%s|\n", args->cmd);



		///////////////////| exec |/////////////////////////
		int k = 0;
		char *tmp;
		while(vars->path[k])
		{
			if(tmp = check_exec(vars->path[k], args->simple_commands[0]->arguments[0]))
			
				execve(tmp, args->simple_commands[0]->arguments, env);

			k++;
		}
	}
}
//int	main(int argc, char **argv, char **env)
//{
//	t_command	args;
//	t_env_var vars;
//	
//	printf("%s\n", (env[find_env(env, "PATH")]));
//	vars.path = malloc(sizeof(char*)*count_colomns(env[find_env(env, "PATH")]));
//	make_path_vector(env[find_env(env, "PATH")]+5, vars.path, count_colomns(env[find_env(env, "PATH")]));
//	int l = count_colomns(env[find_env(env, "PATH")]);
//	while(l--)
//	{
//		printf("%d)\t%s\n",l, vars.path[l]);
//	}
//	loop(&args, &vars, env);
//}
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "minishell.h"

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
		i = 0;
		while (*path && *(path++) != ':')
			i++;
		if (*(--path) != ':')
			path++;
		path = path - i;
		(path_vector)[--l] = ft_substr(path, 0, i);
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
	if (dir && dir[ft_strlen(dir)] != '/')
		dir = ft_strjoin(dir, "/\0");
	all = ft_strjoin(dir, cmd);
	if (ft_strcmp(dir, "/") != 0)
		free(dir);
	if (access(all, F_OK) == 0)
	{
		if (stat(all, &sb) != 0 && ((sb.st_mode & S_IFMT) != S_IFREG || \
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

int	start_path(t_env_var *vars)
{
	vars->status = 0;
	if (find_env(vars->env, "PATH") != -1)
	{
		vars->path = malloc(sizeof(char *) * \
		(count_colomns(vars->env[find_env(vars->env, "PATH")]) + 1));
		vars->path[count_colomns(vars->env[find_env(vars->env, \
		"PATH")])] = NULL;
		make_path_vector(vars->env[find_env(vars->env, "PATH")] + 5, \
		vars->path, count_colomns(vars->env[find_env(vars->env, "PATH")]));
	}
	else
		vars->path = calloc(sizeof(char *), 1);
	return (0);
}

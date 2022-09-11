#include "minishell.h"

int	ft_dollar_leng(int i, char *pipe_line)
{
	int	j;

	j = 0;
	i++;
	while (pipe_line[i])
	{
		if (ft_isalnum(pipe_line[i]) == 0)
			break ;
		i++;
		j++;
	}
	return (j);
}

char	*ft_env_var(int i, char *pipe_line, int k, t_command *command)
{
	char	*res;
	int		j;

	j = 0;
	i++;
	res = NULL;
	res = (char *)malloc(k + 1);
	res[k] = '\0';
	while (j < k)
	{
		res[j] = pipe_line[i + j];
		j++;
	}
	res = ft_find_env_var(&res, command->env);
	return (res);
}

char	*ft_find_env_var(char **var, char **env)
{
	int		i;
	char	*res;
	int		k;
	int		m;

	ft_zero_var(&i, &k, &m, &res);
	i = find_env(env, *var);
	if (i != -1)
	{
		while (env[i][k])
		{
			if (env[i][k] == '=')
				break ;
			k++;
		}
		free(*var);
		*var = NULL;
		res = (char *)malloc(ft_strlen(env[i]) - k);
		res[ft_strlen(env[i]) - k - 1] = '\0';
		k++;
		while (env[i][k])
		{
			res[m] = env[i][k];
			k++;
			m++;
		}
	}
	return (res);
}

char	*ft_pipe_line_chng(char **pipe_line, char *res, int *i_k, t_command *command)
{
	int		size;
	int		t;
	char	*new_pl;
	int		del;

	del = 0;
	t = 0;
	size = ft_strlen(*pipe_line) + ft_strlen(res) - i_k[1] - 1;
	new_pl = (char *)malloc(size + 1);
	new_pl[size] = '\0';
	while (t < size)
	{
		if (t < i_k[0])
			new_pl[t] = (*pipe_line)[t];
		else if (t >= i_k[0] && t < i_k[0] + ft_strlen(res))
			new_pl[t] = res[t - i_k[0]];
		else
			new_pl[t] = (*pipe_line)[ft_strlen(*pipe_line) - (size - t)];
		t++;
	}
	while (del < command->tmp)
	{
		del++;
		(*pipe_line)--;
	}
	command->tmp=0;
	free(*pipe_line);
	return (new_pl);
}

char	*ft_dollar(char **pipe_line, t_command *command)
{
	int		i_k[2];
	char	*res;

	i_k[0] = 0;
	i_k[1] = 0;
	while ((*pipe_line)[i_k[0]] && (*pipe_line)[i_k[0]] != '|' \
			&& (*pipe_line)[i_k[0]] != '<' && (*pipe_line)[i_k[0]] != '>')
	{
		if ((*pipe_line)[i_k[0]] == '$')
		{
			i_k[1] = ft_dollar_leng(i_k[0], *pipe_line);
			res = ft_env_var(i_k[0], *pipe_line, i_k[1], command);
			*pipe_line = ft_pipe_line_chng(pipe_line, res, i_k, command);
			i_k[0] = i_k[0] + ft_strlen(res);
		}
		else
			i_k[0]++;
	}
	return (*pipe_line);
}

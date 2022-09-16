#include "minishell.h"

int	ft_strlen_space(char *str)
{
	int		i;
	char	k;

	k = '\0';
	i = 0;
	if (ft_quotes(str) == 0)
	{
		while (str[i] && str[i] != ' ' && str[i] != '|')
			i++;
	}
	else
	{
		k = str[0];
		i++;
		while (str[i] && str[i] != k)
			i++;
		i--;
	}
	return (i);
}

int	ft_flags(char *pipe_line, int flag, int i)
{
	if (pipe_line[i] == '\'' && flag == 0)
		flag = 1;
	else if (pipe_line[i] == '\'' && flag == 1)
		flag = 0;
	if (pipe_line[i] == '\"' && flag == 0)
		flag = 2;
	else if (pipe_line[i] == '\"' && flag == 2)
		flag = 0;
	return (flag);
}

int	ft_chek_leng_com(char *pipe_line)
{
	int	i;
	int	k;
	int	flag;

	i = 0;
	k = 0;
	flag = 0;
	while (pipe_line[i] && pipe_line[i] != '|')
	{
		flag = ft_flags(pipe_line, flag, i);
		if ((pipe_line[i] == '>' || pipe_line[i] == '<') && flag == 0)
		{
			k--;
			if (pipe_line[i + 1] && pipe_line[i] == pipe_line[i+1])
				i++;
			if (pipe_line[i + 1] && pipe_line[i + 1] == ' ')
				k--;
		}
		if (pipe_line[i] != ' ' && flag == 0)
		{
			while (pipe_line[i] && pipe_line[i] != ' ' && pipe_line[i] != '|')
				i++;
			k++;
		}
		else
			i++;
	}
	return (k);
}

int	ft_alloc_for_pattern(int n, char *pipe_line, t_command *command)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (n == 0)
	{
		while (pipe_line[j] && pipe_line[j] != ' ' && pipe_line[j] \
			!= '|' && pipe_line[j] != '>' && pipe_line[j] != '<')
			j++;
	}
	ft_alloc_dup(n, &pipe_line, &j, command);
	return (j);
}

void	ft_copy_pipe(char **pipe_line, t_command *command, int i, int k)
{
	int		j;
	char	f;

	f = 0;
	j = 0;
	if (ft_quotes(*pipe_line) == 0)
	{
		while (**pipe_line && **pipe_line != ' ' && **pipe_line != \
			'|' && **pipe_line != '>' && **pipe_line != '<' && ++command->tmp)
		{
			command->simple_commands[i]->arguments[k][j] = **pipe_line;
			fkng_bll_shit(pipe_line, &j);
		}
	}
	else
	{
		ft_cp_dop(command, &f, pipe_line);
		while (**pipe_line && **pipe_line != f && ++command->tmp)
		{
			command->simple_commands[i]->arguments[k][j] = **pipe_line;
			fkng_bll_shit(pipe_line, &j);
		}
		(*pipe_line)++;
	}
}

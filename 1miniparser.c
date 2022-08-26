#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

t_command	*parsbody(char *pipe_line);
void		ft_find_pipe(char *pipe_line, t_command *command);
char		*ft_pars_simple(char *pipe_line, t_command *command);
void		ft_file_find(char **pipe_line, t_command *command, int k);

//int	main(void)
//{
//	parsbody("cat \"file2.txt lkm\" < ljhjl | sort | uniq >> list4.txt >lkkj >>kk << hjl <jh");
//	return (0);
//}

t_command	*parsbody(char *pipe_line)
{
	int			j;
	int			i;
	t_command	*command;

	i = 0;
	command = (t_command *)malloc(sizeof(t_command));
	command->cmd = pipe_line;
	ft_find_pipe(pipe_line, command);
	command->simple_commands = (t_simpleCommand **)malloc(sizeof
			(t_simpleCommand *) *(command->number_of_simple_commands + 1));
	while (i <= command->number_of_simple_commands)
	{
		command->simple_commands[i] = (t_simpleCommand *)
			malloc(sizeof(t_simpleCommand));
		i++;
	}
	command->simple_commands[command->number_of_simple_commands] = NULL;
	pipe_line = ft_pars_simple(pipe_line, command);

	//вывод структур
	i = 0;
	j = 0;
	while (command->simple_commands[i])
	{
		j = 0;
		while (command->simple_commands[i]->arguments[j])
		{
			printf("пайп: %d, позиция: %d, наименование: %s\n", i + 1, j + 1, command->simple_commands[i]->arguments[j]);
			j++;
		}
		printf("in: %d, %s\nout: %d, %s\n", command->simple_commands[i]->in_file_type, command->simple_commands[i]->in_file, command->simple_commands[i]->out_file_type, command->simple_commands[i]->out_file);
		i++;
	}
	printf("%s", pipe_line);
	return (command);
}

int	ft_strlen_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '|')
		i++;
	return (i);
}

void	ft_file_out(char **pipe_line, int *ch, int n, char **file)
{
	int	i;

	i = 0;
	*ch = n;
	(*pipe_line)++;
	while (**pipe_line == ' ')
		(*pipe_line)++;
	*file = (char *)malloc(ft_strlen_spaces(*pipe_line) + 1);
	(*file)[ft_strlen_spaces(*pipe_line)] = '\0';
	while (i < ft_strlen_spaces(*pipe_line))
	{
		(*file)[i] = (*pipe_line)[i];
		i++;
	}
	while (**pipe_line && (**pipe_line != ' ' \
	&& **pipe_line != '>' && **pipe_line != '<' && **pipe_line != '|'))
		(*pipe_line)++;
}

void	ft_file_find(char **pipe_line, t_command *command, int k)
{
	while (**pipe_line)
	{
		while(**pipe_line == ' ')
			(*pipe_line)++;
		if (**pipe_line && ((**pipe_line) == '|'))
			return ;
		if ((*pipe_line)[0] && (*pipe_line)[1] && \
			(*pipe_line)[0] == '>' && (*pipe_line)[1] != '>')
			ft_file_out(pipe_line, &command->simple_commands[k]->out_file_type, \
			1, &command->simple_commands[k]->out_file);
		if ((*pipe_line)[0] && (*pipe_line)[1] && \
			(*pipe_line)[0] == '>' && (*pipe_line)[1] == '>')
		{
			(*pipe_line)++;
			ft_file_out(pipe_line, &command->simple_commands[k]->out_file_type, \
			2, &command->simple_commands[k]->out_file);
		}
		if ((*pipe_line)[0] && (*pipe_line)[1] && \
			(*pipe_line)[0] == '<' && (*pipe_line)[1] != '<')
			ft_file_out(pipe_line, &command->simple_commands[k]->in_file_type, \
			1, &command->simple_commands[k]->in_file);
		if ((*pipe_line)[0] && (*pipe_line)[1] && \
			(*pipe_line)[0] == '<' && (*pipe_line)[1] == '<')
		{
			(*pipe_line)++;
			ft_file_out(pipe_line, &command->simple_commands[k]->in_file_type, \
			2, &command->simple_commands[k]->in_file);
		}
	}
	return ;
}

int	ft_chek_leng_com(char *pipe_line)
{
	int	i;
	int	k;

	i = 0;
	k = 1;
	if (pipe_line[0] == ' ')
			k--;
	while (pipe_line[i] && (pipe_line[i] != '|' \
		&& pipe_line[i] != '>' && pipe_line[i] != '<'))
	{
		if (pipe_line[i] == ' ')
			k++;
		if (pipe_line[i] && pipe_line[i + 1] && pipe_line[i] == ' ' \
		&& (pipe_line[i + 1] == '|' || pipe_line[i + 1] == '>' \
		|| pipe_line[i + 1] == '<'))
			k--;
		i++;
	}
	return (k);
}

void	*ft_dollar()
{
	printf("был найдет $ внутри двойных ковычек!");
}

int	ft_quotes(char *pipe_line)
{
	int	one;
	int two;
	int j;
	int flag[2];

	flag[0] = 0;
	flag[1] = 0;
	one = 0;
	two = 0;
	j = 0;
	while (pipe_line[j] && pipe_line[j] != ' ' && pipe_line[j] \
		!= '|' && pipe_line[j] != '>' && pipe_line[j] != '<')
	{
		j++;
		if (flag[1] == 1 && pipe_line[j-1] == '&')
			ft_dollar();
		if ((int)(pipe_line[j-1]) == 39)
		{
			if (flag[0] == 0 && flag[1] == 0)
				flag[0] = 1;
			else if (flag[0] == 1 && flag[1] == 0)
				flag[0] = 0;
			else continue;
			one++;
		}
		if (pipe_line[j-1] == 34)
		{
			if (flag[1] == 0 && flag[0] == 0)
				flag[1] = 1;
			else if (flag[1] == 1 && flag[0] == 0)
				flag[1] = 0;
			else continue;
			two++;
		}
		if (pipe_line[j] && pipe_line[j-1] == 92 && pipe_line[j] == 39)
			one--;
		if (pipe_line[j] && pipe_line[j-1] == 92 && pipe_line[j] == 34)
			two--;
	}
	//printf("1: %d, 2: %d\n", one, two);
	return (one + two);
}

int	ft_alloc_for_pattern(int n, char* pipe_line)
{
	int	j;

	j = 0;
	if (n == 0)
	{
		while (pipe_line[j] && pipe_line[j] != ' ' && pipe_line[j] \
			!= '|' && pipe_line[j] != '>' && pipe_line[j] != '<')
			j++;
	}
	if (n != 0)
	{
		if (*pipe_line == ' ')
			pipe_line++;
		if (pipe_line[0] == '\'')
		{
			j++;
			while (pipe_line[j] != '\'' || (pipe_line[j-1] && pipe_line[j - 1] == '\\' && pipe_line[j]=='\''))
				j++;
		}
		else if (pipe_line[0]=='\"')
		{
			j++;
			while (pipe_line[j] != '\"' || (pipe_line[j-1] && pipe_line[j - 1] == '\\' && pipe_line[j]=='\"'))
				j++;
		}
		j--;
	}
	return (j);
}

void	ft_copy_pipe(char **pipe_line, t_command *command, int i, int k)
{
	int		j;
	int		n;
	char	f;
	char	sl;

	f = 0;
	sl = 0;
	n = ft_quotes(*pipe_line);
	j = 0;
	if (n == 0)
	{
		while (**pipe_line && **pipe_line != ' ' \
			&& **pipe_line != '|' && **pipe_line != '>' && **pipe_line != '<')
		{
			command->simple_commands[i]->arguments[k][j] = **pipe_line;
			(*pipe_line)++;
			j++;
		}
	}
	else 
	{
		f = **pipe_line;
		(*pipe_line)++;
		while (**pipe_line && (**pipe_line != f || sl == '\\'))
		{
			if (**pipe_line == '\\')
			{
				sl = '\\';
				(*pipe_line)++;
				continue;
			}
			else sl = 0 ;
			command->simple_commands[i]->arguments[k][j] = **pipe_line;
			(*pipe_line)++;
			j++;
		}
		(*pipe_line)++;
	}
}

char	*ft_pars_simple(char *pipe_line, t_command *command)
{
	int	i;
	int	k;

	i = 0;
	while (i < command->number_of_simple_commands)
	{
		command->simple_commands[i]->arguments = (char **)
			malloc(sizeof(char *) * (ft_chek_leng_com(pipe_line) + 1));
		command->simple_commands[i]->in_file_type = 0;
		command->simple_commands[i]->in_file = NULL;
		command->simple_commands[i]->out_file = NULL;
		command->simple_commands[i]->out_file_type = 0;
		command->simple_commands[i]->arguments[ft_chek_leng_com(pipe_line)] = NULL;
		k = 0;
		while (1)
		{
			while (*pipe_line && *pipe_line == ' ')
				pipe_line++;
			if(*pipe_line && (*pipe_line == '<' || *pipe_line == '>'))
				ft_file_find(&pipe_line, command, i);
			if (*pipe_line && *pipe_line == '|')
			{
				pipe_line++;
				break ;
			}
			if (!pipe_line[0])
				break ;
			command->simple_commands[i]->arguments[k] = \
				(char *)malloc(sizeof(char) * (ft_alloc_for_pattern(ft_quotes(pipe_line), pipe_line) + 1));
			command->simple_commands[i]->arguments[k][ft_alloc_for_pattern(ft_quotes(pipe_line), pipe_line)] = '\0';
			ft_copy_pipe(&pipe_line, command, i, k);
			//printf("%s\n", pipe_line);
			k++;
			command->simple_commands[i]->number_of_arguments = k;
		}
		i++;
	}
	return (pipe_line);
}

void	ft_find_pipe(char *pipe_line, t_command *command)
{
	int	i;
	int	k;
	int flag;
	int besit;

	k = 0;
	flag = 0;
	i = 0;
	while (pipe_line[i])
	{
		besit = 0;
		if (pipe_line[i] == '\\')
		{
			besit = 1;
			i++;
		}
		if (pipe_line[i] == '\'' && flag == 0 && besit == 0)
			flag = 1;
		else if (pipe_line[i] == '\'' && flag == 1 && besit == 0)
			flag = -1;
		if (pipe_line[i] == '\"' && flag == 0 && besit == 0)
			flag = 2;
		else if (pipe_line[i] == '\"' && flag == 2 && besit == 0)
			flag = -2;
		if (pipe_line[i] == '|' && (flag == -1 || flag == -2 || flag == 0))
			k++;
		i++;
	}
	command->number_of_simple_commands = k + 1;
}

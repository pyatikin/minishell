#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

t_command	*parsbody(char *pipe_line);
void		ft_find_pipe(char *pipe_line, t_command *command);
char		*ft_pars_simple(char *pipe_line, t_command *command);
void		ft_file_find(char *pipe_line, t_command *command);

//int	main(void)
//{
//	parsbody(" cat file2.txt | sort | uniq >> list4.txt >lkkj >>kk << hjl <jh");
//	return (0);
//}

t_command	*parsbody(char *pipe_line)
{
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
	ft_file_find(pipe_line, command);
	printf("%s\n", command->simple_commands[0]->arguments[0]);
	printf("%s\n", command->simple_commands[0]->arguments[1]);
	printf("%s\n", command->simple_commands[1]->arguments[0]);
	printf("'%s'\n", command->simple_commands[2]->arguments[0]);
	printf("%d\n", command->out_file_type);
	printf("'%s'\n", command->out_file);
	printf("%d\n", command->input_file_type);
	printf("'%s'\n", command->input_file);
	return (command);
}

int	ft_strlen_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
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
	&& **pipe_line != '>' && **pipe_line != '<'))
		(*pipe_line)++;
}

void	ft_file_find(char *pipe_line, t_command *command)
{
	while (*pipe_line)
	{
		while (*pipe_line == ' ')
			pipe_line++;
		if (!(*pipe_line))
			break ;
		if (pipe_line[0] && pipe_line[1] && \
			pipe_line[0] == '>' && pipe_line[1] != '>')
			ft_file_out(&pipe_line, &command->out_file_type, \
			1, &command->out_file);
		if (pipe_line[0] && pipe_line[1] && \
			pipe_line[0] == '>' && pipe_line[1] == '>')
		{
			pipe_line++;
			ft_file_out(&pipe_line, &command->out_file_type, \
			2, &command->out_file);
		}
		if (pipe_line[0] && pipe_line[1] && \
			pipe_line[0] == '<' && pipe_line[1] != '<')
			ft_file_out(&pipe_line, &command->input_file_type, \
			1, &command->input_file);
		if (pipe_line[0] && pipe_line[1] && \
			pipe_line[0] == '<' && pipe_line[1] == '<')
		{
			pipe_line++;
			ft_file_out(&pipe_line, &command->input_file_type, \
			1, &command->input_file);
		}
	}
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

char	*ft_pars_simple(char *pipe_line, t_command *command)
{
	int	i;
	int	j;
	int	k;
	int	n;

	n = 0;
	i = 0;
	while (i < command->number_of_simple_commands)
	{
		n = ft_chek_leng_com(pipe_line);
		command->simple_commands[i]->arguments = (char **)
			malloc(sizeof(char *) * (n + 1));
		command->simple_commands[i]->arguments[n] = NULL;
		k = 0;
		while (1)
		{
			j = 0;
			while (*pipe_line && *pipe_line == ' ')
				pipe_line++;
			if (*pipe_line && *pipe_line == '|')
			{
				pipe_line++;
				break ;
			}
			if (!pipe_line[0])
				break ;
			if (*pipe_line && (*pipe_line == '<' || *pipe_line == '>'))
				break ;
			while (pipe_line[j] && pipe_line[j] != ' ' && pipe_line[j] \
				!= '|' && pipe_line[j] != '>' && pipe_line[j] != '<')
				j++;
			command->simple_commands[i]->arguments[k] = \
				(char *)malloc(sizeof(char) * (j + 1));
			command->simple_commands[i]->arguments[k][j] = '\0';
			j = 0;
			while (*pipe_line && *pipe_line != ' ' \
				&& *pipe_line != '|' && *pipe_line != '>' && *pipe_line != '<')
			{
				command->simple_commands[i]->arguments[k][j] = *pipe_line;
				pipe_line++;
				j++;
			}
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

	k = 0;
	i = 0;
	while (pipe_line[i])
	{
		if (pipe_line[i] == '|')
			k++;
		i++;
	}
	command->number_of_simple_commands = k + 1;
}

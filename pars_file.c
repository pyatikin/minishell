#include "minishell.h"

int	ft_file_fill(char **pipe_line, int l, char **file)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_quotes(*pipe_line) == 0)
	{
		while (i < l)
		{
			(*file)[i] = (*pipe_line)[i];
			i++;
		}
	}
	else
	{
		j = 2;
		(*pipe_line)++;
		while (i < l && ++j)
		{
			(*file)[i] = **pipe_line;
			(*pipe_line)++;
			i++;
		}
		(*pipe_line)++;
	}
	return (j);
}

int	ft_file_out(char **pipe_line, int *ch, int n, char **file)
{
	int	l;
	int	count;

	count = 1;
	l = 0;
	*ch = n;
	(*pipe_line)++;
	while (**pipe_line && **pipe_line == ' ' && ++count)
		(*pipe_line)++;
	l = ft_strlen_space(*pipe_line);
	*file = (char *)malloc(l + 1);
	(*file)[l] = '\0';
	count = count + ft_file_fill(pipe_line, l, file);
	while (**pipe_line && (**pipe_line != ' ' && **pipe_line \
		!= '>' && **pipe_line != '<' && **pipe_line != '|') && ++count)
			(*pipe_line)++;
	return (count);
}

void	ft_file_find2(char **pipe_line, t_command *command, int k)
{
	if ((*pipe_line)[0] && (*pipe_line)[1] && \
		(*pipe_line)[0] == '<' && (*pipe_line)[1] != '<')
		command->tmp = command->tmp + ft_file_out(pipe_line, \
			&command->simple_commands[k]->in_file_type, \
			1, &command->simple_commands[k]->in_file);
	if ((*pipe_line)[0] && (*pipe_line)[1] && (*pipe_line)[0] == \
		'<' && (*pipe_line)[1] == '<' && ++command->tmp)
	{
		(*pipe_line)++;
		command->tmp = command->tmp + ft_file_out(pipe_line, \
			&command->simple_commands[k]->in_file_type, \
			2, &command->simple_commands[k]->in_file);
	}
}

void	ft_file_find(char **pipe_line, t_command *command, int k)
{
	while (**pipe_line)
	{
		while (**pipe_line == ' ' && ++command->tmp)
			(*pipe_line)++;
		if (**pipe_line && ((**pipe_line) == '|'))
			return ;
		if ((*pipe_line)[0] && (*pipe_line)[1] && \
			(*pipe_line)[0] == '>' && (*pipe_line)[1] != '>')
			command->tmp = command->tmp + ft_file_out(pipe_line, \
				&command->simple_commands[k]->out_file_type, 1, \
				&command->simple_commands[k]->out_file);
		if ((*pipe_line)[0] && (*pipe_line)[1] && \
			(*pipe_line)[0] == '>' && (*pipe_line)[1] == '>' && ++command->tmp)
		{
			(*pipe_line)++;
			command->tmp = command->tmp + ft_file_out(pipe_line, \
				&command->simple_commands[k]->out_file_type, \
				2, &command->simple_commands[k]->out_file);
		}
		ft_file_find2(pipe_line, command, k);
	}
}

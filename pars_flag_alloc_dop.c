#include "minishell.h"

void	ft_cp_dop(t_command *command, char *f, char **pipe_line)
{
	command->tmp = command->tmp + 2;
	(*f) = **pipe_line;
	(*pipe_line)++;
}

void	ft_ps_dop(char **pipe_line, t_command *command, int i)
{
	while (**pipe_line && **pipe_line == ' ' && ++command->tmp)
		(*pipe_line)++;
	if (**pipe_line && (**pipe_line == '<' || **pipe_line == '>'))
		ft_file_find(pipe_line, command, i);
}

#include "minishell.h"

t_command	*zero_struk_command(char *pipe_line, t_env_var *vars)
{
	t_command	*command;
	int			i;

	i = 0;
	command = (t_command *)malloc(sizeof(t_command));
	while (pipe_line[i])
		i++;
	command->cmd = (char *)malloc(i + 1);
	i = 0;
	while (pipe_line[i])
	{
		command->cmd[i] = pipe_line[i];
		i++;
	}
	command->cmd[i] = '\0';
	command->number_of_available_simple_commands = 0;
	command->number_of_simple_commands = 0;
	command->background = 0;
	command->tmp = 0;
	command->result = vars->status;
	return (command);
}

t_simpleCommand	*zero_struk_simple(void)
{
	t_simpleCommand	*simple;

	simple = (t_simpleCommand *)malloc(sizeof(t_simpleCommand));
	simple->out_file_type = 0;
	simple->number_of_available_arguments = 0;
	simple->in_file_type = 0;
	simple->number_of_arguments = 0;
	simple->out_file = NULL;
	simple->in_file = NULL;
	simple->arguments = NULL;
	return (simple);
}

void	ft_zero_var(int *i, int *k, int *m, char **res)
{
	*i = 0;
	*k = 0;
	*m = 0;
	*res = NULL;
}

int	ft_small_stuped_bull_sheet(int i, char *pipe_line)
{
	while (pipe_line[i] && pipe_line[i] == ' ')
		i++;
	return (i);
}

void	fkng_bll_shit(char **pipe_line, int *j)
{
	(*pipe_line)++;
	(*j)++;
}

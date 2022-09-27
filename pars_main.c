#include "minishell.h"

t_command	*parsbody(char *pipe_line, t_env_var *vars)
{
	int			i;
	t_command	*command;
	char		*pl;

	i = 0;
	command = zero_struk_command(pipe_line, vars);
	ft_find_pipe(pipe_line, command);
	command->simple_commands = (t_simpleCommand **)malloc(sizeof
			(t_simpleCommand *) *(command->number_of_simple_commands + 1));
	command->env = vars->env;
	while (i < command->number_of_simple_commands)
	{
		command->simple_commands[i] = zero_struk_simple();
		i++;
	}
	command->simple_commands[command->number_of_simple_commands] = NULL;
	pl = ft_strdup(pipe_line);
	ft_pars_simple(&pl, command);
	return (command);
}

void	ft_pars_dop1(char **pipe_line, t_command *command, int i, int *k)
{
	if (ft_quotes_for_pipe(*pipe_line) == -1)
		*pipe_line = ft_dollar(pipe_line, command);
	ft_without_un_quotes(*pipe_line, '\"');
	ft_without_un_quotes(*pipe_line, '\'');
	command->simple_commands[i]->arguments = (char **) \
		malloc(sizeof(char *) * (ft_chek_leng_com(*pipe_line) + 1));
	command->simple_commands[i]->arguments[ft_chek_leng_com(*pipe_line)] = NULL;
	*k = 0;
}

void	ft_pars_dop2(char **pipe_line, t_command *command, int i, int *k)
{
	command->simple_commands[i]->arguments[*k] = \
		(char *)malloc(sizeof(char) * (ft_alloc_for_pattern \
			(ft_quotes(*pipe_line), *pipe_line, command) + 1));
	command->simple_commands[i]->arguments[*k][ft_alloc_for_pattern \
		(ft_quotes(*pipe_line), *pipe_line, command)] = '\0';
	ft_copy_pipe(pipe_line, command, i, *k);
	(*k)++;
	command->simple_commands[i]->number_of_arguments = *k;
}

void	ft_pars_simple(char **pipe_line, t_command *command)
{
	int	i;
	int	k;

	i = 0;
	while (i < command->number_of_simple_commands)
	{
		ft_pars_dop1(pipe_line, command, i, &k);
		while (1)
		{
			ft_ps_dop(pipe_line, command, i);
			if (**pipe_line && **pipe_line == '|' && ++command->tmp)
			{
				(*pipe_line)++;
				break ;
			}
			if (!(*pipe_line)[0])
				break ;
			ft_pars_dop2(pipe_line, command, i, &k);
		}
		i++;
	}
	i = 0;
	ft_cl_pl(&i, command, pipe_line);
}

void	ft_find_pipe(char *pipe_line, t_command *command)
{
	int	i;
	int	k;
	int	flag;

	k = 0;
	flag = 0;
	i = 0;
	while (pipe_line[i])
	{
		flag = ft_flags(pipe_line, flag, i);
		if (pipe_line[i] == '|' && (flag == -1 || flag == -2 || flag == 0))
			k++;
		i++;
	}
	command->number_of_simple_commands = k + 1;
}

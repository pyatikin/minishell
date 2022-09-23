#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "error_msgs.h"
#include "minishell.h"

int	check_g_interrupt(void)
{
	if (g_interrupt)
		rl_done = true;
	return (0);
}

void	pipe_for_read_input(char *redirect, t_simpleCommand *cur_command)
{
	int	fd[2];

	pipe(fd);
	ft_putstr_fd(redirect, fd[1]);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	do_update_target(char **redirect, char *readline_res)
{
	char	*res;
	char	*tmp;

	tmp = *redirect;
	res = ft_strjoinchr(readline_res, endl);
	*redirect = ft_strjoin(*redirect, res);
	free(tmp);
	free(res);
}

void	do_read_input(char *target, t_simpleCommand *cur_command)
{
	char	*readline_res;
	char	*redirect;

	readline_res = NULL;
	redirect = NULL;
	rl_event_hook = check_g_interrupt;
	while (target && g_interrupt == false)
	{
		readline_res = readline(">");
		if (!readline_res && g_interrupt == false)
			print_err(MSG_ERR_HEREDOC, target, 0);
		if (ft_strcmp(readline_res, target) == 0)
			break ;
		if (readline_res)
			do_update_target(&redirect, readline_res);
		free(readline_res);
		readline_res = NULL;
	}
	rl_event_hook = NULL;
	pipe_for_read_input(redirect, cur_command);
	free(target);
	free(readline_res);
	free(redirect);
}

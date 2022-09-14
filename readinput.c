#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "error_msgs.h"
#include "minishell.h"

//static inline void	parse_read_input_target(t_redirect *redirect, char **env)
//{
//	char	*tmp;
//
//	if (redirect->target)
//	{
//		tmp = redirect->target;
//		redirect->target = parse_cmd(redirect->target, env, false);
//		free(tmp);
//	}
//}
void pipe_for_read_input(char *redirect, t_simpleCommand *cur_command)
{
	int fd[2];
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
	while (1)
	{
		readline_res = readline(">");
		if (!readline_res)
			print_err(MSG_ERR_HEREDOC, target, 0);
		//printf("1read = %s\ttarget = %s\t cmp = %d\n", readline_res, target, ft_strcmp(readline_res, target));
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
	
	//parse_read_input_target(redirect);
}

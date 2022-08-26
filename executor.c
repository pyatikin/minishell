#include "minishell.h"

static inline int	do_action_exec(t_command *action, char ***env)
{
	action->pid = fork();
	if (action->pid == success)
	{
		if (is_valid_action_path(action, *env) == false)
			exit(127);
		do_update_shlvl(env);
		do_redirects(*action);
		if (action->pipe_in)
			close(action->pipe_in);
		if (action->pipe_out)
			close(action->pipe_out);
		if (action->exec.path)
			execve(action->exec.path, action->exec.argv, *env);
		execve(action->exec.argv[0], action->exec.argv, *env);
	}
	else if (action->pid < 0)
	{
		perror(MSG_PROG_NAME);
		action->pid = 0;
		return (unsuccess);
	}
	do_finish_exec(action);
	return (success);
}
#include "minishell.h"
#include <signal.h>
#include <termios.h>

void	echo_ctl(char on, int fd)
{
	struct termios	tstate;

	tcgetattr(fd, &tstate);
	if (on)
		tstate.c_lflag |= ECHOCTL;
	else
		tstate.c_lflag &= ~ECHOCTL;
	tcsetattr(fd, TCSANOW, &tstate);
}

void	usual_handler(int s)
{
	if (s == SIGQUIT && MAC_OS)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else if (s == SIGINT)
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handler_heredoc(int s)
{
	if (s == SIGQUIT && MAC_OS)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else if (s == SIGINT)
	{
		g_interrupt = 1;
		if (MAC_OS)
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	other_handler(int s)
{
	if (s == SIGQUIT)
		printf("Quit: %d\n", s);
	else if (s == SIGINT)
		printf("\n");
}

void	set_signals(int handler, int ctl, t_env_var *vars)
{
	sig_t		h_fun;

	if (handler == 1)
		h_fun = &usual_handler;
	else if (handler == 2)
		h_fun = &no_handler;
	else if (handler == 3)
		h_fun = &handler_heredoc;
	else
		h_fun = &other_handler;
	echo_ctl(ctl, vars->stdin_fd);
	signal(SIGINT, h_fun);
	signal(SIGQUIT, h_fun);
}

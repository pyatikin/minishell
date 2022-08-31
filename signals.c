#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <readline/readline.h>

void	echo_ctl(char on)
{
	struct termios	tstate;

	tcgetattr(0, &tstate);
	if (on)
		tstate.c_lflag |= ECHOCTL;
	else
		tstate.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &tstate);
}

void	c_handler(void)
{
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	n_handler(void)
{
	//rl_on_new_line();
	//rl_redisplay();
}

void	set_signals(void)
{
	struct sigaction	sig_int_handler_c;
	struct sigaction	sig_int_handler_n;

	echo_ctl(0);
	sig_int_handler_c.sa_handler = c_handler;
	sigemptyset(&sig_int_handler_c.sa_mask);
	sig_int_handler_c.sa_flags = 0;
	sigaction(SIGINT, &sig_int_handler_c, NULL);
	sig_int_handler_n.sa_handler = n_handler;
	sigemptyset(&sig_int_handler_n.sa_mask);
	sig_int_handler_n.sa_flags = 0;
	sigaction(SIGQUIT, &sig_int_handler_n, NULL);
}
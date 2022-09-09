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

void	usual_handler(int s)
{
	//rl_on_new_line();
	//printf("\n");
	//rl_replace_line("", 1);
	////rl_on_new_line();
	//rl_redisplay();
	if (s == SIGQUIT)
	{
		//rl_on_new_line();
		//rl_redisplay();
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
	if (s == SIGQUIT)
	{
		//rl_on_new_line();
		//rl_redisplay();
		printf("Quit\n");
		//rl_replace_line("", 1);
		//rl_on_new_line();
		//rl_redisplay();
	}
	else if (s == SIGINT)
	{
		//if (MAC_OS)
		//{
			//rl_on_new_line();
			//rl_redisplay();
		//}
		printf("\n");
		rl_replace_line("", 1);
		//rl_on_new_line();
		rl_redisplay();
	}
}

void	no_handler(int s) //TODO проверить в чек листе
{
	//rl_on_new_line();
	//rl_redisplay();
}

void	set_signals(int handler, int ctl)
{
	//struct sigaction	sig_int_handler_c;
	//struct sigaction	sig_int_handler_n;
//
	//echo_ctl(0);
	//sig_int_handler_c.sa_handler = c_handler;
	//sigemptyset(&sig_int_handler_c.sa_mask);
	//sig_int_handler_c.sa_flags = 0;
	//sigaction(SIGINT, &sig_int_handler_c, NULL);
	//sig_int_handler_n.sa_handler = n_handler;
	//sigemptyset(&sig_int_handler_n.sa_mask);
	//sig_int_handler_n.sa_flags = 0;
	//sigaction(SIGQUIT, &sig_int_handler_n, NULL);
	sig_t		h_fun;

	if (handler == 1)
		h_fun = &usual_handler;
	else if (handler == 2)
		h_fun = &no_handler;
	else if (handler == 3)
		h_fun = &handler_heredoc;
	else
		h_fun = &no_handler;
	echo_ctl(ctl);
	signal(SIGINT, h_fun);
	signal(SIGQUIT, h_fun);
}
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
void c_handler(int s){
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}
void n_handler(int s){
	//rl_on_new_line();
	//rl_redisplay();
}
void set_signals()
{
	struct sigaction sigIntHandler_C;
	struct sigaction sigIntHandler_N;

	echo_ctl(0);
	sigIntHandler_C.sa_handler = c_handler;
	sigemptyset(&sigIntHandler_C.sa_mask);
	sigIntHandler_C.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler_C, NULL);

	sigIntHandler_N.sa_handler = n_handler;
	sigemptyset(&sigIntHandler_N.sa_mask);
	sigIntHandler_N.sa_flags = 0;
	sigaction(SIGQUIT, &sigIntHandler_N, NULL);
}
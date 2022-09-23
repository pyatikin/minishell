#include "minishell.h"
#include <signal.h>
#include <termios.h>

void	no_handler(int s)
{
	if (s == SIGQUIT || s == SIGINT)
	{
	}
}

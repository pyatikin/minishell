#include "minishell.h"

int	args_size(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_echo(char **args)
{
	int	i;
	int	option_count;

	i = 1;
	option_count = 0;
	if (args_size(args) > 1)
	{
		while (args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			option_count = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (option_count == 0)
		write(1, "\n", 1);
	return (0);
}

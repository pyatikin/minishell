#include "minishell.h"

char	*get_env_value(char *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	tmp = strdup(&env[i + 1]);
	return (tmp);
}

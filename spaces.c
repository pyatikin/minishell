#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

void	quote_check(char *cmd, int *start, char **quote_type)
{
	if (cmd[*start] == quote || cmd[*start] == single_quote)
	{
		if (*quote_type == NULL)
			*quote_type = &cmd[*start];
		else if (cmd[*start] == **quote_type)
			*quote_type = NULL;
	}
	(*start)++;
}

int	count_true_spaces(char *cmd, int start)
{
	int		i;
	int		flag;
	char	*quote_type;

	i = 0;
	flag = 1;
	quote_type = NULL;
	while (cmd[start])
	{
		if (quote_type == NULL && cmd[start] == ' ')
		{
			if (flag)
			{
				i++;
				flag = 0;
			}
		}
		else
		{
			i++;
			flag = 1;
		}
		quote_check(cmd, &start, &quote_type);
	}
	return (i);
}

void	make_new_cmd(char *cmd, char **new_cmd, int start)
{
	int		i;
	int		flag;
	char	*quote_type;

	i = 0;
	flag = 1;
	quote_type = NULL;
	while (cmd[start])
	{
		if (quote_type == NULL && cmd[start] == ' ')
		{
			if (flag)
			{
				(*new_cmd)[i++] = cmd[start];
				flag = 0;
			}
		}
		else
		{
			(*new_cmd)[i++] = cmd[start];
			flag = 1;
		}
		quote_check(cmd, &start, &quote_type);
	}
}

void	first_or_last(char **new_cmd)
{
	int	i;

	if (!is_space(*new_cmd, 0) && !is_space(*new_cmd, ft_strlen(*new_cmd) - 1))
		return ;
	if (is_space(*new_cmd, ft_strlen(*new_cmd) - 1))
		(*new_cmd)[ft_strlen(*new_cmd) - 1] = '\0';
	if (is_space(*new_cmd, 0))
	{
		i = 0;
		while ((*new_cmd)[i] && (*new_cmd)[i + 1])
		{
			(*new_cmd)[i] = (*new_cmd)[i + 1];
			i++;
		}
		(*new_cmd)[i] = '\0';
	}		
}

char	*ft_chng_line(char **cmd)
{
	int		len;
	char	*new_cmd;

	if (!cmd || !*cmd || !**cmd)
		return (NULL);
	len = count_true_spaces(*cmd, 0);
	new_cmd = malloc(sizeof(char) * (len + 1));
	new_cmd[len] = '\0';
	make_new_cmd(*cmd, &new_cmd, 0);
	first_or_last(&new_cmd);
	free(*cmd);
	return (new_cmd);
}

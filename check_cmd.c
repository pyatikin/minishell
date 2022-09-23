#include "minishell.h"
#include "enums.h"

int	escaped(char *cmd, int i)
{
	int	j;

	if (i-- == 0)
		return (false);
	j = 0;
	while (i >= 0)
	{
		if (cmd[i] != escape)
			break ;
		j++;
		i--;
	}
	if (j % 2 != 0)
		return (true);
	return (false);
}

char	escaped_eof(char *cmd)
{
	if (*cmd && cmd[ft_strlen(cmd) - 1] == escape)
		return (escape);
	return (0);
}

char	has_opened_quotes(char *cmd, int start, int end)
{
	char	*quote_type;

	quote_type = NULL;
	while (start <= end && cmd[start] != ends)
	{
		if (cmd[start] == quote || cmd[start] == single_quote)
		{
			if (quote_type == NULL)
				quote_type = &cmd[start];
			else if (cmd[start] == *quote_type)
				quote_type = NULL;
		}
		start++;
	}
	if (quote_type)
		return (*quote_type);
	return (false);
}

char	more_two_sequenses_controls(
	char *cmd, char opened_qoute, int i, int j)
{
	while (cmd[i] != ends)
	{
		if (cmd[i] == quote || cmd[i] == single_quote)
		{
			if (opened_qoute == false)
				opened_qoute = cmd[i];
			else if (opened_qoute && opened_qoute == single_quote
				&& cmd[i] == opened_qoute)
				opened_qoute = 0;
			else if (opened_qoute
				&& opened_qoute == quote)
				opened_qoute = 0;
		}
		else if ((cmd[i] == ampersand || cmd[i] == pipes)
			&& opened_qoute == false)
		{
			j = i;
			while (cmd[i + 1] == cmd[j])
				i++;
			if (i - j > 1)
				return (cmd[i]);
		}
		i++;
	}
	return (false);
}

int	has_opened_parenth(
	char *cmd, char parenth, char opened_quote, int i)
{
	while (cmd[i] != ends)
	{
		if (cmd[i] == quote || cmd[i] == single_quote)
		{
			if (cmd[i] == single_quote && opened_quote == single_quote)
				opened_quote = 0;
			else if (cmd[i] == quote && opened_quote == quote)
				opened_quote = 0;
			else if (opened_quote == 0)
				opened_quote = cmd[i];
		}
		if (opened_quote == false
			&& cmd[i] == open_parenth)
			parenth++;
		else if (opened_quote == false
			&& cmd[i] == close_parenth)
		{
			parenth--;
			if (parenth < 0)
				return (1);
		}
		i++;
	}
	return (parenth != 0);
}

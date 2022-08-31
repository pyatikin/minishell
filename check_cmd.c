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

static inline char	escaped_eof(char *cmd)
{
	if (*cmd && cmd[ft_strlen(cmd) - 1] == escape
		/*&& escaped(cmd, ft_strlen(cmd) - 1) == false*/)
		return (escape);
	return (0);
}

static inline char	has_opened_quotes(char *cmd, int start, int end)
{
	char	*quote_type;

	quote_type = NULL;
	while (start <= end && cmd[start] != ends)
	{
		if (cmd[start] == quote || cmd[start] == single_quote)
		{
			if (quote_type == NULL)
			{
				//if (escaped(cmd, start) == false)
					quote_type = &cmd[start];
			}
			else if (cmd[start] == *quote_type)
			{
				//if (*quote_type == single_quote)
				//	quote_type = NULL;
				//else if (escaped(cmd, start) == false)
					quote_type = NULL;
			}
		}
		start++;
	}
	if (quote_type)
		return (*quote_type);
	return (false);
}

static inline char	more_two_sequenses_controls(
	char *cmd, char opened_qoute, int i, int j)
{
	while (cmd[i] != ends)
	{
		if (cmd[i] == quote || cmd[i] == single_quote)
		{
			if (opened_qoute == false /*&& escaped(cmd, i) == false*/)
				opened_qoute = cmd[i];
			else if (opened_qoute && opened_qoute == single_quote
				&& cmd[i] == opened_qoute)
				opened_qoute = 0;
			else if (opened_qoute
				&& opened_qoute == quote /*&& escaped(cmd, i) == false*/)
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

static inline int	has_opened_parenth(
	char *cmd, char parenth, char opened_quote, int i)
{
	while (cmd[i] != ends)
	{
		if (cmd[i] == quote || cmd[i] == single_quote)
		{
			if (cmd[i] == single_quote && opened_quote == single_quote)
				opened_quote = 0;
			else if (cmd[i] == quote && opened_quote == quote
				/*&& escaped(cmd, i) == false*/)
				opened_quote = 0;
			else if (opened_quote == 0 /*&& escaped(cmd, i) == false*/)
				opened_quote = cmd[i];
		}
		if (opened_quote == false
			&& cmd[i] == open_parenth /*&& escaped(cmd, i) == false*/)
			parenth++;
		else if (opened_quote == false
			&& cmd[i] == close_parenth /*&& escaped(cmd, i) == false*/)
		{
			parenth--;
			if (parenth < 0)
				return (1);
		}
		i++;
	}
	return (parenth != 0);
}

static inline int	empty_heredoc_or_redirect(char *cmd)
{
	if (cmd == NULL || *cmd == ends)
		return (unsuccess);
	if (((*cmd == l_crnr || *cmd == r_crnr) && ft_strlen(cmd) == 1)
		|| (ft_strcmp(cmd, "<<") == success || ft_strcmp(cmd, ">>") == success)
		|| (cmd[ft_strlen(cmd) - 1] == l_crnr
			|| cmd[ft_strlen(cmd) - 1] == r_crnr))
	{
		print_err(MSG_ERR_SYNATX, NULL, false);
		return (unsuccess);
	}
	return (success);
}

static inline int	check_cmd_sequenses(char *cmd)
{
	if (escaped_eof(cmd) == escape)
	{
		print_err(MSG_ERR_CMD_EEOF, NULL, false);
		return (false);
	}
	if (has_opened_quotes(cmd, 0, ft_strlen(cmd)))
	{
		print_err(MSG_ERR_CMD_UQ, NULL,
			has_opened_quotes(cmd, 0, ft_strlen(cmd)));
		return (false);
	}
	if (more_two_sequenses_controls(cmd, 0, 0, 0))
	{
		print_err(MSG_ERR_MORE2CNTRLS, NULL,
			more_two_sequenses_controls(cmd, 0, 0, 0));
		return (false);
	}
	if (has_opened_parenth(cmd, 0, 0, 0))
	{
		print_err(MSG_ERR_CMD_HAS_UP, NULL, false);
		return (false);
	}
	if (empty_heredoc_or_redirect(cmd))
		return (false);
	return (true);
}

int	pipes_and_redirects(char *cmd)
{
	int	i;
	char redirect_type;
	int count;

	i = 0;
	if (cmd == NULL)
		return (unsuccess);
	//i = ft_strlen(*cmd);
	//while (--i >= 0 && (*cmd)[i] != ends && (*cmd)[i] == space
	//	&& escaped(*cmd, i) == false)
	//	(*cmd)[i] = ends;
	//i = 0;
	//while (**cmd != ends && **cmd == space && escaped(*cmd, i) == false)
	//{
	//	i++;
	//	*cmd += 1;
	//}

	count = 0;
	redirect_type = '\0';
	while (cmd[i])
	{	
		if (cmd[i] == '>' || cmd[i] == '<')
		{
			if (redirect_type == '\0')
				redirect_type = cmd[i];
			else if (cmd[i] == redirect_type)
				count++;
			else
			{
				print_err(MSG_ERR_INVRDTYPE, NULL, false);
				return (unsuccess);
			}
		}
		if (cmd[i] == redirect_type && count == 2)
		{
			print_err(MSG_ERR_MORE2CNTRLS, NULL, redirect_type);
			return (unsuccess);
		}
		if (cmd[i] == ' ')
		{
			redirect_type = '\0';
			count = 0;
		}
		i++;
	}
	if (*cmd == pipes)
	{
		print_err(MSG_ERR_SYNATX, NULL, false);
		return (unsuccess);
	}
	if (*cmd && cmd[ft_strlen(cmd) - 1] == pipes)
		print_err(MSG_ERR_SYNATX, NULL, false);
	if (cmd)
		return (success);
	return (unsuccess);
}

int	check_cmd(char *cmd)
{
	int			res;

	if (pipes_and_redirects(cmd) == unsuccess)
		return (-1);
	res = check_cmd_sequenses(cmd);
	if (!res)
		return (2);
	return (0);
}

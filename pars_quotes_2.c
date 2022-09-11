#include "minishell.h"

char	*ft_quotes_chng_strt(char *pipe_line, int i)
{
	int		space;
	char	chng;

	space = i;
	while (pipe_line[space] && pipe_line[space] != ' ')
		space--;
	space++;
	while (i - space > 0)
	{
		chng = pipe_line[space];
		pipe_line[space] = pipe_line[space + 1];
		pipe_line[space + 1] = chng;
		(space)++;
	}
	return (pipe_line);
}

char	*ft_quotes_chng_end(char *pipe_line, int *i)
{
	int		space;
	char	chng;

	space = *i;
	while (pipe_line[space] && pipe_line[space] != ' ')
		space++;
	while (space - *i > 1)
	{
		chng = pipe_line[*i];
		pipe_line[*i] = pipe_line[*i + 1];
		pipe_line[*i + 1] = chng;
		(*i)++;
	}
	*i = space;
	return (pipe_line);
}

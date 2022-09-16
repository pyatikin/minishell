#include "minishell.h"

char	*ft_quotes_chng_strt(char *pipe_line, int i)
{
	int		space;
	char	chng;

	space = i;
	chng = '\0';
	while (space >= 0 && pipe_line[space] && \
		pipe_line[space] != ' ' && pipe_line[space] \
		!= '|' && pipe_line[space] != '<' && pipe_line[space] != '>')
		space--;
	space++;
	while (i > 0 && i - space > 0)
	{
		chng = pipe_line[i];
		pipe_line[i] = pipe_line[i - 1];
		pipe_line[i - 1] = chng;
		i--;
	}
	return (pipe_line);
}

char	*ft_quotes_chng_end(char *pipe_line, int *i)
{
	int		space;
	char	chng;

	space = *i;
	while (pipe_line[space] && pipe_line[space] != ' ' && pipe_line[space] \
		!= '|' && pipe_line[space] != '<' && pipe_line[space] != '>')
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

void	ft_wuq_dop(char **pipe_line, int *i, int *flag, char g)
{
	if ((*pipe_line)[*i] && (*pipe_line)[*i] == g && (*flag) == 0)
	{
		(*flag) = 1;
		if ((*i > 0) && (*pipe_line)[(*i) - 1] && \
			((*pipe_line)[(*i) - 1] != ' ' \
			&& (*pipe_line)[(*i) - 1] != '|' && (*pipe_line)[(*i) - 1] != '<' \
			&& (*pipe_line)[(*i) - 1] != '>' && (*pipe_line)[(*i) - 1] != g))
			(*pipe_line) = ft_quotes_chng_strt(*pipe_line, (*i));
	}
	else if ((*pipe_line)[(*i)] && (*pipe_line)[(*i)] == g && *flag == 1)
	{
		*flag = 0;
		if ((*pipe_line)[(*i) + 1] && ((*pipe_line)[(*i) + 1] != ' ' \
			&& (*pipe_line)[(*i) + 1] != '|' && (*pipe_line)[(*i) + 1] != '<' \
			&& (*pipe_line)[(*i) + 1] != '>' && (*pipe_line)[(*i) + 1] != g))
			*pipe_line = ft_quotes_chng_end(*pipe_line, i);
	}
}

#include "minishell.h"

int	pipes_and_redirects(char *cmd)
{
	int		i;
	char	redirect_type;
	int		count;
	int		f;

	ft_z_p_a_r(&i, &f, &count, &redirect_type);
	if (cmd == NULL)
		return (unsuccess);
	while (cmd[i])
	{	
		f = par_dop_if(cmd, &i, &redirect_type, &count);
		if (f == unsuccess || f == success)
			return (f);
	}
	if (*cmd == pipes)
		return (print_err(MSG_ERR_SYNATX, NULL, false));
	if (*cmd && cmd[ft_strlen(cmd) - 1] == pipes)
		return (print_err(MSG_ERR_SYNATX, NULL, false));
	if (cmd)
		return (success);
	return (unsuccess);
}

int	check_cmd(char **cmd)
{
	int			res;

	if (pipes_and_redirects(*cmd) == unsuccess)
	{
		free(*cmd);
		return (-1);
	}
	res = check_cmd_sequenses(*cmd);
	if (!res)
	{
		free(*cmd);
		return (2);
	}
	return (0);
}

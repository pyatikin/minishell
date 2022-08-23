#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "enums.h"
# include "error_msgs.h"

typedef struct s_file
{
	char	*in_file;
	int		in_file_type;
}	t_file;


typedef struct s_simpleCommand
{
	int			number_of_available_arguments;
	int			number_of_arguments;
	char		**arguments;
	t_file	*out_file;
	t_file	*in_file;
}	t_simpleCommand;

typedef struct s_command
{
	char					*cmd;
	int						number_of_available_simple_commands;
	int						number_of_simple_commands;
	t_simpleCommand			**simple_commands;
	
	
	int						background;
}	t_command;

size_t	ft_strlen(const char *str);
int	check_cmd(char **cmd);
void	print_err(char *main, char	*word, char ch);
char	*ft_chng_line(char **cmd);
t_command	*parsbody(char *pipe_line);
#endif
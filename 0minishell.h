#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "enums.h"
# include "error_msgs.h"

# define BEGIN(x,y) "\001\033["#x";"#y"m\002"    // x: background, y: foreground
# define CLOSE "\001\033[0m\002"                 // Закрыть все свойства

typedef struct s_simpleCommand
{
	int		number_of_available_arguments;
	int		number_of_arguments;
	char	**arguments;
}	t_simpleCommand;

typedef struct s_command
{
	char					*cmd;
	int						number_of_available_simple_commands;
	int						number_of_simple_commands;
	t_simpleCommand			**simple_commands;
	char					*out_file;
	char					*input_file;
	int						out_file_type;
	int						input_file_type;
	int						background;
}	t_command;

int	check_cmd(char **cmd);
void	print_err(char *main, char	*word, char ch);
char	*ft_chng_line(char **cmd);
t_command	*parsbody(char *pipe_line);
static inline int	escaped(char *cmd, int i);

#endif
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "enums.h"
# include "error_msgs.h"
# include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#define CLOSE "\001\033[0m\002"                 // Закрыть все свойства
#define BLOD  "\001\033[1m\002"                 // Подчеркнуть, жирным шрифтом, выделить
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"    // x: background, y: foreground
#define MYSHELL "Myshell > "
 

typedef struct s_simpleCommand
{
	int		number_of_available_arguments;
	int		number_of_arguments;
	char	**arguments;
	char	*out_file;
	int		out_file_type;
	char	*in_file;
	int		in_file_type;
}	t_simpleCommand;

typedef struct s_command
{
	char					*cmd;
	int						number_of_available_simple_commands;
	int						number_of_simple_commands;
	t_simpleCommand			**simple_commands;
	int						background;
}	t_command;

typedef struct s_env_var
{
	char	**env;
	char	**path;
}	t_env_var;

void set_signals();
int	escaped(char *cmd, int i);
int	check_cmd(char *cmd);
void	print_err(char *main, char	*word, char ch);
char	*ft_chng_line(char **cmd);
t_command	*parsbody(char *pipe_line);
size_t	ft_strlen(const char *str);

#endif
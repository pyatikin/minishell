#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <sys/stat.h>
# include "libft.h"
# include "enums.h"
# include "error_msgs.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

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
	int		out_fd;
	char	*in_file;
	int		in_file_type;
	int		in_fd;
	int		db_fd[2];
}	t_simpleCommand;

typedef struct s_command
{
	char					*cmd;
	int						number_of_available_simple_commands;
	int						number_of_simple_commands;
	t_simpleCommand			**simple_commands;
	int						background;
	char					**env;
	int						tmp;
}	t_command;

typedef struct s_env_var
{
	char	**env;
	char	**path;
	int		stdin_fd;
	int		stdout_fd;
	int		status;
}	t_env_var;

int				args_size(char **args);
int				ft_echo(char **args);
int				ft_dollar_leng(int i, char *pipe_line);
char			*ft_env_var(int i, char *pipe_line, int k, t_command *command);
char			*ft_find_env_var(char **var, char **env);
char			*ft_pipe_line_chng(char **pipe_line, char *res, \
					int *i_k, t_command *command);
char			*ft_dollar(char **pipe_line, t_command *command);
int				ft_file_fill(char **pipe_line, int l, char **file);
int				ft_file_out(char **pipe_line, int *ch, int n, char **file);
void			ft_file_find2(char **pipe_line, t_command *command, int k);
void			ft_file_find(char **pipe_line, t_command *command, int k);
int				ft_strlen_space(char *str);
int				ft_flags(char *pipe_line, int flag, int i);
int				ft_chek_leng_com(char *pipe_line);
int				ft_alloc_for_pattern(int n, char *pipe_line, \
					t_command *command);
void			ft_copy_pipe(char **pipe_line, \
					t_command *command, int i, int k);
t_command		*parsbody(char *pipe_line, char **env);
void			ft_pars_dop1(char **pipe_line, \
					t_command *command, int i, int *k);
void			ft_pars_dop2(char **pipe_line, \
					t_command *command, int i, int *k);
void			*ft_pars_simple(char **pipe_line, t_command *command);
void			ft_find_pipe(char *pipe_line, t_command *command);
int				ft_quotes_for_pipe(char *pipe_line);
int				ft_quotes(char *pipe_line);
int				deteck_flag(int k, int l, int *count);
void			ft_alloc_dup(int n, char **pipe_line, int *j, \
					t_command *command);
char			*ft_without_un_quotes(char *pipe_line, char q);
t_command		*zero_struk_command(char *pipe_line);
t_simpleCommand	*zero_struk_simple(void);
void			ft_zero_var(int *i, int *k, int *m, char **res);
int				ft_small_stuped_bull_sheet(int i, char *pipe_line);
void			fkng_bll_shit(char **pipe_line, int *j);
int				ft_pwd(void);
int				find_env(char **env, char *s);
char			*ft_quotes_chng_end(char *pipe_line, int *i);
char			*ft_quotes_chng_strt(char *pipe_line, int i);

char			*ft_strdup(const char *s1);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);

void			set_signals(int handler, int ctl);
int				escaped(char *cmd, int i);
int				check_cmd(char *cmd);
void			print_err(char *main, char	*word, char ch);
char			*ft_chng_line(char **cmd);
int				start_path(t_command *args, t_env_var *vars);
int				ft_env(t_env_var *vars, t_simpleCommand *cur_command);
int				ft_export(t_env_var *vars, t_simpleCommand *cur_command);
int				ft_clean(t_command *args, t_env_var *vars);
int				exec_loop(t_command *args, t_env_var *vars);
int				last_clean(t_command *args, t_env_var *vars);
int				ft_unset(t_command *args, t_env_var *vars, t_simpleCommand *cur_command);
int				add_new_env(t_env_var *vars, char* new);
int				ft_cd(char **args, t_env_var *env);
void			ft_putendl_fd(const char *s, int fd);
#endif
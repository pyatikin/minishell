#include "minishell.h"
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MYSHELL "Myshell > "

int	input_loop(t_command *args, t_env_var *vars, char *tmp)
{
	while (1)
	{
		tmp = readline(BEGIN(30, 36) MYSHELL CLOSE);
		if (!tmp)
		{
			printf("exit\n");
			return (0);
		}
		if (ft_strlen(tmp))
			add_history(tmp);
		set_signals(0, 1, vars);
		tmp = ft_chng_line(&tmp);
		if (check_cmd((tmp)) != 0)
			continue ;
		args = parsbody(tmp, vars);
		free(tmp);
		start_path(vars);
		exec_loop(args, vars);
		set_signals(1, 0, vars);
		ft_clean(args, vars);
		g_interrupt = 0;
		//printf("RES = %d", vars->status);
	}
}

void	dup_env(t_env_var *vars, char **env)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	while (env[++i])
		c++;
	vars->env = malloc(sizeof(char *) * (c + 1));
	vars->env[c] = NULL;
	i = -1;
	while (env[++i])
		vars->env[i] = ft_strdup(env[i]);
}

void	preprocess(t_env_var *vars, char **env)
{
	dup_env(vars, env);
	vars->status = 0;
	vars->stdin_fd = dup(STDIN_FILENO);
	vars->stdout_fd = dup(STDOUT_FILENO);
}

int	main(int argc, char **argv, char **env)
{
	t_command	args;
	t_env_var	vars;
	char		*tmp;

	tmp = NULL;
	g_interrupt = 0;
	preprocess(&vars, env);
	set_signals(1, 0, &vars);
	(void)argv;
	if (argc == 1)
	{
		input_loop(&args, &vars, tmp);
		rl_clear_history();
		last_clean(&args, &vars);
		//echo_ctl(1);
		return (0);
	}
	printf("ERROR ARGS");
	return (1);
}

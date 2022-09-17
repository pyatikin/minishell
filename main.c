#include "minishell.h"
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#define CLOSE "\001\033[0m\002"                 // Закрыть все свойства
#define BLOD  "\001\033[1m\002"                 // Подчеркнуть, жирным шрифтом, выделить
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"    // x: background, y: foreground
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
		set_signals(0, 1);
		tmp = ft_chng_line(&tmp);
		if (check_cmd((tmp)) != 0)
			continue;
		//write(1, args->cmd, sizeof(args->cmd));
		
		args = parsbody(tmp, vars->env);
		free(tmp);
		start_path(vars);
		//printf("|%s|\n", args->cmd);
		exec_loop(args, vars);
		set_signals(1, 0);
		ft_clean(args, vars);
		g_interrupt = 0;
	}
	
}

void dup_env(t_env_var *vars, char **env)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	while(env[++i])
		c++;
	vars->env = malloc(sizeof(char *) * (c + 1));
	vars->env[c] = NULL;
	i = -1;
	while(env[++i])
		vars->env[i] = ft_strdup(env[i]);
}

void preprocess(t_env_var *vars, char **env)
{
	
	dup_env(vars, env);
	vars->stdin_fd = dup(STDIN_FILENO);
	vars->stdout_fd = dup(STDOUT_FILENO);
	
	//printf("stdin = %d,\tstdout = %d", vars->stdin_fd, vars->stdout_fd);
}

int	main(int argc, char **argv, char **env)
{
	t_command	args;
	//int			res;
	t_env_var	vars;
	char		*tmp;

	tmp = NULL;
	g_interrupt = 0;
	preprocess(&vars, env);
	set_signals(1, 0);
	//printf("P = %p\n", vars.env);

	//start_path(&args, env, &vars);
	//sig_t		h_fun;
	//h_fun = &n_handler;
	//signal(SIGQUIT, h_fun);

	(void)argv;
	if (argc == 1)
	{
		input_loop(&args, &vars, tmp);
		rl_clear_history();
		last_clean(&args, &vars);
		//free(vars.env);
		//last_clean(&args, &vars);
		//close(args.fd);
		//free(args.res);
		//args.res = get_env_value("LES", args.env);
		//res = ft_atoi(args.res);
		//free_args(&args, true);
		echo_ctl(1);
		return (0);
	}
    printf("ERROR ARGS");
	//print_err(ERR_ARGC, NULL, 0);
	return (1);
}
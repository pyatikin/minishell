#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#define CLOSE "\001\033[0m\002"                 // Закрыть все свойства
#define BLOD  "\001\033[1m\002"                 // Подчеркнуть, жирным шрифтом, выделить
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"    // x: background, y: foreground


int	input_loop(t_command *args)
{
	while (1)
	{
		args->cmd = readline(BEGIN(30, 36)"Myshell >"CLOSE);
		if (!args->cmd)
		{
			printf("exit\n");
			return (0);
		}
		if (ft_strlen(args->cmd))
			add_history(args->cmd);
		args->cmd = ft_chng_line(&(args->cmd));
		if (check_cmd((args->cmd)) != 0)
			continue;
		//write(1, args->cmd, sizeof(args->cmd));
		
		args = parsbody(args->cmd);
		printf("|%s|\n", args->cmd);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_command	args;
	int			res;

	(void)argv;
	if (argc == 1)
	{
		input_loop(&args);
		//close(args.fd);
		//free(args.res);
		//args.res = get_env_value("LES", args.env);
		//res = ft_atoi(args.res);
		//free_args(&args, true);
		//echo_ctl(1);
		return (0);
	}
    printf("ERROR ARGS");
	//print_err(ERR_ARGC, NULL, 0);
	return (1);
}
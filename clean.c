#include "minishell.h"

//int	main(int argc, char **argv, char **env)
//{
//	t_command	*command;
//
//	command = parsbody("kjh \"kjh uou kjh\" >\"jkl\" | jhjhjjhjjh| <<lkji lk", env);
//	ft_clean(command);
//	printf("\n\n\n");
//	command = parsbody (\
//		"l\"$cdsa\"md $SHLVL <<\"kljh\" l\'$PWD\' >\"jkl\" e'c'ho| $SHELL <<jlk \"$?\""\
//		, env);
//	ft_clean(command);
//	printf("\n\n\n");
//	command = parsbody ("\"$!!\"", env);
//	ft_clean(command);
//	return (0);
//}



void	ft_show(t_command *command)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("команда: '%s'\n", command->cmd);
	while (command->simple_commands[i])
	{
		j = 0;
		while (command->simple_commands[i]->arguments[j])
		{
			printf("пайп: %d, позиция: %d, наименование: %s\n", \
				i + 1, j + 1, command->simple_commands[i]->arguments[j]);
			j++;
		}
		printf("in: %d, %s\nout: %d, %s\n", command->simple_commands[i]->\
			in_file_type, command->simple_commands[i]->in_file, command->\
			simple_commands[i]->out_file_type, command->simple_commands[i]->\
			out_file);
		i++;
	}
}

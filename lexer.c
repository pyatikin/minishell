#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <readline/readline.h>

char	*get_directory(char *str)
{
	int		i;
	char	*dir;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	while (*str != '/' && i >= 0)
	{
		str--;
		i--;
	}
	if (i < 0)
		return (NULL);
	dir = malloc(sizeof(char) * (i + 1));
	dir[i + 1] = '\0';
	while (i >= 0)
	{
		dir[i] = *str;
		str--;
		i--;
	}
	return (dir);
}

int	check_command(t_simpleCommand *cur_command)
{
	char		*com;
	struct stat	sb;

	com = cur_command->arguments[0];
	if (com == "echo\0" || com == "cd\0" || com == "pdw\0" || com == "export\0" || com == "unset\0" || com == "env\0" || com == "exit\0")
		return (0);
	else if (access(com, F_OK) == 0)
	{
		if (stat(com, &sb) > 0 && ((sb.st_mode & S_IFMT) != S_IFREG || (sb.st_mode & S_IFMT) != S_IFDIR))
		{
			printf("%s: No such file or directory\n", com);
			return (1);
		}
		return (0);
	}
	else
		printf("%s: command not found\n", com);
	return (1);
}

void	lexer(t_command *command)
{
	int	i;

	i = 0;
	while (i < command->number_of_simple_commands)
	{
		if (check_command(command->simple_commands[i]))
			printf("ERROR\n");
		i++;
	}
}



//////////////////////////////!
//int main(int argc, char **argv, char *envp[])
//{
////	t_command	*first;
////	t_simpleCommand	cur;
////	t_simpleCommand	cur2;
////
////	first = malloc(sizeof(t_command));
////	first->number_of_simple_commands = 2;
////	first->simple_commands = malloc(sizeof(t_simpleCommand) * first->number_of_simple_commands);
////	cur.number_of_arguments = 2;
////	cur.arguments = malloc(sizeof(char*) * cur.number_of_arguments);
////	cur.arguments[0] = "echo\0";
////	cur.arguments[1] = "me\0";
////	first->simple_commands[0] = &cur;
////
////	cur2.number_of_arguments = 2;
////	cur2.arguments = malloc(sizeof(char*) * cur.number_of_arguments);
////	cur2.arguments[0] = "ls\0";
////	cur2.arguments[1] = "-la\0";
////	first->simple_commands[1] = &cur2;
////
////	//lexer(first);
////	//printf("%s \n", get_directory("qwe/"));
////
//	int ret;
//	int i = 0;
//	char *cmd[] = {"ls","-l", (char *)0 };
//	char **env;
//	struct stat	sb;
//	env = envp;
//	//while(env[i])
//	//{
//	//	printf("%s\n", env[i]);
//	//	i++;
//	//}
//	//printf("\n");
//	//if (access("/bin/lsa", F_OK) == 0)
//	{
//		if (stat("/bin/lsa", &sb) < 0 && ((sb.st_mode & S_IFMT) != S_IFREG || (sb.st_mode & S_IFMT) != S_IFDIR))
//		{
//			printf("%s: No such file or directory\n", "/bin/lsa");
//			return (1);
//		}
//		ret = execve ("/bin/ls", cmd, envp);
//	}
//
////	 while (1)
////    {
////        char * str = readline(BEGIN(49, 34)"Myshell $ "CLOSE);
////        free(str);
////    }
////
////	
////	
////
////}
//
//// #include <stdlib.h>
//// #include <readline/readline.h>
//
//// int main(void)
//// {
////     while (1)
////     {
////         char * str = readline("Myshell $ ");
////         free(str);
////     }
// }
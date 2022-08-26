#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <readline/readline.h>
//int main(int argc, char **argv, char **envp)
//{
//    int ret;
//	int i = 0;
//	char *cmd[] = {"cat", (char *)0 };
//    char *com = "/bin/cat";
//	char **env;
//	struct stat	sb;
//	env = envp;
//	//while(env[i])
//	//{
//	//	printf("%s\n", env[i]);
//	//	i++;
//	//}
//	//printf("\n");
//    char *file;
//    int fd;
//    while(1)
//    {
//        file = readline(BEGIN(30, 36) MYSHELL CLOSE);
//        fd = open(file, O_RDONLY);
//        //write(fd, "123\0", 5);
//        dup2(fd, 0);
//        //close(fd);
//	    if (access(com, F_OK) == 0)
//	    {
//	    	if (stat(com, &sb) > 0 && ((sb.st_mode & S_IFMT) != S_IFREG || (sb.st_mode & S_IFMT) != S_IFDIR))
//	    	{
//	    		printf("%s: No such file or directory\n", com);
//	    		return (1);
//	    	}
//	    	ret = execve (com, cmd, envp);
//	    }
//
//    }
//
//}
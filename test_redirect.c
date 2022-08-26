//#include "minishell.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <sys/stat.h>
//#include <string.h>
//#include <fcntl.h>
//#include <readline/readline.h>
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
//    int fd1, fd2;
//    fd1 = open("01", O_RDONLY | O_CREAT);
//    
//    //while(1)
//    //{
//    //    file = readline(BEGIN(30, 36) MYSHELL CLOSE);
//    //    fd = open(file, O_RDONLY);
//    //    //write(fd, "123\0", 5);
//    //    dup2(fd, 0);
//    //    //close(fd);
//	//    if (access(com, F_OK) == 0)
//	//    {
//	//    	if (stat(com, &sb) > 0 && ((sb.st_mode & S_IFMT) != S_IFREG || (sb.st_mode & S_IFMT) != S_IFDIR))
//	//    	{
//	//    		printf("%s: No such file or directory\n", com);
//	//    		return (1);
//	//    	}
//	//    	ret = execve (com, cmd, envp);
//	//    }
////
//    //}
//
//}
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int
main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t cpid;
    char buf;
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0) {    /* Потомок читает из канала */
        close(pipefd[1]);          /* Закрывает неиспользуемый конец для записи */
        while (read(pipefd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        _exit(EXIT_SUCCESS);
    } else {            /* Родитель пишет значение argv[1] в канал */
        close(pipefd[0]);          /* Закрывает неиспользуемый конец для чтения */
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);          /* Читатель видит EOF */
        wait(NULL);                /* Ожидание потомка */
        exit(EXIT_SUCCESS);
    }
}
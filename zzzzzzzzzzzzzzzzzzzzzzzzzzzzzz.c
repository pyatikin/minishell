#include "minishell.h"
int	main(int argc, char **argv, char **env)
{
    char *a[] = {"cat", "< 1", NULL};
    execve("/bin/cat", a, env);
    return 0;
}

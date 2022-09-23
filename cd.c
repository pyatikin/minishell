#include "minishell.h"

void	print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

int	update_oldpwd(t_env_var *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!(oldpwd))
		return (1);
	if (find_env(env->env, "OLDPWD") == -1)
		add_new_env(env, oldpwd);
	if (find_env(env->env, "OLDPWD") != -1)
	{
		find_and_del(env, "OLDPWD");
		add_new_env(env, oldpwd);
	}
	free(oldpwd);
	return (0);
}

void	gtp_dop(t_env_var *env, int *env_path)
{
	update_oldpwd(env);
	(*env_path) = find_env(env->env, "HOME\0");
	if ((*env_path) == -1)
		ft_putendl_fd("minishell : cd: HOME not set", 2);
}

int	go_to_path(int option, t_env_var *env)
{
	int		ret;
	int		env_path;
	char	*tmp;

	env_path = -1;
	if (option == 0)
	{
		gtp_dop(env, &env_path);
		if (env_path == -1)
			return (1);
	}
	else if (option == 1)
	{
		env_path = find_env(env->env, "OLDPWD\0");
		if (env_path == -1)
			ft_putendl_fd("minishell : cd: OLDPWD not set", 2);
		if (env_path == -1)
			return (1);
		update_oldpwd(env);
	}
	tmp = get_env_value(env->env[env_path]);
	ret = chdir(tmp);
	free(tmp);
	return (ret);
}

int	ft_cd(char **args, t_env_var *env)
{
	int		cd_ret;

	cd_ret = 0;
	if (args[1] == NULL)
		return (go_to_path(0, env));
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, env);
	else
	{
		update_oldpwd(env);
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			print_error(args);
	}
	return (cd_ret);
}

#include "minishell.h"

int	builtin_echo(char **args)
{
	int	i;

	i = 1;
	if (ft_strncmp(args[1], "-n", 2) == 0)
		i = 2;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[++i])
			printf(" ");
	}
	if (ft_strncmp(args[1], "-n", 2) != 0)
		printf("\n");
	return (0);
}

int	builtin_cd(char **args)
{
	char	cwd[256];
	char	*old_wd;
	size_t	len;

	if (chdir(args[1]) < 0)
		perror("chdir");
	old_wd = mini_getenv("PWD");
	len = ft_strlen(old_wd);
	getcwd(cwd, sizeof(cwd));
	if (ft_strlen(cwd) > len)
		len = ft_strlen(cwd);
	if (ft_strncmp(cwd, old_wd, len) != 0)
		mini_setenv("OLDPWD", old_wd);
	mini_setenv("PWD", cwd);
	return (0);
}

int	builtin_pwd(void)
{
	char	cwd[256];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (0);
}

int	builtin_export(char **args)
{
	mini_setenv(args[1], "test");
	return (0);
}

int	builtin_unset(char **args)
{
	int		i;

	i = 0;
	while (ft_strncmp(args[1], g_var.env[i], ft_strlen(args[1])) != 0)
		i++;
	rm_from_2d(g_var.env, i);
	return (0);
}

int	builtin_env(void)
{
	int	i;

	i = 0;
	while (g_var.env[i])
	{
		printf("%s\n", g_var.env[i]);
		i++;
	}
	return (0);
}

int	builtin_exit(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

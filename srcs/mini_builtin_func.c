#include "minishell.h"

int	builtin_echo(char **args)
{
	if (args[1])
	{
		if (ft_strncmp(args[1], "-n", 2) == 0)
			print_2d(args + 2, ' ');
		else
		{
			print_2d(args + 1, ' ');
			printf("\n");
		}
	}
	else
		printf("\n");
	return (EXIT_SUCCESS);
}

int	builtin_cd(char **args)
{
	char	cwd[256];
	char	*old_wd;
	char	*target;

	target = args[1];
	if (!target)
		target = "..";
	if (chdir(target) < 0)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	old_wd = mini_getenv("PWD");
	getcwd(cwd, sizeof(cwd));
	if (old_wd)
		if (ft_strcmp(cwd, old_wd) != 0)
			mini_setenv("OLDPWD", old_wd);
	mini_setenv("PWD", cwd);
	return (EXIT_SUCCESS);
}

int	builtin_pwd(void)
{
	char	cwd[256];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}

int	builtin_export(char **args)
{
	int	status;

	status = EXIT_SUCCESS;
	if (!args[1])
	{
		print_2d(g_var.env, '\n');
		printf("\n");
	}
	while (*++args)
	{
		if (status == EXIT_SUCCESS)
			status = export_env(*args);
		else
			export_env(*args);
	}
	return (status);
}

int	builtin_unset(char **args)
{
	char	*temp;
	int		i;

	while (*++args)
	{
		temp = ft_strjoin(*args, "=");
		i = 0;
		while (ft_strncmp(temp, g_var.env[i], ft_strlen(temp)) != 0)
			if (!g_var.env[++i])
				break ;
		free(temp);
		if (g_var.env[i])
			rm_from_2d(&g_var.env, i);
	}
	return (EXIT_SUCCESS);
}

int	builtin_env(void)
{
	print_2d(g_var.env, '\n');
	printf("\n");
	return (EXIT_SUCCESS);
}

int	builtin_exit(void)
{
	mini_exit(&g_var);
	return (EXIT_SUCCESS);
}

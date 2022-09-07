#include "minishell.h"

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
	int	status;

	status = EXIT_SUCCESS;
	while (*++args)
	{
		if (status == EXIT_SUCCESS)
			status = unset_env(*args);
		else
			unset_env(*args);
	}
	return (status);
}

int	unset_env(char *arg)
{
	char	*temp;
	int		i;

	if (is_envname_valid(arg) == 2)
	{
		temp = ft_strjoin(arg, "=");
		i = 0;
		while (ft_strncmp(temp, g_var.env[i], ft_strlen(temp)) != 0)
			if (!g_var.env[++i])
				break ;
		free(temp);
		if (g_var.env[i])
			rm_from_2d(&g_var.env, i);
		exp_stack_remove_if(&g_var.export, arg);
		return (EXIT_SUCCESS);
	}
	ft_putstr_fd("unset: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

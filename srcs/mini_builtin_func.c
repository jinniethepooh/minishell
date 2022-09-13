/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtin_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prrattan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:56:59 by prrattan          #+#    #+#             */
/*   Updated: 2022/09/13 11:56:59 by prrattan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		target = mini_getenv("HOME");
	if (chdir(target) < 0)
	{
		if (mini_getenv("HOME"))
			perror("cd");
		else
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
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

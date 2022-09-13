/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtin_func2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prrattan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:57:02 by prrattan          #+#    #+#             */
/*   Updated: 2022/09/13 11:57:04 by prrattan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(char **args)
{
	int	status;

	status = EXIT_SUCCESS;
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
	put_error("unset", arg, EXIT_FAILURE);
	return (EXIT_FAILURE);
}

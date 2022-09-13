/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prrattan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 11:56:08 by prrattan          #+#    #+#             */
/*   Updated: 2022/09/13 11:56:09 by prrattan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mini_export_setenv(char *name);
static int	is_export_bef(char *name);
static void	export_loop_checker(char ***args);

char	**map_args_to_export(char ***args)
{
	// char	*name;
	// char	*val;
	int		i;

	if (!(args && *args))
		return (0);
	i = -1;
	while ((*args)[++i])
	{
		if (is_envname_valid((*args)[i]) != 1)
		{
			while (--i >= 0)
				rm_from_2d(args, i);
			return (*args);
		}
	}
	export_loop_checker(args);
	// while (**args)
	// {
	// 	name = ft_strdup(**args);
	// 	*ft_strchr(name, '=') = 0;
	// 	val = ft_strdup(ft_strchr(**args, '=') + 1);
	// 	rm_from_2d(args, 0);
	// 	exp_stack_push(&g_var.export, exp_stack_new(name, val));
	// 	if (mini_getenv(name) || is_export_bef(name))
	// 		mini_export_setenv(name);
	// }
	return (*args);
}

int	export_env(char *arg)
{
	char	*name;

	if (is_envname_valid(arg))
	{
		if (is_envname_valid(arg) == 1)
		{
			name = ft_strdup(arg);
			*ft_strchr(name, '=') = 0;
			exp_stack_push(&g_var.export,
				exp_stack_new(name, ft_strdup(ft_strchr(arg, '=') + 1)));
			mini_export_setenv(name);
		}
		else
			mini_export_setenv(arg);
		return (EXIT_SUCCESS);
	}
	put_error("export", arg, EXIT_FAILURE);
	return (EXIT_FAILURE);
}

static void	mini_export_setenv(char *name)
{
	t_export	*exp;

	exp = g_var.export;
	while (exp)
	{
		if (ft_strcmp(exp->name, name) == 0 && exp->val)
		{
			mini_setenv(exp->name, exp->val);
			exp_stack_remove_if(&g_var.export, name);
			return ;
		}
		exp = exp->prev;
	}
	exp_stack_push(&g_var.export, exp_stack_new(ft_strdup(name), 0));
}

static int	is_export_bef(char *name)
{
	t_export	*exp;

	exp = g_var.export;
	while (exp)
	{
		if (ft_strcmp(exp->name, name) == 0)
			if (!exp->val)
				return (1);
		exp = exp->prev;
	}
	return (0);
}

static void	export_loop_checker(char ***args)
{
	char	*name;
	char	*val;

	while (**args)
	{
		name = ft_strdup(**args);
		*ft_strchr(name, '=') = 0;
		val = ft_strdup(ft_strchr(**args, '=') + 1);
		rm_from_2d(args, 0);
		exp_stack_push(&g_var.export, exp_stack_new(name, val));
		if (mini_getenv(name) || is_export_bef(name))
			mini_export_setenv(name);
	}
}

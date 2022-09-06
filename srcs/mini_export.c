#include "minishell.h"

static void	mini_export_setenv(char *name);

char	**map_val_to_export(char ***args)
{
	char	*name;
	int		i;

	if (!*args)
		return (0);
	i = 0;
	while ((*args)[i])
	{
		if (is_envname_valid((*args)[i]) != 1) // without '='
			break ;
		name = ft_strdup((*args)[i]);
		*ft_strchr(name, '=') = 0;
		exp_stack_push(&g_var.export,
			exp_stack_new(name, ft_strdup(ft_strchr((*args)[i], '=') + 1)));
		if (mini_getenv(name) || is_export_bef(name))
			mini_export_setenv(name);
		rm_from_2d(args, i);
	}
	return (*args);
}

int	export_env(char *arg)
{
	char	*name;

	if (is_envname_valid(arg))
	{
		if (is_envname_valid(arg) == 1) // with '='
		{
			name = ft_strdup(arg);
			*ft_strchr(name, '=') = 0;
			exp_stack_push(&g_var.export,
				exp_stack_new(name, ft_strdup(ft_strchr(arg, '=') + 1)));
			mini_export_setenv(name);
		}
		else // without '='
			mini_export_setenv(arg);
		return (EXIT_SUCCESS);
	}
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static void	mini_export_setenv(char *name)
{
	t_export	*exp;
	int			to_set;

	to_set = 1;
	exp = g_var.export;
	while (exp)
	{
		if (ft_strcmp(exp->name, name) == 0)
		{
			if (to_set && exp->status > 0)
				mini_setenv(exp->name, exp->val);
			if (exp->status)
				to_set = 0;
			if (exp->status >= 0)
				exp->status = 0;
		}
		exp = exp->prev;
	}
	if (to_set)
	{
		exp_stack_push(&g_var.export, exp_stack_new(ft_strdup(name), 0));
		g_var.export->status = -1;
	}
}

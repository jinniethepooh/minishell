#include "minishell.h"

static void	mini_export_setenv(char *name);
static int	is_export_bef(char *name);

char	**map_val_to_export(char ***args)
{
	char	*name;
	int		i;

	if (!*args)
		return (0);
	i = 0;
	while ((*args)[i])
	{
		if (is_envname_valid((*args)[i]) != 1)
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
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
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

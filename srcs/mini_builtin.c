#include "minishell.h"

static void	set_builtin_str(char **b_str)
{
	b_str[0] = "echo";
	b_str[1] = "pwd";
	b_str[2] = "env";
	b_str[3] = "cd";
	b_str[4] = "export";
	b_str[5] = "unset";
	b_str[6] = "exit";
}

static void	set_builtin_func(int (**b_func)())
{
	b_func[0] = &builtin_echo;
	b_func[1] = &builtin_pwd;
	b_func[2] = &builtin_env;
	b_func[3] = &builtin_cd;
	b_func[4] = &builtin_export;
	b_func[5] = &builtin_unset;
	b_func[6] = &builtin_exit;
}

int	is_builtin(char **args)
{
	char	*b_str[7];
	int		i;

	if (args)
	{
		i = 0;
		set_builtin_str(b_str);
		while (i < 7)
		{
			if (ft_strcmp(args[0], b_str[i]) == 0)
				return (i + 1);
			i++;
		}
	}
	return (0);
}

int	call_builtin(t_command *c)
{
	char	*b_str[7];
	int		(*b_func[7])();
	int		i;

	if (c->cmd_args)
	{
		i = 0;
		set_builtin_str(b_str);
		set_builtin_func(b_func);
		while (i < 7)
		{
			if (ft_strcmp(c->cmd_args[0], b_str[i]) == 0)
				return ((b_func[i])(c->cmd_args));
			i++;
		}
	}
	return (0);
}

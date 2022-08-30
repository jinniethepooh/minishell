#include "minishell.h"

static void	set_builtin_str(char **b_str)
{
	b_str[0] = "echo";
	b_str[1] = "cd";
	b_str[2] = "pwd";
	b_str[3] = "export";
	b_str[4] = "unset";
	b_str[5] = "env";
	b_str[6] = "exit";
}

static void	set_builtin_func(int (**b_func)())
{
	b_func[0] = &builtin_echo;
	b_func[1] = &builtin_cd;
	b_func[2] = &builtin_pwd;
	b_func[3] = &builtin_export;
	b_func[4] = &builtin_unset;
	b_func[5] = &builtin_env;
	b_func[6] = &builtin_exit;
}

int	is_builtin(char **args)
{
	char	*b_str[7];
	size_t	len;
	int		i;

	i = 0;
	set_builtin_str(b_str);
	while (i < 7)
	{
		len = ft_strlen(args[0]);
		if (ft_strlen(b_str[i]) > len)
			len = ft_strlen(b_str[i]);
		if (ft_strncmp(args[0], b_str[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	call_builtin(char **args)
{
	char	*b_str[7];
	int		(*b_func[7])();
	size_t	len;
	int		i;

	i = 0;
	set_builtin_str(b_str);
	set_builtin_func(b_func);
	while (i < 7)
	{
		len = ft_strlen(args[0]);
		if (ft_strlen(b_str[i]) > len)
			len = ft_strlen(b_str[i]);
		if (ft_strncmp(args[0], b_str[i], len) == 0)
		{
			//printf("called %s\n", b_str[i]);
			(b_func[i])(args);
			return (1);
		}
		i++;
	}
	return (0);
}

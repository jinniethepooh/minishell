#include "minishell.h"

int	mini_setenv(char *name, char *val)
{
	char	*temp;
	int		i;

	temp = ft_strjoin(name, "=");
	i = 0;
	while (ft_strncmp(temp, g_var.env[i], ft_strlen(temp)) != 0)
		if (!g_var.env[++i])
			break ;
	if (g_var.env[i])
	{
		free(g_var.env[i]);
		g_var.env[i] = ft_strjoin(temp, val);
	}
	else
		add_to_2d(&g_var.env, ft_strjoin(temp, val), i - 1);
	free(temp);
	return (0);
}

char	*mini_getenv(char *name)
{
	char	*temp;
	int		i;

	temp = ft_strjoin(name, "=");
	i = 0;
	while (ft_strncmp(temp, g_var.env[i], ft_strlen(temp)) != 0)
		if (!g_var.env[++i])
			break ;
	free(temp);
	if (g_var.env[i])
		return (g_var.env[i] + ft_strlen(name) + 1);
	return (0);
}

int	is_envname_valid(char *name)
{
	if (name && *name)
	{
		if (ft_isalpha(*name) || *name == '_')
		{
			while (*name && (ft_isalnum(*name) || *name == '_'))
				name++;
			if (*name == '=')
				return (1);
			if (!*name)
				return (2);
		}
	}
	return (0);
}

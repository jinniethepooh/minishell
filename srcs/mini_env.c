#include "minishell.h"

int	mini_setenv(char *name, char *val)
{
	char	*temp;
	int		i;

	temp = ft_strjoin(name, "=");
	i = 0;
	while (ft_strncmp(temp, g_var.env[i], ft_strlen(temp)) != 0)
		i++;
	if (g_var.env[i])
	{
		free(g_var.env[i]);
		g_var.env[i] = ft_strjoin(temp, val);
	}
	else
		add_to_2d(g_var.env, ft_strjoin(temp, val));
	free(temp);
	return (0);
}

char	*mini_getenv(char *name)
{
	char	*temp;
	int		len;
	int		i;

	temp = ft_strjoin(name, "=");
	len = ft_strlen(temp);
	i = 0;
	while (ft_strncmp(temp, g_var.env[i], len) != 0)
		i++;
	free(temp);
	if (g_var.env[i])
		return (g_var.env[i] + len);
	return (0);
}

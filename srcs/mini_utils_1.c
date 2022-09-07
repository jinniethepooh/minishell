#include "minishell.h"

int	ft_wcount(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			++s;
		if (*s != c && *s)
			++count;
		while (*s != c && *s)
			++s;
	}
	return (count);
}

int	ft_isquotes(char c)
{
	return (c == '\'' || c == '"');
}

int	ft_isredir(char c)
{
	return (c == '<' || c == '>');
}

int  ft_loop_until(const char *s, char c, int flag)
{
	int	len;

	len = 0;
	if (flag)
	{
		while (s[len] && s[len] == c)
			++len;
	}
	else
	{
		while (s[len] && s[len] != c)
			++len;
	}
	return (len);
}

void	put_error(char *title, char *token, int status)
{
	g_var.exit_status = status;
	ft_putstr_fd("tinyshell: ", STDERR_FILENO);
	if (status == EXIT_FAILURE)
	{
		ft_putstr_fd(title, STDERR_FILENO);
		ft_putstr_fd(": `", STDERR_FILENO);
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier", STDERR_FILENO);
	}
	else if (status == 2)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

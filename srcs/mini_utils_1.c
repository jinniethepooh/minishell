#include "minishell.h"

int	ft_isquotes(char c)
{
	return (c == '\'' || c == '"');
}

int	ft_isredir(char c)
{
	return (c == '<' || c == '>');
}

int	ft_loop_until(const char *s, char c, int flag)
{
	int	len;

	len = 0;
	if (flag)
	{
		while (s[len] && s[len] == c)
			++len;
	}
	else
		return (pos_in_str((char *)s, c));
	return (len);
}

int	redir_checker(char *str)
{
	if (!*str)
		put_error(NULL, "newline", 2);
	else
	{
		*(str + 1) = 0;
		put_error(NULL, str, 2);
	}
	return (0);
}

void	put_error(char *title, char *token, int status)
{
	g_var.exit_status = status;
	ft_putstr_fd("tinyshell: "RED, STDERR_FILENO);
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
	else if (status == 'h')
	{
		ft_putstr_fd("warning: here-document delimited ", STDERR_FILENO);
		ft_putstr_fd("by end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putstr_fd("')", STDERR_FILENO);
	}
	ft_putstr_fd("\n"RES, STDERR_FILENO);
}

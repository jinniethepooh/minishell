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

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r');
}

int	ft_isspecial(char c)
{
	if (c == '-')
		return ('-');
	// if (c == '\\')
	// 	return ('\\');
	// if (c == '/')
	// 	return ('s');
	if (c == '>')
		return ('>');
	if (c == '<')
		return ('<');
	if (c == '|')
		return ('|');
	return (ft_isspace(c));
}

int loop_quotes(void)
{
	int	i;
	int	curr_q;

	i = 0;
	curr_q = 0;
	while (g_var.from_rl[i])
	{
		if (g_var.from_rl[i] == '\'' || g_var.from_rl[i] == '"')
		{
			curr_q = g_var.from_rl[i];
			++i;
		}
		while (g_var.from_rl[i] && g_var.from_rl[i] != curr_q)
			++i;
		if (g_var.from_rl[i] == curr_q)
			curr_q = 0;
		if (g_var.from_rl[i])
			++i;
	}
	return (curr_q);
}

int	ft_is_valid_quote(void)
{
	if (loop_quotes())
	{
		printf("tinyshell: "RED"invaid quotes\n");
		return (1);
	}
	return (0);
}
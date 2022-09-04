#include "minishell.h"

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

static int quotes_checker(void)
{
	int	i;
	int	curr_q;

	i = 0;
	curr_q = 0;
	while (g_var.from_rl[i] && !ft_isquotes(g_var.from_rl[i]))
		++i;
	while (g_var.from_rl[i])
	{
		if (ft_isquotes(g_var.from_rl[i]))
			curr_q = g_var.from_rl[i++];
		i += ft_loop_until(&g_var.from_rl[i], curr_q, 0);
		if (g_var.from_rl[i] == curr_q)
			curr_q = 0;
		if (g_var.from_rl[i])
			++i;
	}
	return (curr_q);
}

int	ft_isvalid_quotes(void)
{
	if (quotes_checker())
	{
		printf("tinyshell: "RED"invaid quotes\n");
		return (0);
	}
	return (1);
}
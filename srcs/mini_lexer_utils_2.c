#include "minishell.h"

// detect var from env

int  ft_loop_quotes(const char *s, char q)
{
    int len;

    len = 0;
    while (s[len] && s[len] != q)
        ++len;
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
        i += ft_loop_quotes(&g_var.from_rl[i], curr_q);
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
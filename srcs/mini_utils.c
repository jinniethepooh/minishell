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

int	ft_isquotes(char c)
{
	return (c == '\'' || c == '"');
}

int	ft_isredir(char c)
{
	return (c == '<' || c == '>');
}

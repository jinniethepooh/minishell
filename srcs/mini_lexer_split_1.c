#include "minishell.h"

static int	ft_piece_loop(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		if (ft_isquotes(s[i]) && s[i + 1])
			i += (ft_loop_until(&s[i + 1], s[i], 0) + 1);
		i++;
	}
	return (i);
}

static int	ft_piece(char *s, char c)
{
	int	piece;

	piece = 0;
	if (*s != c)
		piece++;
	while (*s)
	{
		if (ft_isquotes(*s))
			s += (ft_loop_until(s + 1, *s, 0) + 1);
		if (*s == c && *(s + 1) != c && *(s + 1))
			piece++;
		if (*s)
			s++;
	}
	return (piece);
}

static char	*ft_strdup_untilc(const char *s, char c)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_piece_loop(s, c) + 1;
	str = (char *)malloc(len * sizeof(char));
	while (s[i] && i < len - 1)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	**pipe_split(char const *s, char c)
{
	int		i;
	int	 j;
	char	*cpy;
	char	**arr;

	i = 0;
	cpy = ft_strdup(s);
	arr = malloc((ft_piece(cpy, c) + 1) * sizeof(char *));
	j = ft_loop_until(cpy, c, 1);
	while (cpy[j])
	{
		if (cpy[j] != c)
		{
			arr[i++] = ft_strdup_untilc(&cpy[j], c);
			j += ft_piece_loop(&cpy[j], c);
		}
		else
			j += ft_loop_until(&cpy[j], c, 1);
	}
	arr[i] = 0;
	free(cpy);
	return (arr);
}

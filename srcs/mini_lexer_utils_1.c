#include "minishell.h"

// split str regarding ' / "
// split |  >> done
// clean from pipe_split > concern 
// split ' '

static int	ft_strlen_untilc(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
	{
        if (ft_isquotes(s[len]) && s[len + 1])
            len += (ft_loop_quotes(&s[len + 1], s[len]) + 1);
		len++;
	}
	return (len);
}

static char	*ft_strdup_untilc(const char *s, char c)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((ft_strlen_untilc(s, c) + 1) * sizeof(*str));
	while (s[i] && i < ft_strlen_untilc(s, c))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

static int	ft_piece(char *s, char c)
{
	int	piece;

	piece = 0;
	if (*s != c && !ft_isquotes(*s))
		piece++;
	while (*s)
	{
        if (ft_isquotes(*s))
            s += ft_loop_quotes(s, *s);
		if (*s == c && *(s + 1) != c && *(s + 1))
			piece++;
        if (*s)
            s++;
	}
	return (piece);
}

char	**pipe_split(char const *s, char c)
{
	int		i;
    int     j;
	char	*cpy;
	char	**arr;

	i = 0;
    j = 0;
	cpy = ft_strdup(s);
	arr = malloc((ft_piece(cpy, c) + 1) * sizeof(*arr));
	if (cpy[j] != c && cpy[j])
		arr[i++] = ft_strdup_untilc(&cpy[j], c);
	while (cpy[j])
	{
		if (cpy[j] == c && cpy[j + 1] != c && cpy[j + 1])
			arr[i++] = ft_strdup_untilc(&cpy[j + 1], c);
		j += ft_strlen(arr[i - 1]);
	}
	arr[i] = 0;
	free(cpy);
	return (arr);
}

// char    **cmd_split();
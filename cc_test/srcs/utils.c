#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		++len;
	return (len);
}

static int	loop_join(char *src, char *dst)
{
	int	i;

	i = 0;
	while (src && src[i])
	{
		dst[i] = src[i];
		++i;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	res = (char *)malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (!res)
		return (NULL);
	i = loop_join((char *)s1, res);
	i += loop_join((char *)s2, &res[i]);
	res[i] = '\0';
	// to free
	// if (s1)
	// 	free((void *)s1);
	return (res);
}

// TBD
// char	*ft_strchr(const char *s, int c)
// {
// 	int	len;
// 	int	i;

//     if (!s)
//         return (NULL);
// 	len = ft_strlen((char *)s);
// 	i = -1;
// 	while (s[++i])
// 		if (s[i] == (unsigned char)c)
// 			return ((char *)&s[i]);
// 	if (i != len - 1 && c == '\0')
// 		return ((char *)&s[i]);
// 	return (NULL);
// }
#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	i = 0;
	while (cs1[i] == cs2[i] && cs1[i] && cs2[i])
		i++;
	return (cs1[i] - cs2[i]);
}

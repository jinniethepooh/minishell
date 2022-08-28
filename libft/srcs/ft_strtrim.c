/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prrattan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:01:24 by prrattan          #+#    #+#             */
/*   Updated: 2022/02/22 10:37:39 by prrattan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_str(char c, char *str)
{
	if (str && *str)
	{
		while (*str)
			if (c == *str++)
				return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*newstr;

	newstr = ft_strdup(s1);
	start = newstr - 1;
	while (*++start)
		if (!is_in_str(*start, (char *)set))
			break ;
	if (!*start)
	{
		free(newstr);
		return (ft_strdup(""));
	}
	end = start + ft_strlen(start);
	while (*--end)
		if (!is_in_str(*end, (char *)set))
			break ;
	*++end = 0;
	ft_memmove(newstr, start, end - start + 1);
	return (newstr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prrattan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 10:54:04 by prrattan          #+#    #+#             */
/*   Updated: 2022/02/20 10:54:09 by prrattan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s);

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len_s1;
	char	*new_s;

	i = 0;
	len_s1 = ft_strlen(s1);
	new_s = malloc((len_s1 + ft_strlen(s2) + 1) * sizeof(*new_s));
	if (!new_s)
		return (0);
	while (s1[i])
	{
		new_s[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		new_s[len_s1 + i] = s2[i];
		i++;
	}
	new_s[len_s1 + i] = 0;
	return (new_s);
}

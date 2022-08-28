/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prrattan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:04:40 by prrattan          #+#    #+#             */
/*   Updated: 2022/02/21 10:04:02 by prrattan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	i = n - 1;
	if (n <= 0)
		return (0);
	while (*cs1 == *cs2 && cs1 && cs2 && i-- > 0)
	{
		cs1++;
		cs2++;
	}
	if (*cs1 > *cs2)
		return (1);
	else if (*cs1 < *cs2)
		return (-1);
	return (0);
}

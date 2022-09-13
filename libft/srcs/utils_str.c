/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prrattan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:07:12 by prrattan          #+#    #+#             */
/*   Updated: 2022/09/13 12:07:13 by prrattan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_v2.h"

int	count_in_str(char *str, char c)
{
	int	count;

	count = 0;
	if (str)
	{
		while (*str)
			if (c == *str++)
				count++;
	}
	return (count);
}

int	pos_in_str(char *str, char c)
{
	int	pos;

	pos = 0;
	if (str)
	{
		while (str[pos])
		{
			if (str[pos] == c)
				return (pos);
			pos++;
		}
	}
	return (pos);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r');
}

int	ft_isspace_str(char *s)
{
	while (*s)
	{
		if (!ft_isspace(*s))
			return (0);
		s++;
	}
	return (1);
}

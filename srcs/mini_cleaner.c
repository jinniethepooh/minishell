/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:46:17 by cchetana          #+#    #+#             */
/*   Updated: 2022/09/13 19:46:19 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*cmd_cleaner_loop(char *src, int flag);

static char	*cmd_var_gen(char *src)
{
	int		i;
	char	*tmp;
	char	*dst;

	i = get_cmd_move(src, 1) - 1;
	tmp = ft_substr(src + 1, 0, i);
	dst = mini_getenv(tmp);
	free (tmp);
	if (dst)
		return (ft_strdup(dst));
	return (NULL);
}

static char	*cmd_cleaner_var(char *src)
{
	if (*(src + 1) == '?')
		return (ft_itoa(g_var.exit_status));
	else
		return (cmd_var_gen(src));
}

static char	*cmd_cleaner_quotes(char *src)
{
	char	*dst;
	char	*tmp;

	if (*src == '"')
	{
		tmp = ft_substr(&src[1], 0, ft_loop_until(&src[1], src[0], 0));
		dst = cmd_cleaner_loop(tmp, 0);
		free (tmp);
		return (dst);
	}
	else
		return (ft_substr(&src[1], 0, ft_loop_until(&src[1], src[0], 0)));
}

static void	*cmd_cleaner_loop(char *src, int flag)
{
	char	*dst;
	char	*tmp;
	char	*tmp2;
	int		i;

	dst = NULL;
	i = 0;
	while (src[i])
	{
		if (ft_isquotes(src[i]) && flag)
			tmp = cmd_cleaner_quotes(src + i);
		else if (src[i] == '$' && (get_var_skip(src[i + 1]) || \
			src[i + 1] == '?'))
			tmp = cmd_cleaner_var(src + i);
		else
			tmp = ft_substr(src + i, 0, get_cmd_move(src + i, flag));
		tmp2 = dst;
		dst = ft_strjoin(dst, tmp);
		free(tmp);
		free(tmp2);
		i += get_cmd_move(src + i, flag);
	}
	return (dst);
}

char	**cmd_cleaner(char **arr)
{
	char	**clean;
	int		i;

	i = 0;
	clean = (char **)malloc((size_2d(arr) + 1) * sizeof(char *));
	if (!clean)
		return (NULL);
	while (arr[i])
	{
		clean[i] = cmd_cleaner_loop(arr[i], 1);
		if (!clean[i])
			clean[i] = ft_substr("", 0, 1);
		++i;
	}
	clean[i] = 0;
	free_2d(arr);
	return (clean);
}

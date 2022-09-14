/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prrattan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:01:00 by prrattan          #+#    #+#             */
/*   Updated: 2022/09/13 12:01:02 by prrattan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_access_cmd(char **cmd_args, char **env_paths);

int	get_num_cmd(t_shell *sh)
{
	t_command	*c;
	int			n;

	n = 0;
	c = sh->command;
	while (c)
	{
		n++;
		c = c->next;
	}
	return (n);
}

char	*set_cmd_path(t_command *c)
{
	char	**env_paths;

	c->cmd_path = 0;
	if (mini_getenv("PATH"))
	{
		env_paths = ft_split(mini_getenv("PATH"), ':');
		c->cmd_path = get_access_cmd(c->cmd_args, env_paths);
		free_2d(env_paths);
	}
	else
		c->cmd_path = ft_strdup(c->cmd_args[0]);
	return (c->cmd_path);
}

static char	*get_access_cmd(char **cmd_args, char **env_paths)
{
	char	*path;
	char	*temp;
	int		i;

	if (!(cmd_args && env_paths))
		return (0);
	if (ft_strlen(cmd_args[0]) == 0)
		return (0);
	if (ft_strchr(cmd_args[0], '/'))
		return (ft_strdup(cmd_args[0]));
	i = 0;
	while (env_paths[i])
	{
		temp = ft_strjoin(env_paths[i], "/");
		path = ft_strjoin(temp, cmd_args[0]);
		free(temp);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		if (!env_paths[++i])
			path = 0;
	}
	return (path);
}

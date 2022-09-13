/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:50:03 by cchetana          #+#    #+#             */
/*   Updated: 2022/09/13 19:50:03 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_cmd(t_command **cmd, char *raw_cmd)
{
	*cmd = malloc(sizeof(**cmd));
	if (!*cmd)
		mini_exit(&g_var);
	(*cmd)->fd_in = STDIN_FILENO;
	(*cmd)->fd_out = STDOUT_FILENO;
	(*cmd)->cmd_args = cmd_split(raw_cmd, ' ');
	(*cmd)->cmd_path = NULL;
}

void	get_cmd(void)
{
	t_command	**cmd;
	char		**tmp;
	int			i;

	i = 0;
	if (g_var.from_rl)
	{
		cmd = &g_var.command;
		clear_command(cmd);
		tmp = pipe_split(g_var.from_rl, '|');
		while (tmp[i])
		{
			manage_cmd(cmd, tmp[i]);
			cmd = &(*cmd)->next;
			++i;
		}
		free_2d(tmp);
		*cmd = 0;
	}
}

#include "minishell.h"

static void	manage_cmd(t_command **cmd, char *raw_cmd)
{
	*cmd = malloc(sizeof(**cmd));
	if (!*cmd)
		mini_exit(&g_var);
	(*cmd)->fd_in = STDIN_FILENO;
	(*cmd)->fd_out = STDOUT_FILENO;
	(*cmd)->cmd_args = cmd_split(raw_cmd, ' ');
	//map_val_to_export(&(*cmd)->cmd_args);
	map_val_to_redir(*cmd);
	int j = -1;
	while ((*cmd)->cmd_args[++j])
		printf("%d) lex cmd [%s]\n", j, (*cmd)->cmd_args[j]);
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

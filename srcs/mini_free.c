#include "minishell.h"

void	mini_free(t_shell *sh)
{
	free_2d(sh->env);
	clear_command(&sh->command);
	//free(sh->prompt);
}

void	clear_command(t_command **head)
{
	t_command *cur;

	if (!(head && *head))
		return ;
	cur = *head;
	*head = cur->next;
	if (cur->fd_in != STDIN_FILENO)
		close(cur->fd_in);
	if (cur->fd_out != STDOUT_FILENO)
		close(cur->fd_out);
	if (cur->cmd_path)
		free(cur->cmd_path);
	free_2d(cur->cmd_args);
	free(cur);
	clear_command(head);
}

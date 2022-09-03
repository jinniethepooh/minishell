#include "minishell.h"

void    mini_exit(void)
{
	printf("... exiting hell, "BRED"to a deeper!\n"RES);
	free(g_var.prompt);
	free(g_var.from_rl);
	free(g_var.usr);
	free_2d(g_var.env);
	clear_command(&g_var.command);
	exit(EXIT_SUCCESS);
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

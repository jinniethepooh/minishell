#include "minishell.h"

void	mini_exit(t_shell *sh)
{
	printf("... exiting hell, "BRED"to a deeper!\n"RES);
	mini_free(sh);
	exit(EXIT_SUCCESS);
}

void	mini_free(t_shell *sh)
{
	rl_clear_history();
	if (sh->prompt)
		free(sh->prompt);
	if (sh->from_rl)
		free(sh->from_rl);
	if (sh->usr)
		free(sh->usr);
	if (sh->env)
		free_2d(sh->env);
	clear_command(&sh->command);
	exp_stack_clear(&sh->export);
}

void	clear_command(t_command **head)
{
	t_command	*cur;

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

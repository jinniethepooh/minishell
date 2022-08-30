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
	free(cur->cmd_path);
	free_2d(cur->cmd_args);
	free(cur);
	clear_command(head);
}

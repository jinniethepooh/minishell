#include "minishell.h"

int mini_exec(t_shell *sh)
{
	t_command	*c;
	t_pipex		p;
	int			i;

	c = sh->command;
	p = setup_pipe(get_num_cmd(sh) - 1);
	i = 0;
	while (c)
	{
		p.proc[i] = fork();
		if (p.proc[i] < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (p.proc[i] == 0)
		{
			child_proc(c, p, i);
			exit(EXIT_SUCCESS);
		}
		call_builtin(c);
		i++;
		c = c->next;
	}
	close_pipe(p);
	wait_pipe(p);
	return (0);
}

void	child_proc(t_command *c, t_pipex p, int idx)
{
	if (!is_builtin(c->cmd_args))
	{
		if (c->fd_in != STDIN_FILENO || idx == 0)
			dup2(c->fd_in, STDIN_FILENO);
		else
			dup2(p.fd_end[(idx - 1) * 2], STDIN_FILENO);
		if (c->fd_out != STDOUT_FILENO || !c->next)
			dup2(c->fd_out, STDOUT_FILENO);
		else
			dup2(p.fd_end[idx * 2 + 1], STDOUT_FILENO);
		close_pipe(p);
		exec_pipe(c);
	}
}

#include "minishell.h"

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

int mini_exec(t_shell *sh)
{
	t_command	*c;
	t_pipex		p;
	int			i;

	c = sh->command;
	p = setup_pipe(sh);
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
		call_builtin(c->cmd_args);
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
		if (idx == 0)
		{
			if (dup2(g_var.fd_in, STDIN_FILENO) < 0)
				return ;
			dup2(p.fd_end[1], STDOUT_FILENO);
		}
		else if (!c->next)
		{
			dup2(g_var.fd_out, STDOUT_FILENO);
			dup2(p.fd_end[idx * 2 - 2], STDIN_FILENO);
		}
		else
		{
			dup2(p.fd_end[(idx - 1) * 2], STDIN_FILENO);
			dup2(p.fd_end[idx * 2 + 1], STDOUT_FILENO);
		}
		close_pipe(p);
		exec_pipe(c);
	}
}

#include "minishell.h"

t_pipex	setup_pipe(int n_pipe)
{
	t_pipex	p;
	int		i;

	p.n_pipe = n_pipe;
	i = 0;
	while (i < p.n_pipe)
	{
		if (pipe(p.fd_end + i++ *2) < 0)
			perror("pipe");
	}
	return (p);
}

void	exec_pipe(t_command *c)
{
	if (!c->cmd_path)
	{
		ft_putstr_fd("command not found\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (execve(c->cmd_path, c->cmd_args, g_var.env) < 0)
		perror("execve");
}

void	close_pipe(t_pipex p)
{
	int	i;

	i = 0;
	while (i < p.n_pipe * 2)
	{
		if (close(p.fd_end[i++]) < 0)
			perror("close");
	}
}

void	wait_pipe(t_pipex p)
{
	int	i;

	i = 0;
	while (i < p.n_pipe + 1)
	{
		if (waitpid(p.proc[i++], 0, 0) < 0)
			perror("waitpid");
	}
}

#include "minishell.h"

int	map_args_to_redir(t_command *cmd)
{
	char	*mode;
	int		i;

	if (!cmd->cmd_args)
		return (0);
	i = 0;
	while (cmd->cmd_args[i])
	{
		mode = cmd->cmd_args[i];
		if (ft_strcmp(mode, "<<") == 0 || ft_strcmp(mode, "<") == 0
			|| ft_strcmp(mode, ">>") == 0 || ft_strcmp(mode, ">") == 0)
		{
			if (mini_redir(cmd, i))
			{
				rm_from_2d(&cmd->cmd_args, i + 1);
				rm_from_2d(&cmd->cmd_args, i);
				continue ;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	mini_redir(t_command *c, int i)
{
	char	*mode;
	char	*name;

	mode = c->cmd_args[i];
	name = c->cmd_args[i + 1];
	if (ft_strcmp(mode, "<") == 0)
		c->fd_in = open(name, O_RDONLY);
	else if (ft_strcmp(mode, ">>") == 0)
		c->fd_out = open(name, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (ft_strcmp(mode, ">") == 0)
		c->fd_out = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (c->fd_in < 0 || c->fd_out < 0)
	{
		perror(name);
		return (0);
	}
	return (1);
}

int	map_args_to_heredoc(t_command *cmd)
{
	char	***args;
	int		i;

	if (!cmd)
		return (EXIT_SUCCESS);
	if (cmd->cmd_args)
	{
		args = &cmd->cmd_args;
		i = 0;
		while ((*args)[i])
		{
			if (ft_strcmp((*args)[i], "<<") == 0)
			{
				if (mini_heredoc(cmd, (*args)[i + 1]) == EXIT_SIGINT)
					return (EXIT_SIGINT);
				rm_from_2d(args, i + 1);
				rm_from_2d(args, i);
				continue ;
			}
			i++;
		}
	}
	return (map_args_to_heredoc(cmd->next));
}

static void	heredoc_child_proc(t_pipex p, char *eof)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			put_error(NULL, eof, 'h');
			break ;
		}
		if (ft_strcmp(line, eof) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, p.fd_end[1]);
		ft_putstr_fd("\n", p.fd_end[1]);
		free(line);
	}
	close_pipe(p);
}

int	mini_heredoc(t_command *cmd, char *eof)
{
	t_pipex	p;
	int		status;

	p = setup_pipe(1);
	p.proc[0] = fork();
	if (p.proc[0] < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (p.proc[0] == 0)
	{
		signal_settings_child(1);
		heredoc_child_proc(p, eof);
		exit(EXIT_SUCCESS);
	}
	signal_settings_child(0);
	cmd->fd_in = dup(p.fd_end[0]);
	close_pipe(p);
	waitpid(p.proc[0], &status, 0);
	if (WIFSIGNALED(status))
		if (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT)
			return (signal_exit_child(WTERMSIG(status)));
	return (WEXITSTATUS(status));
}

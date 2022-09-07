#include "minishell.h"

char	**map_val_to_redir(t_command *cmd)
{
	char	***args;
	char	*mode;
	int		i;

	if (!cmd->cmd_args)
		return (0);
	args = &cmd->cmd_args;
	i = 0;
	while ((*args)[i])
	{
		mode = (*args)[i];
		if (ft_strcmp(mode, "<<") == 0 || ft_strcmp(mode, "<") == 0
			|| ft_strcmp(mode, ">>") == 0 || ft_strcmp(mode, ">") == 0)
		{
			mini_redir(cmd, mode, (*args)[i + 1]);
			rm_from_2d(args, i + 1);
			rm_from_2d(args, i);
			continue ;
		}
		i++;
	}
	return (*args);
}

void	mini_redir(t_command *c, char *mode, char *name)
{
	t_pipex	p;

	if (ft_strcmp(mode, "<<") == 0)
	{
		p = mini_heredoc(name);
		c->fd_in = dup(p.fd_end[0]);
		close_pipe(p);
		return ;
	}
	else if (ft_strcmp(mode, "<") == 0)
		c->fd_in = open(name, O_RDONLY);
	else if (ft_strcmp(mode, ">>") == 0)
		c->fd_out = open(name, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (ft_strcmp(mode, ">") == 0)
		c->fd_out = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (c->fd_in < 0 || c->fd_out < 0)
		perror(name);
}

t_pipex	mini_heredoc(char *eof)
{
	t_pipex	p;
	char	*line;

	p = setup_pipe(1);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, eof) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, p.fd_end[1]);
		ft_putstr_fd("\n", p.fd_end[1]);
		free(line);
	}
	return (p);
}

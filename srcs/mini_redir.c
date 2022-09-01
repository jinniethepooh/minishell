#include "minishell.h"

void	mini_redir_input(t_command *c, char *mode, char *name)
{
	t_pipex	p;

	if (ft_strcmp(mode, "<<") == 0)
	{
		p = mini_heredoc(name);
		c->fd_in = dup(p.fd_end[0]);
		close_pipe(p);
		return ;
	}
	if (ft_strcmp(mode, "<") == 0)
		c->fd_in = open(name, O_RDONLY);
	if (c->fd_in < 0)
		perror(name);
}

void	mini_redir_output(t_command *c, char *mode, char *name)
{
	if (ft_strcmp(mode, ">") == 0)
		c->fd_out = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (ft_strcmp(mode, ">>") == 0)
		c->fd_out = open(name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (c->fd_out < 0)
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

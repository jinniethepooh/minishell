#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <curses.h>
# include <termios.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "colour.h"
# include "libft.h"
# include "mini_signal.h"

typedef struct s_pipex
{
	int		n_pipe;
	int		*fd_end;
	pid_t	*proc;
}	t_pipex;

typedef struct s_command
{
	char				*cmd_path;  // ex. "/usr/bin/cat"
	char				**cmd_args; // ex. "cat -e"
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	int			fd_in;
	int			fd_out;
	char		cwd[PATH_MAX];
	char		usr[256];
	t_command	*command;
	char		*prompt;
	char		**dir;
	char		**env;
	t_pipex		*pipex;
}	t_shell;

t_shell	g_var;

int		ft_wcount(const char *s, char c);
int		ft_isspace(char c);
void    mini_exit(t_shell *shell);

#endif

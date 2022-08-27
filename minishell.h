#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_pipex
{
	int		n_pipe;
	int		*fd_end;
	pid_t	*proc;
	int		is_heredoc;
	char	**argv;
	char	*cmd_path;
	char	**cmd_args;
}	t_pipex;

typedef struct s_shell
{
	int		fd_in;
	int		fd_out;
	char	cwd[256];
	char	usr[256];
	char	**argv;
	char	**env;
	t_pipex	*pipex;
}	t_shell;

t_shell	g_var;

#endif

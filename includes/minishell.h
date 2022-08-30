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
	int		fd_end[200];
	pid_t	proc[100];
}	t_pipex;

typedef struct s_command
{
	char				*cmd_path;  // ex. "/usr/bin/cat"
	char				**cmd_args; // ex. { "cat", "-e" }
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	int			fd_in;
	int			fd_out;
	char		cwd[PATH_MAX];
	char		usr[256];
	t_command	*command;
	char		*from_rl;
	char		*prompt;
	char		**dir;
	char		**env;
	int			exit_status;
}	t_shell;

t_shell	g_var;

int		ft_wcount(const char *s, char c);
int		ft_isspace(char c);
int		ft_isspecial(char c);
void    mini_exit(t_shell *shell);
void    get_cmd(t_shell *shell);

/* utils_2d.c */
int		size_2d(char **arr);
void	free_2d(char **arr);
char	**dup_2d(char **src_arr);
char	**add_to_2d(char **old_arr, char *mem);
char	**rm_from_2d(char **old_arr, int idx);

/* mini_env.c */
int		mini_setenv(char *name, char *val);
char	*mini_getenv(char *name);

/* mini_exec.c */
int 	mini_exec(t_shell *sh);
void	child_proc(t_command *c, t_pipex p, int idx);

/* mini_exec_utils.c */
t_pipex	setup_pipe(int n_pipe);
void	exec_pipe(t_command *c);
void	close_pipe(t_pipex p);
void	wait_pipe(t_pipex p);

/* mini_builtin.c */
int		is_builtin(char **args);
int		call_builtin(char **args);

/* mini_builtin_func.c */
int		builtin_echo(char **args);
int		builtin_cd(char **args);
int		builtin_pwd(void);
int		builtin_export(char **args);
int		builtin_unset(char **args);
int		builtin_env(void);
int		builtin_exit(void);

/* mini_free.c */
void	mini_free(t_shell *sh);
void	clear_command(t_command **head);

/* mini_cmd_utils.c */
char	*set_cmd_path(t_command *c);
int		get_num_cmd(t_shell *sh);

#endif

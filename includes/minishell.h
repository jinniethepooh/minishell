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
# include "mini_lexer.h"

typedef struct s_export
{
	char			*name;
	char			*val;
	struct s_export	*prev;
}	t_export;

typedef struct s_pipex
{
	int		n_pipe;
	int		fd_end[200];
	pid_t	proc[100];
}	t_pipex;

typedef struct s_command
{
	int					fd_in;
	int					fd_out;
	char				*cmd_path;
	char				**cmd_args;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	char		*usr;
	char		*prompt;
	t_command	*command;
	t_export	*export;
	char		*from_rl;
	char		**env;
	int			sig_detect;
	int			exit_status;
}	t_shell;

extern t_shell	g_var;

/* validator */
int		ft_isquotes(char c);
int		ft_isredir(char c);
int		is_input_valid(t_shell *sh);

/* helper */
int 	ft_loop_until(const char *s, char c, int flag);
void	put_error(char *title, char *token, int status);

/* mini_init.c */
t_shell	*shell_init(t_shell *sh, char **env);
void	set_prompt(t_shell *sh);
void	mini_add_history(t_shell *sh);

/* mini_exit.c */
void    mini_exit(t_shell *sh);
void	mini_free(t_shell *sh);
void	clear_command(t_command **head);

/* mini_cmd_utils.c */
char	*set_cmd_path(t_command *c);
int		get_num_cmd(t_shell *sh);

/* mini_env.c */
int		mini_setenv(char *name, char *val);
char	*mini_getenv(char *name);
int		is_envname_valid(char *name);

/* mini_redir.c */
int		map_args_to_redir(t_command *cmd);
int		mini_redir(t_command *c, int idx);
int		map_args_to_heredoc(t_command *cmd);
int		mini_heredoc(t_command *cmd, char *eof);

/* mini_exec.c */
int 	mini_exec(t_shell *sh);

/* mini_exec_utils.c */
t_pipex	setup_pipe(int n_pipe);
void	exec_pipe(t_command *c);
void	close_pipe(t_pipex p);
int		wait_pipe(t_pipex p);

/* mini_builtin.c */
int		is_builtin(char *arg);
int		call_builtin(t_command *c);

/* mini_builtin_func.c */
int		builtin_echo(char **args);
int		builtin_cd(char **args);
int		builtin_pwd(void);
int		builtin_env(void);
int		builtin_exit(void);

/* mini_builtin_func2.c */
int		builtin_export(char **args);
int		builtin_unset(char **args);
int		unset_env(char *arg);

/* mini_export.c */
int		export_env(char *arg);
char	**map_args_to_export(char ***arr);

/* mini_export_utils.c */
t_export	*exp_stack_new(char *name, char *val);
void		exp_stack_push(t_export **stack, t_export *node);
void		exp_stack_clear(t_export **head);
void		exp_stack_remove_if(t_export **head, char *data_ref);

#endif

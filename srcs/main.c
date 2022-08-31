#include "minishell.h"

// sample
//		./minishell "cd .. | ls"
//		./minishell "ls -al | cat Makefile | wc -l"

int	main(int argc, char **args, char **env)
{
	(void)args;
	if (argc != 2)
		return 0;

	g_var.env = dup_2d(env);

	t_command	**cmd;
	char	**temp = ft_split(args[1], '|');
	int		i = 0;

	cmd = &g_var.command;
	while (temp[i])
	{
		*cmd = malloc(sizeof(**cmd));
		(*cmd)->fd_in = STDIN_FILENO;
		(*cmd)->fd_out = STDOUT_FILENO;
		(*cmd)->cmd_args = ft_split(temp[i], ' ');
		if (i == 1)
		{
			// to test redir without lexer part
			// in normal shell
			//		ls -al | grep ma << eof | sort | wc -l
			// in minishell
			// instead of typing "<< eof", uncomment line 35
			//		./minishell "ls -al | grep ma | sort | wc -l"

			//mini_redir_input(*cmd, "<<", "eof");
		}
		(*cmd)->cmd_path = set_cmd_path(*cmd);
		cmd = &(*cmd)->next;
		i++;
	}
	free_2d(temp);
	*cmd = 0;

	mini_exec(&g_var);
	mini_free(&g_var);
}

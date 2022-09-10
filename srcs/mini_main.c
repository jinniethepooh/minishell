#include "minishell.h"

t_shell	g_var;

int	 main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	shell_init(&g_var, env);
	while (1)
	{
		set_prompt(&g_var);
		g_var.from_rl = readline(g_var.prompt);
		if (g_var.from_rl == NULL)
			break ;
		mini_add_history(&g_var);
		if (is_input_valid(&g_var))
		{
			get_cmd();
			g_var.exit_status = map_args_to_heredoc(g_var.command);
			if (g_var.exit_status != EXIT_SUCCESS)
				continue ;
			g_var.exit_status = mini_exec(&g_var);
		}
		free(g_var.prompt);
		free(g_var.from_rl);
	}
	mini_exit(&g_var);
	return (EXIT_SUCCESS);
}

#include "minishell.h"

static void	 get_history(void)
{
	int	 i;

	i = 0;
	while (g_var.from_rl[i])
	{
		if (!ft_isspace(g_var.from_rl[i]))
		{
			add_history(g_var.from_rl);
			return ;
		}
		++i;
	}
}

static char	*set_str_color(char *src, int start, char *color)
{
	char	*color_str;
	char	*temp;
	char	*result;

	temp = ft_strjoin(color, src + start);
	color_str = ft_strjoin(temp, RES);
	free(temp);
	temp = ft_substr(src, 0, start);
	result = ft_strjoin(temp, color_str);
	free(temp);
	free(color_str);
	return (result);
}

void	set_prompt(t_shell *sh)
{
	char	*temp;
	char	*cwd_color;
	char	*cwd;

	cwd = malloc(256 * sizeof(*cwd));
	*cwd = ':';
	getcwd(cwd + 1, 255);
	temp = mini_getenv("HOME");
	if (temp)
	{
		if (ft_strncmp(cwd + 1, temp, ft_strlen(temp)) == 0)
		{
			temp = ft_strjoin(":~", ft_strnstr(cwd + 1, temp, ft_strlen(cwd + 1)) + ft_strlen(temp));
			free(cwd);
			cwd = temp;
		}
	}
	cwd_color = set_str_color(cwd, 1, YEL);
	free(cwd);
	temp = ft_strjoin(sh->usr, cwd_color);
	free(cwd_color);
	sh->prompt = ft_strjoin(temp, "$ ");
	g_var.sig_detect = 0;
	free(temp);
}

static void	shell_init(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	signal_settings();
	g_var.env = dup_2d(env);
	g_var.usr = set_str_color(mini_getenv("USER"), 0, BCYN);
	g_var.from_rl = NULL;
	g_var.command = NULL;
	g_var.prompt = NULL;
	g_var.export = NULL;
}

int	 main(int argc, char **argv, char **env)
{
	shell_init(argc, argv, env);
	while (1)
	{
		set_prompt(&g_var);
		g_var.from_rl = readline(g_var.prompt);
		if (g_var.from_rl == NULL)
			mini_exit(&g_var);
		get_history();
		if (ft_isvalid_quotes() && ft_isvalid_pipe())
		{
			get_cmd();
			g_var.exit_status = mini_exec(&g_var);
			if (g_var.sig_detect)
				g_var.exit_status = EXIT_SIGINT;
			signal_settings();
		}
		free(g_var.prompt);
		free(g_var.from_rl);
	}
	mini_exit(&g_var);
	return (EXIT_SUCCESS);
}
#include "minishell.h"

static char	*set_str_color(char *src, int start, char *color);

t_shell	*shell_init(t_shell *sh, char **env)
{
	signal_settings();
	sh->env = dup_2d(env);
	sh->usr = set_str_color(mini_getenv("USER"), 0, BCYN);
	sh->from_rl = NULL;
	sh->command = NULL;
	sh->prompt = NULL;
	sh->export = NULL;
	sh->sig_detect = 0;
	return (sh);
}

static void	*get_prompt_dir(char *cwd, char *temp)
{
	if (ft_strncmp(cwd + 1, temp, ft_strlen(temp)) == 0)
	{
		temp = ft_strjoin(":~", ft_strnstr(cwd + 1, temp, \
			ft_strlen(cwd + 1)) + ft_strlen(temp));
		free(cwd);
		cwd = temp;
	}
	return (cwd);
}

void	set_prompt(t_shell *sh)
{
	char	*temp;
	char	*cwd_color;
	char	*cwd;

	cwd = malloc(257 * sizeof(*cwd));
	*cwd = ':';
	getcwd(cwd + 1, 256);
	temp = mini_getenv("HOME");
	if (temp)
		cwd = get_prompt_dir(cwd, temp);
	// {
		// if (ft_strncmp(cwd + 1, temp, ft_strlen(temp)) == 0)
		// {
		// 	temp = ft_strjoin(":~", ft_strnstr(cwd + 1, temp,
		// 		ft_strlen(cwd + 1)) + ft_strlen(temp));
		// 	free(cwd);
		// 	cwd = temp;
		// }
	// }
	cwd_color = set_str_color(cwd, 1, YEL);
	free(cwd);
	temp = ft_strjoin(sh->usr, cwd_color);
	free(cwd_color);
	sh->prompt = ft_strjoin(temp, "$ ");
	free(temp);
	signal_settings();
}

void	mini_add_history(t_shell *sh)
{
	if (!ft_isspace_str(sh->from_rl))
		add_history(sh->from_rl);
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

#include "minishell.h"

int	set_cmd_path(t_command *c)
{
	char	**env_paths;
	char	*temp;
	int		i;

	i = 0;
	env_paths = ft_split(getenv("PATH"), ':');
	while (env_paths[i])
	{
		temp = ft_strjoin(env_paths[i], "/");
		c->cmd_path = ft_strjoin(temp, c->cmd_args[0]);
		free(temp);
		if (access(c->cmd_path, F_OK) == 0)
			break ;
		free(c->cmd_path);
		i++;
	}
	free_2d_arr(env_paths);
	if (!c->cmd_path)
	{
		c->cmd_path = 0;
	}
	if (c->next)
		return (set_cmd_path(c->next));
	return (0);
}

/*
int	main()
{
	g_var.command = malloc(sizeof(*g_var.command));
	g_var.command->cmd_args = ft_split("cat -e", ' ');

	g_var.command->next = malloc(sizeof(*g_var.command->next));
	g_var.command->next->cmd_args = ft_split("ls -al", ' ');

	set_cmd_path(g_var.command);

	t_command	*cmd = g_var.command;
	while (cmd)
	{
		printf("cmd path %s\n", cmd->cmd_path);
		cmd = cmd->next;
	}
}
*/

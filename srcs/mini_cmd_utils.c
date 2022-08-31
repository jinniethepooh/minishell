#include "minishell.h"

char	*set_cmd_path(t_command *c)
{
	char	**env_paths;
	char	*temp;
	int		i;

	if (!c->cmd_args)
		return (0);
	if (access(c->cmd_args[0], F_OK) == 0)
		c->cmd_path = ft_strdup(c->cmd_args[0]);
	else
	{
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
			if (!env_paths[++i])
				c->cmd_path = 0;
		}
		free_2d(env_paths);
	}
	return (c->cmd_path);
}

int	get_num_cmd(t_shell *sh)
{
	t_command	*c;
	int			n;

	n = 0;
	c = sh->command;
	while (c)
	{
		n++;
		c = c->next;
	}
	return (n);
}

/*
int	main()
{
	g_var.command = malloc(sizeof(*g_var.command));
	g_var.command->cmd_args = ft_split("cat -e", ' ');

	g_var.command->next = malloc(sizeof(*g_var.command->next));
	g_var.command->next->cmd_args = ft_split("ls -al", ' ');

	set_cmd_path(g_var.command);
	set_cmd_path(g_var.command->next);

	t_command	*cmd = g_var.command;
	while (cmd)
	{
		printf("cmd path %s\n", cmd->cmd_path);
		cmd = cmd->next;
	}
}
*/

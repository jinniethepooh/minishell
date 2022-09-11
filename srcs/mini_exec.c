#include "minishell.h"

static int	fork_proc(t_command *cmd, t_pipex px, int idx);
static void	child_proc(t_command *cmd, t_pipex px, int idx);

int mini_exec(t_shell *sh)
{
	t_command	*cmd;
	t_pipex		px;

	cmd = sh->command;
	if (get_num_cmd(sh) == 1)
	{
		map_args_to_export(&cmd->cmd_args);
		if (!map_args_to_redir(cmd))
			return (EXIT_FAILURE);
		if (size_2d(cmd->cmd_args) < 1)
			return (EXIT_SUCCESS);
		if (is_builtin(cmd->cmd_args[0]) > 3)
			return (call_builtin(cmd));
	}
	px = setup_pipe(get_num_cmd(sh) - 1);
	return (fork_proc(cmd, px, 0));
}

static int	fork_proc(t_command *cmd, t_pipex px, int idx)
{
	if (!cmd)
	{
		signal_settings_child(0);
		close_pipe(px);
		return (wait_pipe(px));
	}
	px.proc[idx] = fork();
	if (px.proc[idx] < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (px.proc[idx] == 0)
	{
		signal_settings_child(1);
		child_proc(cmd, px, idx);
		exit(EXIT_SUCCESS);
	}
	return (fork_proc(cmd->next, px, idx + 1));
}

static void	child_proc(t_command *cmd, t_pipex px, int idx)
{
	map_args_to_export(&cmd->cmd_args);
	if (!map_args_to_redir(cmd))
		exit(EXIT_FAILURE);
	if (size_2d(cmd->cmd_args) < 1)
		exit(EXIT_SUCCESS);
	if (cmd->fd_in != STDIN_FILENO || idx == 0)
		dup2(cmd->fd_in, STDIN_FILENO);
	else
		dup2(px.fd_end[(idx - 1) * 2], STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO || !cmd->next)
		dup2(cmd->fd_out, STDOUT_FILENO);
	else
		dup2(px.fd_end[idx * 2 + 1], STDOUT_FILENO);
	close_pipe(px);
	cmd->cmd_path = set_cmd_path(cmd);
	exec_pipe(cmd);
}

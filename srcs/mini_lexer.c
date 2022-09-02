#include "minishell.h"

void     malloc_cmd(t_command **cmd)
{
        *cmd = malloc(sizeof(**cmd));
        if (!*cmd)
            mini_exit();
        (*cmd)->fd_in = STDIN_FILENO;
        (*cmd)->fd_out = STDOUT_FILENO;
}

void    get_cmd(void)
{
        t_command **cmd;
        char **tmp;
        int i;

        i = 0;
        if (g_var.from_rl)
        {
            cmd = &g_var.command;
            tmp = ft_split(g_var.from_rl, '|');
            while (tmp[i])
            {
                malloc_cmd(cmd);
                (*cmd)->cmd_args = ft_split(tmp[i], ' ');
                (*cmd)->cmd_path = NULL;
                cmd = &(*cmd)->next;
                ++i;
            }
            free_2d(tmp);
            *cmd = 0;
        }
}
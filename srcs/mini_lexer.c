#include "minishell.h"

// static void     redir_check_cmd(t_command **cmd)
// {
//         int i;

//         i = 0;
//         while ((*cmd)->cmd_args[i])
//         {
//             if (!ft_strcmp((*cmd)->cmd_args[i], ">"))
//                 mini_redir_output((*cmd), ">", )

//             ++i;
//         }
// }

char	**pipe_split(char const *s, char c);

static void     manage_cmd(t_command **cmd, char *raw_cmd)
{
        *cmd = malloc(sizeof(**cmd));
        if (!*cmd)
            mini_exit();
        (*cmd)->fd_in = STDIN_FILENO;
        (*cmd)->fd_out = STDOUT_FILENO;
        // to rebuilt ft_splt
        (*cmd)->cmd_args = ft_split(raw_cmd, ' ');
        (*cmd)->cmd_path = NULL;
        // redir_check_cmd(cmd);
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
            tmp = pipe_split(g_var.from_rl, '|');
            while (tmp[i])
            {
                manage_cmd(cmd, tmp[i]);
                cmd = &(*cmd)->next;
                ++i;
            }
            free_2d(tmp);
            *cmd = 0;
        }
}